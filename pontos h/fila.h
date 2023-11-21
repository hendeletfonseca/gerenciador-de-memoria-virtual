#include <stdio.h>
#include <stlib.h>

struct fila;

TF *cria (int tam_quadro);

int incr (int ind, int n);

int vazia (TF *f);

int cheia (TF *f);

PG retira(TF *f);

void libera(TF *f);

void insere(TF *f, PG* pagina);

void inicializa_memoria_principal(MP *memoria_principal);

PG busca_pagina_memoria_principal(MP *memoria_principal, int num_pagina);

void aloca_pagina_memoria_principal(MP *memoria_principal, PG pagina);

void inicializa_tabela_paginas(P *processo);

TP busca_pagina_tabela(P *processo, int num_pagina);
