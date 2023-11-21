#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>
#include <math.h>

/* estrutura das variáveis */

typedef struct pagina {
    int *tam_pagina; 
    int *tam_endereco_virtual;
    int *endereco_virtual; // endereco da pag na memoria virtual
    P *processo_associado; // processo a qual a pg esta associada
} PG;

typedef struct tabela_paginas {
    int bit_p;
    int bit_m;
    int end_quadro; // endereço na memoria principal
    int tam_preenchido; // para saber se ja ultrapassou o tam da memoria principal ou nao
    struct tabela_paginas *prox; // estamos tratando como se fosse uma fila... 
} TP;

typedef struct processo {
    char *identificador; // nome do processo lido no arquivo 
    char *estado_processo; // informa em qual estado o processo esta: novo, pronto, bloqueado, executando, finalizado
    int *tam_imagem; // tamanho do processo
    TP *tab_paginas; // lista encadeada, vamos usar esse TP?
    struct processo *prox; // pois na ms tem uma lista de processos...
} P;

typedef struct memoria_principal {
    int tam_mp;
    int num_quadros;
    int *vetor_paginas;
    TP *fila_lru;
} MP;

typedef struct memoria_secundaria {
    int tam_ms;
    P *processos;
} MS;

/* funções de operação */
// amanda
void imprime_tabela_paginas(TP *tab_pags){

    printf("=======================\n");
    int i = 0;
    TP *aux = tab_pags;
    while(aux != NULL){
        printf("Lacuna %d: \n", i);
        printf("Bit de presença na memória principal: %d \n", tab_pags->bit_p);
        printf("Bit de modificação da página: %d \n", tab_pags->bit_m);
        printf("Endereço do quadro na memória principal: %d \n", tab_pags->end_quadro);
        printf("-------------------------\n");
        aux = aux->prox;
    }
}

// amanda
void imprime_estado_processo(P *processo){
    printf("Dados do processo %s: \n", processo->identificador);
    printf("----------------------\n");
    printf("Estado do processo: %s \n", processo->estado_processo);
    printf("Tamanho do processo: %d \n", processo->tam_imagem);
    printf("Tabela de páginas associada: \n");
    imprime_tabela_paginas(processo->tab_paginas);
    printf("\n");
}

// amanda
void configuracoes(int *tam_mf, int *tam_ms, int *tam_qm,
 int *tam_end_logico, PG pag) {

    *tam_qm = 0;
    *tam_mf = 0;

    printf("Digite o tamanho desejado para cada uma das opcoes abaixo \n");
    
    printf("1. Tamanho do quadro de memoria (valor inteiro em KB): \n");
    while(*tam_qm <= 0){
        scanf("%d", tam_qm);
    }
    *tam_qm *= 1024;

    printf("2. Tamanho da memoria fisica (Deve ser multiplo do tamanho do quadro: %d): \n", *tam_qm);
    do {
        if(*tam_mf) printf("Valor incorreto, deve ser multiplo de %d!", *tam_qm)
        scanf("%d", tam_mf);
    } while (*tam_mf % (*tam_qm) != 0);
    
    printf("3. Tamanho da memoria secundaria: \n");
    scanf("%d", tam_ms);

    printf("4. Tamanho em bits do endereço lógico: \n");
    scanf("%d", tam_end_logico);
    *tam_end_logico = pow(2, *tam_end_logico-3); // o que é isso?

    pag.tam_pagina = *tam_qm;
    pag.tam_endereco_virtual = *tam_end_logico;
}

// amanda
void flags(char flag_processo, char *nome_processo, int tam_processo, MS *m_secundaria, MP *m_principal){

    P *proc;

    // aqui aloca o processo se ele não existir, ou busca na memória caso já esteja lá
    proc = aloca_processo(m_secundaria, nome_processo);

    if(flag_processo == 'P'){
        imprime_estado_processo(proc); // antes da alteração
        instrucao_cpu();
        imprime_estado_processo(proc); // depois da alteração
    }
    if(flag_processo ==  'I'){
        //estado bloqueado a espera de E/S
        impressao_p(proc);
        instrucao_es();
        impressao_p(proc);
    }
    if(flag_processo == 'C'){
        impressao_p(proc);        
    }
    if(flag_processo == 'R'){
        //estado esperando estar na mp --> pronto --> executando 
        impressao_p(proc);
        leitura();
        impressao_p(proc);
    }
    if(flag_processo == 'W'){
        //estado esperando estar na mp --> pronto --> executando
        impressao_p(proc);
        escrita();
        impressao_p(proc);
    }
    if(flag_processo == 'T'){
        //estado final?? :)
        impressao_p(proc);
        halt();
        impressao_p(proc);
    }
    else {
        printf("Opção inválida. \n");
    }
}
/* operações das estruturas de dados - lru */


