#include "funcoes.c"

int main(void){

    setlocale(LC_ALL, "pt_BR.UTF-8");

    // variaveis para manipulação dos arquivos
    char acao;
    char *nome_processo;
    int tam_processo;

    // variaveis para manipulação das funções
    int tamanho_mf, tamanho_ms, tamanho_pag, tamanho_qm, tamanho_el;

    // variaveis para alocacao de memoria
    P *aux_processo;
    MP *mem_principal;
    MS *mem_secundaria;
    PG *vetor_paginas;

    configuracoes(&tamanho_mf, &tamanho_ms, &tamanho_pag, &tamanho_qm, &tamanho_el, mem_principal, mem_secundaria, vetor_paginas);

    // alocando a memoria necessaria
    mem_principal = (*mem_principal)malloc(sizeof(mem_principal) * mem_principal->tamanho_mp);
    if(!mem_principal) exit(1);

    mem_secundaria = (*mem_secundaria)malloc(sizeof(mem_secundaria) * mem_secundaria->tamanho_ms);
    if(!mem_secundaria) exit(1);

    // abrindo o arquivo
    FILE* fila_processos = fopen("processos.txt", "r");
    if(fila_processos == NULL){
        printf("Erro na leitura da fila de processos. \n");
        exit(1);
    }

    // readline do arquivo e execucao
    while(fscanf(fila_processos, "%s %c %d", nome_processo, acao, &tam_processo)){
        flags(proc, acao, nome_processo, tam_processo, mem_secundaria);
    }
    
    // fechando o arquivo
    fclose(fila_processos);

    // liberando memoria
    free(mem_principal);
    free(mem_secundaria);
    free(vetor_paginas);

    return 0;
}