#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>

/* estrutura das variáveis*/

typedef struct pagina {
    int *tam_pagina; 
    int *tam_endereco_virtual;
    int *endereco_virtual; // endereco da pag na memoria virtual
    P *processo_associado; // processo a qual a pg esta associada
} PG;

typedef struct tabela_paginas {
    //PG *pagina; -----> endereço virtual 
    int bit_p; // bit de presenca
    int bit_m; // bit de modificacao
    int end_quadro; // endereco da pagina na memoria principal
} TP;

typedef struct processo {
    char *identificador; // nome do processo lido no arquivo
    char *estado_processo; // informa em qual estado o processo esta: novo, pronto, bloqueado, executando, finalizado
    int *tam_imagem; // tamanho do processo
    int *endereco_fisico; // precisa disso aqui? uma vez q a propria variavel processo ja guarda seu endereço
    TP *tab_paginas; // tabela de paginas de um respectivo processo (qual estrutura de dados sera usada para a tabela de paginas?)
} P;

typedef struct memoria_principal {
    int *tam_mp;
    int *num_quadros;
    TP *quadro_paginas; // isso aq eh uma fila(?)
} MP;

typedef struct memoria_secundaria {
    int tam_ms;
    P *processos; // todos os processos estarao aqui, É UMA ESTRUTURA DE DADOS!!!!
} MS;

/*funções utilizadas*/

// amanda
void configuracoes(int *tam_mf, int *tam_ms, int *tam_pag, int *tam_qm,
 int *tam_end_logico, MP *m_principal, MS *m_secundaria, PG *pag) {
   
    int aux;

    printf("Digite o tamanho desejado para cada uma das opcoes: \n");
    
    printf("1. Tamanho do quadro de memoria (valor inteiro em KB): \n");
    scanf("%d", &aux);
    aux = aux * 1024;
    (*tam_qm) = aux;

    printf("2. Tamanho da memoria fisica (Deve ser multiplo do tamanho do quadro): \n");
    do {
        scanf("%d", &aux);
    } while (aux % (*tam_qm) != 0);
    scanf("%d", &aux);
    (*tam_mf) = aux;
    
    printf("3. Tamanho da memoria secundaria: \n");
    scanf("%d", &aux);
    (*tam_ms) = aux;
    
    printf("4. Tamanho da pagina de um processo (valor inteiro em KB): \n");
    scanf("%d", &aux);
    aux = aux * 1024;
    (*tam_pag) = aux;

    printf("5. Tamanho do endereco logico: \n");
    scanf("%d", &aux);
    aux = (sizeof(aux)) * 8;
    (*tam_end_logico) = aux;
    //Endereço Lógico composto por numeros de paginas + tamanho da pagina
    //Com tamanho da pagina do item 4 e mais o tamanho do endereço logico temos o numero de paginas.

    // guardando as informações nas estruturas
    m_principal->num_quadros = tam_qm;
    m_principal->tam_mp = tam_mf;
    m_secundaria->tam_ms = tam_ms;
    pag->tam_pagina = tam_pag;
    pag->tam_endereco_virtual = tam_end_logico;
}

// amanda
P *inicia_processo(char *nome_processo, int tam_processo){
   
    P *novo;

    novo = (*P)malloc(tam_processo*sizeof(P)); // tam_processo ja estara em bytes 
    strcpy(nome_processo, novo->identificador);
    strcpy(novo->estado_processo, "Novo");
    novo->tam_imagem = tam_processo;
    /*endereço fisico: nao sei ainda
    tab de paginas: quebrar o processo em paginas e alocar a memoria necessaria, tem q contar
    qual o tamanho necessario p isso*/ 
    return novo;
}

void impressao(P *proc){

}

void leitura(){
    // le o endereco e escreve, deixando p dps so pq n sei fazer msm
}

void escrita(){
    // mapeia o endereco e escreve, deixando p dps so pq n sei fazer msm
}

void termino(){
    // remove o processo da fila de processos, ou seja, mata o processo
}

void instrucao_cpu(){
    // instrucao a ser executada pela cpu
}

void instrucao_es(){
    // instrucao de entrada/saida 
}

void ver_mp(){
    
}
void ver_ms(){
    
}
void termino(){

} 
void instrucao_cpu (){

} 
void instrucao_es(){

}

// amanda --raio mudou strcmp para comparar caracter a caracter nao necessario em sercmp
// flag_processo ser apenas um caracter
void flags(P *proc, char *flag_processo, char *nome_processo, int tam_processo, MS *m_secundaria){

    P *novo;

    // atualizacoes do processo sao na funcao de flag

    if(flag_processo == 'P'){
        impressao();
        instrucao_cpu();
        impressao();
    }
    if(flag_processo ==  'I'){
        impressao();
        instrucao_es();
        impressao();
    }
    if(flag_processo == 'C'){
        novo = inicia_processo(nome_processo, tam_processo);
        proc = novo;
        //m_secundaria->processos = proc;
        /*qnd a estrutura de dados estiver definida vem aq e troca, so 
        ta aqui pra nao esquecer */
        impressao();        
    }
    if(flag_processo == 'R'){
        impressao();
        leitura();
        impressao();
    }
    if(flag_processo == 'W'){
        impressao();
        escrita();
        impressao();
    }
    if(flag_processo == 'T'){
        impressao();
        termino();
        impressao();
    }
    else {
        printf("Opção inválida. \n");
    }
}
/*
P -  instrução a ser executada pela CPU
I -  instrução de I/O
C -  criação (submissão de um processo)
R - pedido de leitura em um endereço lógico
W - pedido de escrita em um endereço lógico de um dado valor
T - terminação de processo
*/