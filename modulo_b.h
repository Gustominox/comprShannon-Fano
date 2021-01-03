#ifndef interface_h
#define interface_h
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


typedef struct VFS{
    char valor;
    int freq;
    char SF[20];
}vfs;

/* Calcula b^e */
int mypow(int b, int e);

/* Converte uma string que se refere a um inteiro em um inteiro */
int string_int(char *x, int *salto);

/* Dado um array de inteiros e o seu nº de elementos calculamos o maior elemento do array e guardamos em "im" o índice desse elemento */
int maior_array (int *f, int n, int *im);

/* Ordena um array de inteiros por ordem decrescente e coloca esses valores e o índice original no array da struct VFS */
void array_descendente (int *f, int n, vfs *aux);


void vfs_por_valor (vfs *tabela, int n);

int elem_nao_nulos(vfs *f, int n);

void shannon_fano(vfs *tabela, int nn, float met_tab);

void do_cod (char *nome_do_fich, unsigned long long tamanho_ficheiro);

#endif //CD_MAIN_INTERFACE_H