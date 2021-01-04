#include "blocos.h"
#include "fsize.h"

size_t definir_tamanho_bloco_entrada (char inp_size) {
    size_t tam = 65536;
    if (inp_size == 'K') tam = 655360;
    if (inp_size == 'm') tam = 8388608;
    if (inp_size == 'M') tam = 67108864;
                               
    return tam;
}

void data() {
    int dia, mes, ano;
    time_t now;

    time(&now);

    struct tm *local = localtime(&now);

    dia = local->tm_mday;
    mes = local->tm_mon + 1;
    ano = local->tm_year + 1900;

    printf("%02d/%02d/%d\n", dia, mes, ano);

}

void processamento_blocos(char nome_do_fich[],size_t inp_size,unsigned long long *tamanho_ficheiro, long long *n_blocks, unsigned long *size_of_last_block, unsigned long *block_size){

FILE *f_e;

 
f_e = fopen(nome_do_fich, "rb");

*block_size = inp_size; 

*n_blocks = fsize(f_e, NULL, block_size, size_of_last_block);
*tamanho_ficheiro = (*n_blocks-1) * *block_size + *size_of_last_block; 

if(*size_of_last_block < 1024) {
    *n_blocks = *n_blocks-1;
    *size_of_last_block = *block_size+*size_of_last_block;
    }
    fclose(f_e);
}
