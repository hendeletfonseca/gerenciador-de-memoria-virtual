#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>
#include "estruturas.c"
#include "util.c"

void configuracoes(int *tam_mf, int *tam_ms, int *tam_pag, int *tam_qm, int *tam_end_log);
void readInputLine(FILE* arquivo);

int main(void) {
    int size_memoria_principal, size_memoria_secundaria, size_pagina, size_quadro, size_end_log;
    configuracoes(&size_memoria_principal, &size_memoria_secundaria, &size_pagina, &size_quadro, &size_end_log);

    // inicializa quadros
    int qtd_quadros = size_memoria_principal / size_quadro;
    Quadro *quadros = (Quadro*)malloc(qtd_quadros * sizeof(Quadro));
    for (int i = 0; i < qtd_quadros; i++) {
        quadros[i].dados = (int*)malloc(size_quadro * sizeof(int));
    }

    // inicializa memoria principal
    Memoria_principal *memoria_principal = (Memoria_principal*)malloc(sizeof(Memoria_principal));
    memoria_principal->num_quadros = qtd_quadros;
    memoria_principal->quadros = quadros;

    // inicializa tabela de paginas
    Tabela_de_paginas *tabela_de_paginas = (Tabela_de_paginas*)malloc(sizeof(Tabela_de_paginas));
    tabela_de_paginas->num_paginas = 0;
    tabela_de_paginas->paginas = NULL;

    FILE *arquivo = fopen("processos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    } else
    {
        readInputLine(arquivo);
    }


    return 0;
}

void configuracoes(int *tam_mf, int *tam_ms, int *tam_pag, int *tam_qm, int *tam_end_logico) {
   
    int aux;

    printf("Digite o tamanho desejado para cada uma das opcoes: \n");
    
    printf("1. Tamanho do quadro de memoria (valor inteiro em KB): \n");
    scanf("%d", &aux);
    aux = aux * 1024;
    (*tam_qm) = aux;

    printf("2. Tamanho da memoria fisica (Deve ser multiplo do tamanho do quadro): \n");
    do {
        scanf("%d", &aux);
    } while (aux % (*tam_qm) != 0);
    scanf("%d", &aux);
    (*tam_mf) = aux;
    
    printf("3. Tamanho da memoria secundaria: \n");
    scanf("%d", &aux);
    (*tam_ms) = aux;
    
    printf("4. Tamanho da pagina de um processo (valor inteiro em KB): \n");
    scanf("%d", &aux);
    aux = aux * 1024;
    (*tam_pag) = aux;

    printf("5. Tamanho do endereco logico: \n");
    scanf("%d", &aux);
    aux = (sizeof(aux)) * 8;
    (*tam_end_logico) = aux;
    //Endereço Lógico composto por numeros de paginas + tamanho da pagina
    //Com tamanho da pagina do item 4 e mais o tamanho do endereço logico temos o numero de paginas.
}

void readInputLine(FILE* arquivo) {
    static char line[256];
    // Ler a próxima linha do arquivo
    if (fgets(line, sizeof(line), arquivo) == NULL) return;

    int id_proc;
    char flag;

    int i = 0;
    while (line[i] != '\0' && line[i] != ' ') {
        i++;
    }

    char id_str[i + 1];
    for (int j = 0; j < i; j++) {
        id_str[j] = line[j];
    }
    id_str[i] = '\0';
    i++;

    // Converter a nova string para int
    id_proc = atoi(id_str);

    flag = line[i++];

    switch (flag) {
        case 'P':
            char num_char[50];
            int j = 0;
            while (line[i] != '\0' && line[i] != ' ') {
                num_char[j++] = line[++i];
            }
            char end_log[j + 1];
            for (int k = 0; k < j; k++) {
                end_log[k] = num_char[k];
            }
            end_log[j] = '\0';

            int end_logico = atoi(end_log);
            break;
        
        case 'I':
            break;

        case 'R':
            break;

        case 'W':
            break;

        case 'C':
            break;

        case 'T':
            break;

        default:
            break;
    }

}