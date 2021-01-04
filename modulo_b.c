#include "modulo_b.h"

int mypow(int b, int e){
    int r = 1;
    for(int i = 0; i < e; i++)
        r = r * b;
    return r;
}

int string_int(char *x, int *salto){
    int r, i, j;
    int alg[21];
    if (x[0] != '@' && x[0] != ';'){
        for(i = 0; x[i] != '@' && x[i] != ';'; i++)
            alg[i] = x[i] - 48;
        j = i;
        *salto = j + 1;
        r = 0;
        i = 0;
        for (int k = j-1;  k >= 0; k--){
            r = r + (alg[k] * mypow(10, i));
            i++;
        }
    }
    else{
        r = -1;
        *salto = 1;
    }        
    return r;
}

int maior_array (int *f, int n, int *im){
    int m;
    *im = 0;
    m = -1;
    for (int i = 0; i < n; i++){
        if (f[i] > m){ 
            *im = i;
            m = f[i];
        }
    }
    return m;
}

void array_descendente (int *f, int n, vfs *aux){
    int im;
    for (int i = 0; i < n; i++){
        aux[i].freq = maior_array (f, n, &im);
        aux[i].valor = im;
        aux[i].SF[0] = '\0';
        f[im] = -1;
    }           
}

void vfs_por_valor (vfs *tabela, int n){
    vfs aux[n];
    for (int i = 0; i < n; i++){
    
        int a = tabela[i].valor;
        aux[a].freq = tabela[i].freq;
        aux[a].valor = a;
        strcpy(aux[a].SF, tabela[i].SF);
    }
    for (int i = 0; i < n; i++){
        strcpy(tabela[i].SF, aux[i].SF);
        tabela[i].freq = aux[i].freq;
        tabela[i].valor = aux[i].valor;
    }  
}

int elem_nao_nulos(vfs *f, int n){
    for (int i = 0; i < n; i++)
        if (f[i].freq == 0) return i;
    return n;
}

void shannon_fano(vfs *tabela, int nn, float met_tab){
    int i, j;
    float soma = 0;
    for(i = 0; i < nn; i++){
        soma = soma + tabela[i].freq;
        if (soma > met_tab){ 
            break;
        }    
    }
    if ((abs(soma - met_tab)) > (abs(soma - tabela[i].freq - met_tab))){
        soma = soma - tabela[i].freq;
        i--;
    }
    for(j = 0; j < nn; j++){
        if(j <= i)
            strcat(tabela[j].SF, "0");
        else
            strcat(tabela[j].SF, "1");  
    }
    if (i+1 > 1)
        shannon_fano(tabela, i + 1, soma/2.0);
    if (nn - i - 1 > 1)
        shannon_fano(tabela + i + 1, nn - i - 1, ((met_tab * 2) - soma)/2.0);  
}

void do_cod (char *nome_do_fich, unsigned long long tamanho_ficheiro){
    FILE *f_e = fopen(nome_do_fich, "rb");
    char nome_do_fich_cod[100];
    strcpy(nome_do_fich_cod, nome_do_fich);
    strcat(nome_do_fich_cod, ".cod");
    FILE *f_s = fopen(nome_do_fich_cod, "w+");
    int frequencias[256];
    int i_s, salto, i_buffer_s;
    long long n_blocks;
    unsigned long size_of_last_block, block_size;
    vfs tabela[256];
    char buffer_e[tamanho_ficheiro];
    char buffer_s[128000];
    fread(buffer_e, tamanho_ficheiro, 1, f_e);
    n_blocks = string_int(buffer_e + 3, &salto);
    printf("Número de Blocos: %lld\n", n_blocks);
    i_s = 3 + salto;
    fwrite(buffer_e, i_s, 1, f_s);
    printf("Tamanho dos blocos analisados no ficheiro de símbolos: ");
    for(int j = 0; j < n_blocks-1; j++){
        block_size = string_int(buffer_e + i_s, &salto);
        printf("%lu/", block_size);
        fwrite(buffer_e + i_s, salto, 1, f_s);
        i_s = i_s + salto;
        int i = 0;
        int k;
        int last_freq = -1;
        for(i = 0; i < 256; i++){
            frequencias[i] = string_int(buffer_e + i_s, &salto);
            if (frequencias[i] == -1)
                frequencias[i] = last_freq;
            last_freq = frequencias[i];    
            i_s = i_s + salto;
        }   
        array_descendente(frequencias, 256, tabela);
        int nn = elem_nao_nulos(tabela, 256);
        shannon_fano(tabela, nn, block_size / 2.0);
        vfs_por_valor(tabela, 256);
        i_buffer_s = 0;
        for(k = 0; k < 256; k++){
            int t = strlen(tabela[k].SF);
            char aux[21];
            for(int l = 0; l < t; l++)
                aux[l] = tabela[k].SF[l];
            aux[t] = '\0';    
            strcpy(buffer_s + i_buffer_s, aux);
            i_buffer_s = i_buffer_s + t;
            if (k != 255){
                buffer_s[i_buffer_s] = ';';
                i_buffer_s++;
            }            
        }
        buffer_s[i_buffer_s] = '@';
        i_buffer_s++;
        fwrite(buffer_s, i_buffer_s, 1, f_s);  
    }

    size_of_last_block = string_int(buffer_e + i_s, &salto);
    printf("%lu bytes\n", size_of_last_block);
    fwrite(buffer_e + i_s, salto, 1, f_s);
    i_s = i_s + salto;
    int i = 0;
    int last_freq = -1;
    for(i = 0; i < 256; i++){
        frequencias[i] = string_int(buffer_e + i_s, &salto);
        if (frequencias[i] == -1)
            frequencias[i] = last_freq;
        last_freq = frequencias[i];    
        i_s = i_s + salto;    
    }
    array_descendente(frequencias, 256, tabela);
    int nn = elem_nao_nulos(tabela, 256);
    shannon_fano(tabela, nn, size_of_last_block / 2.0);
    vfs_por_valor(tabela, 256);
    i_buffer_s = 0;
    for(int k = 0; k < 256; k++){
        int t = strlen(tabela[k].SF);
            char aux[20];
            for(int l = 0; l < t; l++)
                aux[l] = tabela[k].SF[l];
            aux[t] = '\0';    
            strcpy(buffer_s + i_buffer_s, aux);
        i_buffer_s = i_buffer_s + t;
        if (k != 255){
            buffer_s[i_buffer_s] = ';';
            i_buffer_s++;
        }         
    }
    buffer_s[i_buffer_s] = '@';
    i_buffer_s++;
    fwrite(buffer_s, i_buffer_s, 1, f_s);
    buffer_s[0] = '0';
    fwrite(buffer_s, 1, 1, f_s);

fclose(f_e);
fclose(f_s);
strcpy(nome_do_fich,nome_do_fich_cod);
}
