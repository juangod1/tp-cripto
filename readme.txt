#############################
# Instalación y Compilación #
#############################

tar -xvf gruopo09.tar.gz
cd tp-cripto/src
cmake -S ./
make


#############################
#        Ejecución          #
#############################
----------
ENCRIPCIÓN
----------
./ss -d -s Albert.bmp -m Paris.bmp -k 2 -n 4 --dir color280x440/

----------
DECRIPCIÓN
----------
./ss -d -s secreto.bmp -m color280x440/RW/RW.bmp -k 2 -n 4 --dir color280x440/

----------
TESTS
----------
./ss -t

Aclaración: 
A pedido del enunciado, ninguna de las imágenes referidas anteriormente estará en el tar.gz, deben ser incluidas externamente.
