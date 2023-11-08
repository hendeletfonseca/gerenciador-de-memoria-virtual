#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

/* estrutura das variáveis*/

typedef struct pagina {
    int tam_pagina; 
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
    int tam_mp;
    int num_quadros;
    TP *quadro_paginas; // isso aq eh uma fila(?)

} MP;

typedef struct memoria_secundaria {
    int tam_ms;
    P *processos; // todos os processos estarao aqui
}

/*funções utilizadas*/