#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>
#include <math.h>
#include "fila.c"

/* estrutura das variáveis*/

typedef struct pagina { //precisa mesmo ser ponteiro isso aqui?
    int *tam_pagina; 
    int *tam_endereco_virtual;
    int *endereco_virtual; // endereco da pag na memoria virtual
    P *processo_associado; // processo a qual a pg esta associada
} PG;

typedef struct tabela_paginas {
    //PG *pagina; -----> endereço virtual 
    int bit_p; // bit de presenca
    int bit_m; // bit de modificacao
    int end_quadro; // endereco da pagina na memoria principal -- fisico
} TP;

typedef struct processo {
    // char identificador[2];
    // char estado_processo[10];
    char *identificador; // nome do processo lido no arquivo 
    char *estado_processo; // informa em qual estado o processo esta: novo, pronto, bloqueado, executando, finalizado
    int *tam_imagem; // tamanho do processo
    //int *endereco_fisico; precisa disso aqui? uma vez q a propria variavel processo ja guarda seu endereço
    TP *tab_paginas; //vetores dinamicos, estrutura usada
    int tam_tabela_paginas; // tamanho da tabela de paginas // pq isso???
} P;

typedef struct memoria_principal {
    int *tam_mp;
    int *num_quadros;
    TF *quadro_paginas; // fila para facilitar a implementacao da LRU
} MP;

typedef struct memoria_secundaria {
    int tam_ms;
    P *processos; // todos os processos estarao aqui, É UMA ESTRUTURA DE DADOS!!!!
} MS;

/*funções utilizadas*/

// amanda
void configuracoes(int *tam_mf, int *tam_ms, int *tam_pag, int *tam_qm,
 int *tam_end_logico, MP *m_principal, MS *m_secundaria, PG *pag) {
   
    // int aux = 0; não precisa de aux
    *tam_qm = 0;
    *tam_mf = 0;

    printf("Digite o tamanho desejado para cada uma das opcoes abaixo \n");
    
    printf("1. Tamanho do quadro de memoria (valor inteiro em KB): \n");
    // scanf("%d", &aux);     tirei a necessidade do aux, verifica se está certo -Bossan
    // (*tam_qm) = aux* 1024;
    while(*tam_qm <= 0){
        scanf("%d", tam_qm);
    }
    tam_qm*=1024;

    printf("2. Tamanho da memoria fisica (Deve ser multiplo do tamanho do quadro: %d): \n", *tam_qm);
    // do {                                 mesma coisa do anterior -Bossan
    //    scanf("%d", &aux);
    // } while (aux % (*tam_qm) != 0);
    // scanf("%d", &aux);
    // (*tam_mf) = aux;
    do {
        if(*tam_mf) printf("Valor incorreto, deve ser multiplo de %d!", *tam_qm)
        scanf("%d", tam_mf);
    } while (*tam_mf % (*tam_qm) != 0);
    
    printf("3. Tamanho da memoria secundaria: \n");
    // scanf("%d", &aux);
    // (*tam_ms) = aux;
    scanf("%d", tam_ms);

    printf("4. Tamanho da pagina de um processo (valor inteiro em KB): \n");
    // scanf("%d", &aux);
    // (*tam_pag) = aux* 1024;
    while(tam_pag <= 0){
        scanf("%d", tam_pag);
    }
    tam_pag*=1024;

    //printf("5. Tamanho do endereco logico: \n");
    printf("5. Tamanho em bits do endereço lógico: \n");
    scanf("%d", tam_end_logico);
    *tam_end_logico = pow(2, *tam_end_logico-3); // o -3 é para converter em bytes
    //Endereço Lógico composto por numeros de paginas + tamanho da pagina
    //Com tamanho da pagina do item 4 e mais o tamanho do endereço logico temos o numero de paginas.

    // guardando as informações nas estruturas
    m_principal->num_quadros = tam_qm;
    m_principal->tam_mp = tam_mf;
    m_secundaria->tam_ms = tam_ms;
    pag->tam_pagina = tam_pag;
    pag->tam_endereco_virtual = tam_end_logico;
}

// amanda
P *inicia_processo(MS *m_secundaria, char *nome_processo, int tam_processo){
    //quando inicado entao o processo vai direto pra mem secundaria ent? nao a mp?
    P *aux = NULL;
    bool res = false;

    // checa se o processo ja esta alocado na memoria
    while(P *p= m_secundaria->processos; p != NULL; p = p->proximo){
        if(strcmp(p->identificador, nome_processo) == 0){
            res = true;
            aux = p;
            break;
        }
        /*pula pro proximo*/
    }
    if(!res){
        P *novo;

        novo = (P*)malloc(tam_processo * sizeof(P)); // tam_processo ja estara em bytes 
        strcpy(nome_processo, novo->identificador);
        strcpy(novo->estado_processo, "Novo");
        novo->tam_imagem = tam_processo;
        /*endereço fisico: nao sei ainda
        tab de paginas: quebrar o processo em paginas e alocar a memoria necessaria, tem q contar
        qual o tamanho necessario p isso*/ 
        novo->proximo = m_secundaria->processos;
        m_secundaria->processos = novo;
        
        return novo;
    }
    return aux;
}

