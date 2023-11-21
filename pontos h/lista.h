#include <stdio.h>
#include <stlib.h>

struct lse;

TLSE* inicializa(void){
    return NULL;
}

TLSE* insere_ini(TLSE *l, int x);

void imprime(TLSE *l);

TLSE* busca(TLSE *l, int x);

TLSE* retira(TLSE *l, int x);

void libera(TLSE*l);

TLSE * ultimo_rec(TLSE *l);