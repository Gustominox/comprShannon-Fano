#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "blocos.h"
#include "modulo_a.h"
#include "freq.h"
#include "modulo_b.h"

//Shell> shafa exemplo.txt -m f -c r 
//gcc -o bot *.c


/*{
    unsigned long long tamanho_ficheiro;
    long long n_blocks;
    unsigned long size_of_last_block;
    unsigned long block_size;
    size_t input_size = 65536;
    char nome_do_fich[100]="aaa.txt";
    printf("%s",nome_do_fich);
    processamento_blocos(nome_do_fich,input_size,&tamanho_ficheiro, &n_blocks, &size_of_last_block, &block_size); 
    printf("print:%llu\n%lu\n%lld\n%lu\n\n", tamanho_ficheiro,block_size,n_blocks,size_of_last_block);
    modulo_a_exe(nome_do_fich,input_size,&tamanho_ficheiro, &n_blocks, &size_of_last_block, &block_size);
    printf("print:%llu\n%lu\n%lld\n%lu\n", tamanho_ficheiro,block_size,n_blocks,size_of_last_block);

}*/

int main(int argc, char *argv[ ]){
    if(argc<4) exit(0);
    unsigned long long tamanho_ficheiro;
    long long n_blocks;
    unsigned long size_of_last_block;
    unsigned long block_size;
    int rle = 1;
    size_t input_size;
    char nome_do_fich_rle[100]="";
    char nome_do_fich[100];
    strcpy(nome_do_fich,argv[1]);
    char mod   = argv[3][0];
    char temp1 = '\0';
    char temp2 = '\0';
    char temp3 = '\0';
    char temp4 = '\0';
    if(argc>4){
    temp1 = argv[4][1];//c ou b
    temp2 = argv[5][0];
    }
    if(argc>6){
    temp3 = argv[6][1];//c ou b
    temp4 = argv[7][0];    
    }
    
    float compressaototal;
    float compressao;
    clock_t start_t,end_t;
    double t_exec;



    
    printf("Augusto Campos, a93320, MIEI/CD\nCarlos Silva, a93199, MIEI/CD\nTiago Alexandre Silva, a93182,MIEI/CD\nTiago Pinheiro Silva, a93285, MIEI/CD\n");
    data();            
    if (mod == 'f') {
        if (temp1 == 'b') input_size = definir_tamanho_bloco_entrada(temp2);
        else input_size = definir_tamanho_bloco_entrada(temp4);
        
                //excuta o modulo f
                start_t = clock();
                processamento_blocos(nome_do_fich,input_size,&tamanho_ficheiro, &n_blocks, &size_of_last_block, &block_size); 
                 
                unsigned long long tamanho_ficheiro_ori = tamanho_ficheiro;
                printf("Módulo: f (cálculo das frequências dos símbolos)\n");
                printf("Número de Blocos: %lld\n", n_blocks);
                printf("Tamanho dos blocos analisados no ficheiro original: ");
                for (int i = 0; i < n_blocks - 1; i++)
                    printf("%lu/", block_size);
                printf("%lu bytes\n", size_of_last_block);
                
                unsigned long block_size_rle[n_blocks];
                do_rle(nome_do_fich,input_size,&compressao,&tamanho_ficheiro, &n_blocks, &size_of_last_block, &block_size,block_size_rle);
                
                
                if (compressao<5.0)
                    rle =0;   
                
            
                if ((temp1 == 'c' && temp2 == 'r')||(temp3 =='c' && temp4 == 'r')){
                    rle = 1;
                    strcat(nome_do_fich,".rle");
                } 
                
                if (rle == 1){
                    unsigned long long tamanho_ficheiro_rle = tamanho_ficheiro;
                    
                    strcpy(nome_do_fich_rle,nome_do_fich);
                    float aux = (tamanho_ficheiro_ori-tamanho_ficheiro_rle);
                    //printf("%d - %d = %f",tamanho_ficheiro_ori,tamanho_ficheiro_rle,aux);
                    compressaototal = (aux/tamanho_ficheiro_ori*100);
                    
                    printf("Compressão RLE: %s (%.2f%% compressão)\n",nome_do_fich, compressaototal);//Compressão RLE: exemplo.txt.rle (13% compressão)
                    
                    printf("Tamanho dos blocos analisados no ficheiro RLE: ");
                    for (int i = 0; i < n_blocks - 1; i++)
                        printf("%lu/", block_size_rle[i]);
                    printf("%lu bytes\n", size_of_last_block);
                    processamento_blocos(nome_do_fich_rle,input_size,&tamanho_ficheiro, &n_blocks, &size_of_last_block, &block_size); 
                                          
                    do_freqM(nome_do_fich_rle,  &n_blocks, &size_of_last_block, &block_size);
                    
                
                }else{
                    
                    processamento_blocos(nome_do_fich,input_size,&tamanho_ficheiro, &n_blocks, &size_of_last_block, &block_size); 
               
                    do_freqM(nome_do_fich,  &n_blocks, &size_of_last_block, &block_size);
                    
                }
                
                    end_t = clock();
                    t_exec = ((double)(end_t-start_t)/ CLOCKS_PER_SEC) * 1000.0;
                    printf("Tempo de execução do módulo (ms): %.3f\n", t_exec);
                    printf("Ficheiros gerados: %s %s\n", nome_do_fich, nome_do_fich_rle);    
                
    }
    else if (mod == 't') {
        //excuta o modulo t
        start_t = clock();
        processamento_blocos(nome_do_fich,65538,&tamanho_ficheiro,&n_blocks,&size_of_last_block,&block_size);
        
        
        printf("Módulo: t (cálculo dos códigos dos símbolos)\n");
        do_cod(nome_do_fich,tamanho_ficheiro);

        end_t = clock();
        t_exec = ((double)(end_t-start_t)/ CLOCKS_PER_SEC) * 1000.0;
        printf("Tempo de execução do módulo (ms): %.3f\n", t_exec);
        printf("Ficheiro gerado: %s\n", nome_do_fich);
     
    }
    
    

}

/* No processamento por blocos o ficheiro é dividido pelo tamanho dado pelo utilizador (block_size), ao realizar a Compressao RLE os 
blocos que tinham block_size mudam de tamanho, na nossa implementaçao, antes de calcular as frequencias dos blocos, criamos 
um ficheiro ".rle", ou seja, se os blocos rle tinham: 654780/345782/3008 bytes, o ficheiro ".rle" tem 1003570 bytes e os blocos processados
para o calculo das frequencias tem block_size (655360/348210).

Quando realizamos o RLE o tamanho dos blocos finais mantem-se com o tamanho inicial,
 porém o ficheiro é comprimido, pois o número de blocos e/ou o tamanho do último bloco diminui.*/


/*{
unsigned long long tamanho_ficheiro;
long long n_blocks;
unsigned long size_of_last_block, block_size;
char nome_do_fich [100] = "ddd.rle";
char inp_size = 'b';
processamento_blocos(nome_do_fich,inp_size,&tamanho_ficheiro, &n_blocks, &size_of_last_block, &block_size);

printf("print:%llu\n%lu\n%lld\n%lu\n", tamanho_ficheiro,block_size,n_blocks,size_of_last_block);
do_freqM(nome_do_fich,&tamanho_ficheiro, &n_blocks, &size_of_last_block, &block_size);
}


*/