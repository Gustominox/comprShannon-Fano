
#ifndef CD_BLOCOS_H
#define CD_BLOCOS_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Define o tamanho do bloco de entrada consoante o input recebido */
size_t definir_tamanho_bloco_entrada(char inp_size);

void data();

/* Preenche as variáveis que têm por apontadores os argumentos desta função com as respetivas informações necessárias para uma fase seguinte de um qualquer módulo */
void processamento_blocos(char nome_do_fich[],size_t inp_size,unsigned long long *tamanho_ficheiro, long long *n_blocks, unsigned long *size_of_last_block, unsigned long *block_size);


#endif //CD_BLOCOS_H
