#include <stdio.h>
#include <stlib.h>
//quero usar o tam da mp aqui, preciso importar funcoes.c?

//vou usar fila com vetor dinamico (array circular) pra facilitar a verificacao da mp cheia
//mas assim a gente gasta a mesma quantidade de memoria mesmo se a fila nao tiver cheia
//portanto, qual metodo usar??

typedef struct fila{
    int n, ini;
    int tam = m_principal->num_quadros; // ou é *num_quadros ?? --gabi
    PG* vet; //vetor dinamico de paginas 
} TF;

TF *cria (void){
    TF *f = (TF *)malloc(sizeof(TF));
    f->n = f->ini = 0;
    return f;
}

int incr (int ind, int n){
    return (ind + 1) % n;
}

int vazia (TF *f){
    return f→n == 0;
}

int cheia (TF *f){
   if (f→n == f->tam) return 1;
   return 0;
}

int retira(TF *f){
    if(vazia(f)) exit(1);
    int resp = f→vet[f→ini];
    f→ini = incr(f→ini, f->tam);
    return resp;
}

void libera(TF *f){
    free(f->vet);
    free(f);
}

void insere(TF *f, PG* pagina){
    if(f→n == f->tam) exit(1);
    int fim = (f→ini + f→n++) % f->tam;
    f→vet[fim] = pagina;
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