/* operações das estruturas de dados - memória secundária */

// amanda
MS *inicializa_ms(int tamanho){

    novo->tam_ms = tamanho;
    novo->processos = NULL;

    return novo;
}

/* operações das estruturas de dados - processo */

// amanda
P *busca_processo_mp(MP *m_principal, P *processo){

    // basicamente, se no primeiro end da tp do processo o bit p é 1, então está na mp
    if(processo->tab_paginas->bit_p == 1) {
        TP *aux = m_principal->fila_paginas;
        while(aux != NULL){
            if(aux->end_quadro == processo->tab_paginas->end_quadro) return aux;
            aux = aux->prox;
        }
    }
    return NULL;
}


// amanda
P *busca_processo_ms(MS *m_secundaria, char *nome_processo){

    P *aux = m_secundaria->processos;
    while(aux != NULL && strcmp(aux->identificador, nome_processo) != 0){
        aux = aux->prox;
    }
    return aux;
}

// amanda
P *aloca_processo(MS *m_secundaria, char *nome_processo, int tam_processo){

    P *aux;

    // checa se o processo já esta alocado na memória
    aux = busca_processo_ms(m_secundaria, nome_processo); // vai ter q trocar
    
    // se não estiver, aloca o processo na memória
    if(!aux){
    
        P *novo = (P*)malloc(sizeof(P));
        strcpy(novo->identificador, nome_processo);
        strcpy(novo->estado_processo, "Novo");
        novo->tam_imagem = tam_processo;
        novo->tab_paginas = inicia_tabela_paginas(novo, tam_processo);
        novo->prox = m_secundaria->processos;
        m_secundaria->processos = novo;

        return novo;
    }   

    return aux;
}

/* operações das estruturas de dados - tabela de páginas */

TP *inicia_tabela_paginas(P *processo, int tam_processo){
    // o uso da hash seria aqui, pois queremos quebrar o processo e preencher a tabela de paginas...
}

// amanda
// como é fila, insere no final
TP *insere_pagina(MP *m_principal, PG pagina, TP *tab, int p, int m, int end){

    TP *novo;

    novo = (TP*)malloc(sizeof(TP));
    novo->bit_p = p;
    novo->bit_m = m;
    novo->end_quadro = end;
    if(novo->tam_preenchido += pagina.tam_pagina <= m_principal->tam_mp) novo->tam_preenchido += pagina.tam_pagina;
    else lru(tab);

    if(!tab) return novo;
    
    TP *aux = tab;
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    aux->prox = novo;
    return tab;
}

// amanda
// e remove do início
TP *remove_pagina(TP *tab){
    if(!tab) return NULL;

    TP *aux = tab;

    tab = tab->prox;
    free(aux);
    return tab;
}

// amanda
TP *preenche_fila(MP *m_principal, P *processo, PG pagina){

    TP *aux;
    aux = busca_processo_mp(m_principal, processo);
    if(!aux){
        TP *aux_proc;
        aux = processo->tab_paginas;
        
        while(aux != NULL){
            m_principal->fila_paginas = insere_pagina(m_principal, pagina, aux_proc, aux_proc->bit_p, aux_proc->bit_m, aux_proc->end_quadro);
            aux_proc = aux_proc->prox;
        }
    }
    return aux;
}

/* operações das estruturas de dados - memória principal */
// amanda
MP *inicializa_mp(int tam_mf, int tam_qm){

    MP *novo;
    novo->tam_mp = tam_mf;
    novo->num_quadros = tam_mf / tam_qm;

    novo->vetor_paginas = (int*)malloc(sizeof(int) * novo->num_quadros);
    if(!novo->vetor_paginas) exit(1);

    novo->fila_lru = NULL;

    return novo;
}
