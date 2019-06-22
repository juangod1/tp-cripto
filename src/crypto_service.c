#include "include/crypto_service.h"
#include "include/utils.h"
#include <math.h>

#define NUMBER_OF_BITS(K) k == 2 ? 2 : 1

Matrix ** encrypt_image(Matrix * s, Matrix * w, int k, int n, Matrix ** rw_ret);
Matrix * decrypt_image(int k, int n, Matrix ** shs, Matrix * rw, char * decryption_path, Matrix ** w);

void hide_shadow(Matrix** matrix_vector, int amount_of_matrices, char* shadow_path, int number_of_bits, int shadow_number) {
    int rows = matrix_vector[0]->rows;
    int columns = matrix_vector[0]->columns;
    BitArray* bit_array = construct_bit_array(amount_of_matrices * rows * columns);

    for (int i = 0; i < amount_of_matrices; ++i) {
        BitArray* aux = build_bit_array_from_matrix(matrix_vector[i]);
        concatenate_bit_array(bit_array, aux);
    }

    BMP_Image * throwable = hide_matrix(bit_array, shadow_path, number_of_bits, shadow_number);
    destroyBMP(throwable);
}

Matrix*** recover_matrices(int k, int n, char** secret_images_paths, int * amount_p) {
    Matrix*** matrix_vector = malloc(k * sizeof(GMatrix**));

    for(int i = 0; i < k; i++){
        BMP_Image* image = readBMP(secret_images_paths[i]);
        int counter = 0;

        int amount_of_matrices = (image->width/n) * (image->height/n);
        matrix_vector[i] = malloc(amount_of_matrices * sizeof(GMatrix*));

        BitArray* bit_array = recover_matrix(image, NUMBER_OF_BITS(k));

        for (int j = 0; j < amount_of_matrices; ++j) {
            matrix_vector[i][j] = conversion_to_matrix(build_Gmatrix_from_array(bit_array->numbers + counter, n, n));
            counter += n*n;
        }
        *amount_p=amount_of_matrices;
    }

    return matrix_vector;
}



void encrypt_loop(char* secret_image_path, char* watermark_image_path, char** shadows_path, int k, int n)
{
    BMP_Image* secret_image = readBMP(secret_image_path);
    BMP_Image* watermark_image = readBMP(watermark_image_path);

    if(secret_image->bpp!=8)
    {
        printf("ERROR: SECRET IMAGE HAS '%d' bpp. Exiting program...\n",secret_image->bpp);
        destroyBMP(secret_image);
        destroyBMP(watermark_image);
        exit(EXIT_FAILURE);
    }
    int pixel_amount = secret_image->height*secret_image->width;
    if(pixel_amount%(n*n)!=0)
    {
        printf("ERROR: SECRET IMAGE HAS '%d' PIXELS. Not divisible by n*n. Exiting program...\n",pixel_amount);
        destroyBMP(secret_image);
        destroyBMP(watermark_image);
        exit(EXIT_FAILURE);
    }

    uint8_t * secret_ptr = secret_image->data;
    uint8_t * watermark_ptr = watermark_image->data;

    int s_amount = pixel_amount/(n*n);

    Matrix *** shadows = malloc(n*sizeof(Matrix **));
    for(int i=0; i<n; i++)
    {
        shadows[i]=malloc(s_amount* sizeof(Matrix *));
    }
    Matrix ** rws = malloc(s_amount*sizeof(Matrix *));

    for(int counter=0; counter<s_amount; counter++)
    {
        Matrix * current_s = constructor(n,n);
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                current_s->numbers[j][i]= *secret_ptr++;
            }
        }
        Matrix * current_w = constructor(n,n);
        for(int i=0;i<n;i++)
        {
            for(int j=0; j<n;j++)
            {
                current_w->numbers[j][i] = *watermark_ptr++;
            }
        }
        Matrix ** shs = encrypt_image(current_s,current_w,k,n,&(rws[counter]));

        for(int i=0; i<n; i++)
        {
            shadows[i][counter] = shs[i];
        }
        destroy_matrix_vec(shs,n);
        destroy_matrix(current_s);
        destroy_matrix(current_w);
    }



    for(int i=0; i<n; i++)
    {
        hide_shadow(shadows[i],s_amount,shadows_path[i],NUMBER_OF_BITS(k),i);
        destroy_matrix_vec(shadows[i],s_amount);
    }
    free(shadows);

    //todo: funcion de juan para guardar rw

    destroy_matrix_vec(rws,s_amount);
    destroyBMP(watermark_image);
    destroyBMP(secret_image);
}

