#include <stdio.h>
#include <stlib.h>

//rascunho pra uma possivel ms em lista encadeada
typedef struct lse{
    int info;
    struct lse *prox;
} TLSE;

TLSE* inicializa(void){
    return NULL;
}

//insere no primeiro lugar vago? poderia ter uma funcao pra isso (caso a lista esteja lotada)
TLSE* insere_ini(TLSE *l, int x){
    TLSE * novo = (TLSE*)malloc(sizeof(TLSE));
    novo->info = x;
    novo->prox = l;
    return novo;
}

void imprime(TLSE *l){
    printf("[ ");
    while (l!=NULL){
        printf("[%2d|  ]->",l->info);
        l=l->prox;
    }
    printf(" NULL ]\n");
}

//Busca primeira vez de x
TLSE* busca(TLSE *l, int x){
    TLSE *resp = l;
    while ((resp)&&(resp->info!=x)){
        resp = resp->prox;
    }
    return resp;
}

TLSE* retira(TLSE *l, int x){
    TLSE * ant = NULL, *p = l;
    while ((p!=NULL)&&(p->info!=x)){
        ant = p;
        p = p->prox;
    }
    if (!p) return l;
    if(!ant){
        l = l->prox;
    }
    else{
        ant->prox = p->prox;
    }
    free(p);
    return l;   
}

void libera(TLSE*l){
    TLSE * p;
    while (l!=NULL){
        p = l;
        l = l->prox;
        free(p);
    }
}

TLSE * ultimo_rec(TLSE *l){
    if (!l) return l;
    if (l->prox){
        return ultimo_rec(l->prox);  
    }
    else{
        return l;
    }
}