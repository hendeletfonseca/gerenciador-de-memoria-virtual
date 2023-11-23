#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>
#include <math.h>

typedef struct tabela_paginas {
    int bit_p;
    int bit_m;
    int end_quadro; // endereço na memoria principal
    //achoq nao precisa de tam preenchido  kskskssksk
    struct tabela_paginas *prox; // estamos tratando como se fosse uma lista encadeada... 
} TP;

typedef struct least_recently_used {
    int end;
    struct least_recently_used *prox;
} LRU;
typedef struct processo {
    char *identificador; // nome do processo lido no arquivo 
    char *estado_processo; // informa em qual estado o processo esta: novo, pronto, bloqueado, executando, finalizado
    int *tam_imagem; // tamanho do processo
    TP *tab_paginas; // lista encadeada, vamos usar esse TP?
    struct processo *prox; // pois na ms tem uma lista de processos...
} P;

typedef struct pagina {
    int *tam_pagina; 
    int *tam_endereco_virtual;
    int *endereco_virtual; // endereco da pag na memoria virtual
    P *processo_associado; // processo a qual a pg esta associada
} PG;
typedef struct memoria_principal {
    int tam_mp;
    int num_quadros;
    int *pags_refs;
    LRU *fila_lru; //na pratica isso aqui nao existe :))))
    TP *tabela_paginas;
} MP;

typedef struct memoria_secundaria {
    int tam_ms;
    P *processos;
} MS;

P *aloca_processo(MS *m_secundaria, char *nome_processo, int tam_processo);
void configuracoes(int *tam_mf, int *tam_ms, int *tam_qm, int *tam_end_logico, PG pag);
void instrucao_cpu();
void instrucao_es();
void impressao_p(P *proc);
void leitura();
void escrita();
void flags(char flag_processo, char *nome_processo, int tam_processo, MS *m_secundaria, MP *m_principal);

//inicializa estruturas
MP *inicializa_mp(int tam_mf, int tam_qm);
int busca_pagina_referenciada(MP *m_principal, int end);
void insere_pagina(MP *m_principal, P *processo, int end);

MS *inicializa_ms(int tamanho);
void inicia_tabela_de_paginas_proc(P *processo, int size_pag);


 //qual a diferenca pra minha e oq faz? (gabi)
void busca_pagina(P *processo,  int end_logico, int qtd_bits_endereco_logico); //(a minha) --gabi sksksks

void carrega_pag_mp(P* processo, PG* pagina, MP* m_principal);

LRU *retira_fila(LRU *fila);

P *busca_processo_ms(MS *m_secundaria, char *nome_processo);

LRU *busca_fila(LRU *fila, int end);
void moverParaFinal(LRU *lista, int val);

LRU *insere_fila(LRU *fila, int end);
LRU *insere_fila_parte2(LRU *fila, int end);
int LRU_cheia(LRU *fila, int tam_max)

TP *insere_pagina(MP *m_principal, PG pagina, TP *tab, int p, int m, int end);
TP *remove_pagina(TP *tab);  //na tabela de pag? nao faz sentido pra mim

TP *preenche_fila(MP *m_principal, P *processo, PG pagina); //???

int n_pag (int endereco_logico, int page_size, int qtd_bits_endereco_logico);
int MMU(int endereco_logico, int page_size, int qtd_bits_endereco_logico, TP *tabela);
int casas_decimais_em_binario(int n);
void binario(int n, int *binario, int tamanho);
int decimal(int *binario, int tamanho);
void halt_MP(MP *mp, P *proc);
void halt_MS(MS *ms, P *proc);
void halt(P *proc, MP *mp, MS *ms );

void imprime_tabela_paginas(TP *tab_pags);
void imprime_estado_processo(P *processo);
void ver_mp(MP *mp);
void ver_ms(MS *memoria_secundaria);
void swapper(LRU *lru, TP *tab_paginas);