Matrix ** encrypt_image(Matrix * s, Matrix * w, int k, int n, Matrix ** rw_ret)
{

    Matrix* a = generate_a(k, s);
    Matrix** x_vec = generate_x_vec(n, k);
    Matrix** v_vec = generate_v_vec(x_vec, n, a);
    Matrix* ss = compute_ss(a);
    Matrix* r = generate_r(s, ss);
    int* c_vec = generate_c_vec(n);

    Matrix ** ret  = malloc(n*sizeof(Matrix *));

    for (int i = 0; i < n; ++i) {
        int j = i +1; //index starts in 1
        Matrix* g = generate_G(j, r, c_vec, n, k);
        Matrix* sh = generate_sh(v_vec[i], g);
        ret[i]=sh;
        destroy_matrix(g);
    }

    *rw_ret = generate_rw(w, ss);

    destroy_matrix(a);
    destroy_matrix_vec(x_vec,n);
    destroy_matrix_vec(v_vec,n);
    destroy_matrix(s);
    destroy_matrix(w);
    destroy_matrix(ss);
    destroy_matrix(r);
    free(c_vec);

    return ret;
}


void decrypt_loop(int k, int n, char ** secret_images_paths, char * rw_path, char * decryption_path)
{
    int sh_amount;
    Matrix *** shs = recover_matrices(k,n,secret_images_paths,&sh_amount);
    int rw_amount =10; //todo: funcion juan
    Matrix ** rw = malloc(3); //todo:funcion juan

    if(sh_amount!=rw_amount)
    {
        printf("ERROR: Amount of SH: '%d', Amount of RW: '%d'. Exiting program...\n",sh_amount,rw_amount);
        for(int i=0; i<k;i++)
        {
            destroy_matrix_vec(shs[i],sh_amount);
        }
        free(shs);
        destroy_matrix_vec(rw,rw_amount);
        exit(EXIT_FAILURE);
    }

    Matrix ** w = malloc(sh_amount*sizeof(Matrix *));
    Matrix ** s = malloc(sh_amount*sizeof(Matrix *));

    for(int i=0; i<sh_amount; i++)
    {
        Matrix ** current_shs = shs[i];
        Matrix * current_rw = rw[i];
        s[i] = decrypt_image(k,n,current_shs,current_rw,decryption_path,&(w[i]));
    }

    //todo: funcion de juan para guardar w;
    //todo: funcion de juan para guardar s;

    destroy_matrix_vec(w,sh_amount);
    destroy_matrix_vec(s,sh_amount);
    for(int i=0; i<k;i++)
    {
        destroy_matrix_vec(shs[i],sh_amount);
    }
    free(shs);
    destroy_matrix_vec(rw,rw_amount);
}

Matrix * decrypt_image(int k, int n, Matrix ** shs, Matrix * rw, char * decryption_path, Matrix ** w)
{
    Matrix * keanu = generate_B(shs,k);
    Matrix * ss = compute_ss(keanu);
    Matrix ** g_vec = compute_G_vec(shs, k);
    Matrix * r = compute_R_from_G_vec(g_vec, k, n);
    *w = compute_w_from_SS_and_Rw(ss, rw);
    Matrix * s = compute_s_from_SS_and_R(ss, r);


    destroy_matrix(r);
    destroy_matrix_vec(g_vec, k);
    destroy_matrix(keanu);
    destroy_matrix(ss);

    return s;
}