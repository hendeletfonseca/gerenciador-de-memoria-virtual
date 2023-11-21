#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>
#include <math.h>

/* estrutura das variáveis */

struct pagina;

struct tabela_paginas;

struct processo;

struct memoria_secundaria;

void configuracoes(int *tam_mf, int *tam_ms, int *tam_pag, int *tam_qm,
 int *tam_end_logico, MP *m_principal, MS *m_secundaria, PG pag);