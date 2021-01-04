#include <string.h>
#include <stdio.h>

/* Coverte um unsigned long em uma string retornando o nº de algarismos do número convertido */
int ulong_string(unsigned long x,char *alg);

/* Coverte um long long em uma string retornando o nº de algarismos do número convertido */
int llong_string(long long x,char *alg);

/* Coverte um inteiro em uma string retornando o nº de algarismos do número convertido */
int int_string(int x,char *alg);

/* Coloca no buffer_s as informações no formato que pretendemos para construir o ficheiro ".freq" de 1 bloco */
int do_freqAUX(char *buffer_e, char *buffer_s, unsigned long block_size);

/* Usando a "do_freqAUX", esta função escreve no ficheiro de saída o que vai recebendo no buffer_s e detalhes variados de um ficheiro do tipo ".freq" */
void do_freqM (char *nome_do_fich,  long long *n_blocks, unsigned long *size_of_last_block, unsigned long *block_size);
