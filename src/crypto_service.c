#include "include/crypto_service.h"
#include "include/utils.h"
#include <math.h>

#define NUMBER_OF_BITS(K) k == 2 ? 2 : 1

Matrix ** encrypt_image(Matrix * s, Matrix * w, int k, int n, Matrix ** rw_ret);
Matrix * decrypt_image(int k, int n, Matrix ** shs, Matrix * rw,Matrix ** w, char * shadow_numbers);

void hide_shadow(Matrix** matrix_vector, int amount_of_matrices, char* shadow_path, int number_of_bits, char shadow_number)
{
    BitArray* bit_array = construct_bit_array(0);

    for (int i = 0; i < amount_of_matrices; ++i) {
        BitArray* aux = build_bit_array_from_matrix(matrix_vector[i]);
        bit_array = concatenate(bit_array, aux);
        destroy_bit_array(aux);
    }

    BMP_Image * throwable = hide_matrix(bit_array, shadow_path, number_of_bits, (char)shadow_number);

    if(throwable == NULL)
        exit(EXIT_FAILURE);

    destroyBMP(throwable);
    destroy_bit_array(bit_array);
}

Matrix*** recover_matrices(int k, int n, char** secret_images_paths, int * amount_p, char * shadow_numbers)
{
    Matrix*** matrix_vector = malloc(k * sizeof(Matrix**));

    for(int i = 0; i < k; i++){
        BMP_Image* image = readBMP(secret_images_paths[i]);
        shadow_numbers[i] = image->shadow;
        int counter = 0;

        int amount_of_matrices = (image->width/n) * (image->height/n);
        matrix_vector[i] = malloc(amount_of_matrices * sizeof(Matrix*));

        BitArray* bit_array = recover_matrix(image, NUMBER_OF_BITS(k));

        for (int j = 0; counter < bit_array->size; ++j) {
            matrix_vector[i][j] = build_matrix_from_array(bit_array->numbers + counter, n, k+1);
            counter += (n*(k+1));
        }

        *amount_p = amount_of_matrices;
        destroyBMP(image);
        destroy_bit_array(bit_array);
    }

    return matrix_vector;
}


void encrypt_loop(char* secret_image_path, char* watermark_image_path, char** shadows_path, int k, int n)
{
    BMP_Image* secret_image = readBMP(secret_image_path);
    BMP_Image* watermark_image = readBMP(watermark_image_path);

    int pixel_amount = secret_image->height * secret_image->width;

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
                uint8_t * pointer = secret_image->data + counter*n*n + i*n + j;
                current_s->numbers[j][i]= *pointer;
            }
        }
        Matrix * current_w = constructor(n,n);
        for(int i=0;i<n;i++)
        {
            for(int j=0; j<n;j++)
            {
                uint8_t * pointer = watermark_image->data + counter*n*n + i*n + j;
                current_w->numbers[j][i] = *pointer++;
            }
        }
        Matrix ** shs = encrypt_image(current_s,current_w,k,n,&(rws[counter]));

        for(int i=0; i<n; i++)
        {
            shadows[i][counter] = shs[i];
        }
        free(shs);
        destroy_matrix(current_s);
        destroy_matrix(current_w);
    }



    for(int i=0; i<n; i++)
    {
        hide_shadow(shadows[i],s_amount,shadows_path[i],NUMBER_OF_BITS(k),i);
        destroy_matrix_vec(shadows[i],s_amount);
    }
    free(shadows);

    createImageFromMatrices(rws, watermark_image_path, s_amount, secret_image->width, secret_image->height);

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
        int j = i +1;
        Matrix* g = generate_G(j, r, c_vec, n, k);
        Matrix* sh = generate_sh(v_vec[i], g);
        ret[i]=sh;
        destroy_matrix(g);
    }

    *rw_ret = generate_rw(w, ss);

    destroy_matrix(a);
    destroy_matrix_vec(x_vec,n);
    destroy_matrix_vec(v_vec,n);
    destroy_matrix(ss);
    destroy_matrix(r);
    free(c_vec);

    return ret;
}


void decrypt_loop(int k, int n, char ** secret_images_paths, char * rw_path, char * decryption_path)
{
    int sh_amount;
    char * shadow_numbers= malloc(k* sizeof(char));
    Matrix *** shs = recover_matrices(k,n,secret_images_paths,&sh_amount,shadow_numbers);

    int rw_amount;
    Matrix ** rw = createMatricesFromImage(rw_path, &rw_amount, n);

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
        Matrix ** current_shs = malloc(k*sizeof(Matrix*));
        for(int j=0; j<k; j++){
            current_shs[j] = shs[j][i];
        }
        Matrix * current_rw = rw[i];
        s[i] = decrypt_image(k,n,current_shs,current_rw,&(w[i]),shadow_numbers);
        free(current_shs);
    }

    BMP_Image * water = readBMP(rw_path);

    createImageFromMatrices(rw, "../watermark_out.bmp", rw_amount, water->width, water->height);
    createImageFromMatrices(s, decryption_path, sh_amount,  water->width, water->height);

    destroy_matrix_vec(w,sh_amount);
    destroy_matrix_vec(s,sh_amount);
    for(int i=0; i<k;i++)
    {
        destroy_matrix_vec(shs[i],sh_amount);
    }
    free(shs);
    destroy_matrix_vec(rw,rw_amount);

    destroyBMP(water);
}

Matrix * decrypt_image(int k, int n, Matrix ** shs, Matrix * rw,Matrix ** w, char * shadow_numbers)
{
    Matrix * keanu = generate_B(shs,k);
    Matrix * ss = compute_ss(keanu);
    Matrix ** g_vec = compute_G_vec(shs, k);
    Matrix * r = compute_R_from_G_vec(g_vec, k, n,shadow_numbers);
    *w = compute_w_from_SS_and_Rw(ss, rw);
    Matrix * s = compute_s_from_SS_and_R(ss, r);


    destroy_matrix(r);
    destroy_matrix_vec(g_vec, k);
    destroy_matrix(keanu);
    destroy_matrix(ss);

    return s;
}