
#ifndef modulo_a_h
#define modulo_a_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Função auxiliar do RLE que prepara o buffer_s para posterior escrita no ficheiro .rle */
int do_rle_aux(char buffer_e[],char buffer_s[],size_t tmh_buf);

/* Escreve no buffer_s a sequência "exceção" no formato RLE */
void escreve_rle_seq(char buffer_s[], int *i_s,int cont_seq);

/* Escreve no buffer_s uma qualquer sequência no formato RLE */
void escreve_rle(int n_letras, char letra, char buffer_s[], int *i_s);

/* Usando a "do_rle_aux", esta função escreve no ficheiro RLE o que vai recebendo no buffer_s */
void do_rle(char *nome_do_fich,size_t inp_size,float *compressao,unsigned long long *tamanho_ficheiro, long long *n_blocks, unsigned long *size_of_last_block, unsigned long *block_size, unsigned long *block_size_rle);
#endif //modulo_a_h
