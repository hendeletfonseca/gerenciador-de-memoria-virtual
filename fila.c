#include <stdio.h>
#include <stlib.h>
//quero usar o tam da mp aqui, preciso importar funcoes.c?

//vou usar fila com vetor dinamico (array circular) pra facilitar a verificacao da mp cheia
//mas assim a gente gasta a mesma quantidade de memoria mesmo se a fila nao tiver cheia
//portanto, qual metodo usar??

typedef struct fila{//fila da mp
    int n, ini;
    int tam; // ou é *num_quadros ?? --gabi Valor de tam vai ser inicializado em inicializa_memoria_principal
    // PG* vet; //vetor dinamico de paginas 
    PG** vet; // Agora a fila armazena ponteiros para páginas -Bossan
} TF;

TF *cria (int tam_quadro){
    TF *f = (TF *)malloc(sizeof(TF));
    f->n = f->ini = 0;
    f->tam = tam_quadro; //botei mais coisa no cria -Bossan
    f->vet = (PG *)malloc(sizeof(PG) * tam_quadro);
    return f;
}

int incr (int ind, int n){
    return (ind + 1) % n;
}

int vazia (TF *f){
    return f→n == 0;
}

int cheia (TF *f){
//    if (f→n == f->tam) return 1;
//    return 0;
    return f->n == f->tam; //codigo mais limpo -Bossan
}


// int retira(TF *f){
//     if(vazia(f)) exit(1);
//     int resp = f→vet[f→ini];
//     f→ini = incr(f→ini, f->tam);
//     return resp;
// }
PG retira(TF *f) { // Obrigado GPT -Bossan
    if (vazia_fila(f)) {
        printf("Fila vazia.\n");
        exit(1);
    }

    PG pagina = f->vet[f->ini];
    f->ini = incr(f->ini, f->tam);
    f->n--;
    return pagina;
}

void libera(TF *f){
    free(f->vet);
    free(f);
}

void insere(TF *f, PG* pagina){
    // if(f→n == f->tam) exit(1);
    if (cheia(f)) {
        printf("Fila cheia.\n");
        exit(1);
    }
    int fim = (f→ini + f→n++) % f->tam;
    f→vet[fim] = pagina;
    f->n++;
}



void inicializa_memoria_principal(MP *memoria_principal) {
    int num_quadros = memoria_principal->num_quadros;
    memoria_principal->fila_paginas->n = memoria_principal->fila_paginas->ini = 0;
    memoria_principal->fila_paginas->tam = num_quadros;
    memoria_principal->fila_paginas->vet = (PG **)malloc(sizeof(*PG) * num_quadros);

    for (int i = 0; i < num_quadros; i++) {
        TP *pagina = &(memoria_principal->fila_paginas->vet[i]);
        pagina->bit_p = 0;
        pagina->bit_m = 0;
        pagina->end_quadro = i;
    }
}

PG busca_pagina_memoria_principal(MP *memoria_principal, int num_pagina) {
    TP *fila_paginas = memoria_principal->fila_paginas->vet;
    return fila_paginas[num_pagina];
}

void aloca_pagina_memoria_principal(MP *memoria_principal, PG pagina) {
    if (cheia(memoria_principal->fila_paginas)) {
        PG pagina_substituida = retira(memoria_principal->fila_paginas);
    }
    insere(memoria_principal->fila_paginas, pagina);
}

void inicializa_tabela_paginas(P *processo) {
    int num_paginas = processo->tam_imagem / processo->tab_paginas->tam_pagina;
    processo->tab_paginas = (TP *)malloc(sizeof(TP) * num_paginas);

    for (int i = 0; i < num_paginas; i++) {
        TP *pagina = &(processo->tab_paginas[i]);
        pagina->bit_p = 0;
        pagina->bit_m = 0;
        pagina->end_quadro = -1;
    }
}

TP busca_pagina_tabela(P *processo, int num_pagina) {
    TP *tabela_paginas = processo->tab_paginas;
    return tabela_paginas[num_pagina];
}

/* 
Funcoes de fila com lista encadeada:

typedef struct lse{
    int info;
    struct lse *prox;
} TLSE;

typedef struct fila{
    TLSE *ini, *fim;
} TF;

int vazia (TF *f){
return f->ini == NULL;
}

TF *cria (void){
    TF *f = (TF *) malloc(sizeof (TF));
    f→ini = f→fim = NULL;
    return f;
}

void insere(TF *f, int x){
    TLSE *novo = (TLSE *)malloc(sizeof(TLSE));
    novo→info = x;
    novo→prox = NULL;
    if (f→fim) f→fim→prox = novo;
    else f→ini = novo;
    f→fim = novo;
}

int retira(TF *f){
    if(vazia(p)) exit(1);
    int resp = f→ini→info;
    TLSE *q = f→ini;
    f→ini = f→ini→prox;
    if (!f→ini) f→fim = NULL;
    free(q);
    return resp;
}

void libera(TF *f){
    TLSE *q = f→ini;
    while(q){
        TLSE *t = q;
        q = q→prox;
        free(t);
    }
    free(f);
} 
*/

