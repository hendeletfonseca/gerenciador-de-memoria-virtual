#include "funcoes_2.c"

int main(void){

    setlocale(LC_ALL, "pt_BR.UTF-8");

    // variaveis para manipulação dos arquivos
    char acao;
    char *nome_processo;
    int tam_processo;

    // variaveis para manipulação das funções
    int tamanho_mf, tamanho_ms, tamanho_qm, tamanho_el;

    // variaveis para alocacao de memoria
    MP *mem_principal;
    MS *mem_secundaria;
    PG info_pagina;

    // configurando o espaco de memoria
    configuracoes(&tamanho_mf, &tamanho_ms, &tamanho_qm, &tamanho_el, info_pagina);

    // alocando a memoria necessaria
    mem_secundaria = inicializa_ms(tamanho_ms);
    mem_principal = inicializa_mp(tamanho_mf, tamanho_qm);

    // abrindo o arquivo
    FILE* fila_processos = fopen("processos.txt", "r");
    if(fila_processos == NULL){
        printf("Erro na leitura da fila de processos. \n");
        exit(1);
    }

    // readline do arquivo e execucao
    /*
    essa leitura vai funcionar?? dependendo de qual a Flag a quantidade de valores no input do arquivo
    será diferente ex:
    número-do-processo  P  endereço-lógico
    número-do-processo  W  endereço-lógico  valor
    */
    while(fscanf(fila_processos, "%s %i %d", nome_processo, acao, &tam_processo)){
        flags(acao, nome_processo, tam_processo, mem_secundaria, mem_principal);
    }
    
    // fechando o arquivo
    fclose(fila_processos);

    return 0;
}