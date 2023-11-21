#include <stdio.h>
#include <stdlib.h>

typedef struct memoria_principal {
    PG *pagina;
    int endereco;
    struct memoria_principal *prox;
} MP;

MP *mp_inicializa() {
    return NULL;
}

MP *get_pagina()

MP *mp_insere_inicio(MP *l, PG *p) {
    MP *novo = (MP*)malloc(sizeof(MP));
    novo->pagina = p;
    novo->prox = l;
    return novo;
}

MP *mp_insere_final(MP *l, PG *p) {
    MP *novo = mp_insere_inicio(NULL, p);
    if (l == NULL) {
        return novo;
    }
    MP *aux = l;
    while (aux->prox != NULL) {
        aux = aux->prox;
    }
    aux->prox = novo;
    return l;
}

void mp_libera(MP *l) {
    MP *p = l, *t;
    while (p != NULL) {
        t = p;
        p = p->prox;
        free(t);
    }
}