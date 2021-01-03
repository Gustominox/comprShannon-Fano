
#ifndef CD_BLOCOS_H
#define CD_BLOCOS_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

size_t definir_tamanho_bloco_entrada(char inp_size);

void data();

void processamento_blocos(char nome_do_fich[],size_t inp_size,unsigned long long *tamanho_ficheiro, long long *n_blocks, unsigned long *size_of_last_block, unsigned long *block_size);


#endif //CD_BLOCOS_H