// amanda
void impressao_tp(TP *tabela_proc, int tam_tabela){
    //tabela de paginas sera um vetor? raio aqui Duvida
    /*
    Se for:
    for (int i = 0; i < tam_tabela; i++) {
        printf("Lacuna %d: \n", i);
        printf("Bit de presença na memória principal: %d \n", tabela_proc[i].bit_p);
        printf("Bit de modificação da página: %d \n", tabela_proc[i].bit_m);
        printf("Endereço do quadro na memória principal: %d \n", tabela_proc[i].end_quadro);
    } 
    seria o jeito de manipular nao?
    */
    
    //que tal printar igual tabela? (com linhas pras paginas e colunas pros atributos)
    printf("=======================\n");
    for(int i = 0; i < tam_tabela; i++){
        printf("Lacuna %d: \n", i);
        printf("Bit de presença na memória principal: %d \n", tabela_proc->bit_p);
        printf("Bit de modificação da página: %d \n", tabela_proc->bit_m);
        printf("Endereço do quadro na memória principal: %d \n", tabela_proc->end_quadro);
    }
    printf("=======================\n");
}

// amanda
void impressao_p(P *proc){ //precisa disso?

    printf("Dados do processo %s: \n", proc->identificador);
    printf("----------------------\n");
    printf("Estado do processo: %s \n", proc->estado_processo);
    printf("Tamanho do processo: %d \n", proc->tam_imagem);
    printf("Tabela de páginas associada: \n");
    impressao_tp(proc->tab_paginas, proc->tam_tabela_paginas);
    printf("\n");
}

int calcula_enderecamento(){ // fiz a funcao MMU pra fazer isso, esta no file LRU.c sinto sua falta 

    /*
    endereço Lógico é:
        (numero de páginas)*(tamanho da página + deslocamento)
        acho que é: (numero da pag * tamanho da pag) + delocamento na pag (gabi)
    endereço Físico é:
        (numero de quad)*(tamanho da página + deslocamento)
        acho que é: (numero do quad * tamanho da página) + deslocamento no quadro
    */
}

void leitura(){ //em arquivo?
    // le o endereco e escreve, deixando p dps so pq n sei fazer msm
}

void escrita(){ //em arquivo?
    // mapeia o endereco e escreve, deixando p dps so pq n sei fazer msm
}

void halt(){
    // remove o processo da fila de processos, ou seja, mata o processo
}

void instrucao_cpu(){
    // instrucao a ser executada pela cpu
}

void instrucao_es(){
    // instrucao de entrada/saida 
}

void ver_mp(MP *memoria_principal){
    int num_quadros = *(memoria_principal->num_quadros);
    TP *quadro_paginas = memoria_principal->quadro_paginas;

    printf("Estado da Memória Principal:\n");
    printf("Número total de quadros: %d\n", num_quadros);
    
    for (int i = 0; i < num_quadros; i++) {
        printf("Quadro %d:\n", i);
        printf("  Bit de Presença: %d\n", quadro_paginas[i].bit_p);
        printf("  Bit de Modificação: %d\n", quadro_paginas[i].bit_m);
        printf("  Endereço do Quadro na Memória Principal: %d\n", quadro_paginas[i].end_quadro);
        printf("-----------------------\n");
    }
}
void ver_ms(MS *memoria_secundaria){
    int tam_ms = memoria_secundaria->tam_ms;
    P *processos = memoria_secundaria->processos;

    printf("Estado da Memória Secundária:\n");
    printf("Tamanho total da Memória Secundária: %d\n", tam_ms);

    P *atual = processos;
    while (atual != NULL) {
        printf("Processo %s:\n", atual->identificador);
        printf("  Estado do Processo: %s\n", atual->estado_processo);
        printf("  Tamanho do Processo: %d\n", atual->tam_imagem);
        // Adicione mais informações conforme necessário
        printf("-----------------------\n");

        atual = atual->proximo;
    }
}
void halt(P *proc, char *acao_processo, int *endereco){ 

    /*
    li nos slides q o termino é executado a partir da instrucao halt ai mudei 
    o nome da funcao de termino pra halt pra ficar bonitinho (gabi)

    pega o endereço e busca na tabela de paginas
    checa se esta na memoria principal
    se sim, remove da memoria principal
    remove da tabela de paginas
    */
} 

// amanda --raio mudou strcmp para comparar caracter a caracter nao necessario em sercmp
// flag_processo ser apenas um caracter
void flags(char *flag_processo, char *nome_processo, int tam_processo, MS *m_secundaria){

    P *proc, aux;
    bool res = false;

    // checa se o processo esta na memoria e acessa o ponteiro dele com o nome da flag do processo
    while(m_secundaria->processos != NULL){
        /*busca o processo na memoria*/
        if(strcmp(m_secundaria->processos->identificador, nome_processo) == 0){
            res = true;
            break;
        }
    }
    if(res) proc = m_secundaria->processos;
    else proc = NULL;


    // atualizacoes do processo sao na funcao de flag

    if(flag_processo == 'P'){
        //estado executando
        impressao_p(proc); // antes da alteração 
        instrucao_cpu();
        impressao_p(proc); // depois da alteração
    }
    if(flag_processo ==  'I'){
        //estado bloqueado a espera de E/S
        impressao_p(proc);
        instrucao_es();
        impressao_p(proc);
    }
    if(flag_processo == 'C'){
        //estao novo
        aux = inicia_processo(m_secundaria, nome_processo, tam_processo);
        proc = aux;
        //m_secundaria->processos = proc;
        /*qnd a estrutura de dados estiver definida vem aq e troca, so 
        ta aqui pra nao esquecer */
        impressao_p(proc);        
    }
    if(flag_processo == 'R'){
        //estado esperando estar na mp --> pronto --> executando 
        impressao_p(proc);
        leitura();
        impressao_p(proc);
    }
    if(flag_processo == 'W'){
        //estado esperando estar na mp --> pronto --> executando
        impressao_p();
        escrita();
        impressao_p(proc);
    }
    if(flag_processo == 'T'){
        //estado final?? :)
        impressao_p(proc);
        halt();
        impressao_p(proc);
    }
    else {
        printf("Opção inválida. \n");
    }
}