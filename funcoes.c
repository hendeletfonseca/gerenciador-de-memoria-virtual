#include "funcoes.h"

/* funções de operação */
// amanda
void configuracoes(int *tam_mf, int *tam_ms, int *tam_qm, int *tam_end_logico, PG pag) {

    *tam_qm = 0;
    *tam_mf = 0;

    printf("Digite o tamanho desejado para cada uma das opcoes abaixo \n");
    
    printf("1. Tamanho do quadro de memoria (valor inteiro em KB): \n"); //criar opcao pra ser MB ou GB
    while(*tam_qm <= 0){
        scanf("%d", tam_qm);
    }
    *tam_qm *= 1024;

    printf("2. Tamanho da memoria fisica (Deve ser multiplo do tamanho do quadro: %d): \n", *tam_qm);
    do {
        if(*tam_mf) printf("Valor incorreto, deve ser multiplo de %d!", *tam_qm)
        scanf("%d", tam_mf);
    } while (*tam_mf % (*tam_qm) != 0);
    
    printf("3. Tamanho da memoria secundaria: \n");
    scanf("%d", tam_ms);

    printf("4. Tamanho em bits do endereço lógico: \n");
    scanf("%d", tam_end_logico);
    *tam_end_logico = pow(2, *tam_end_logico-3); // o que é isso?

    pag.tam_pagina = *tam_qm;
    pag.tam_endereco_virtual = *tam_end_logico;
}

// amanda
void flags(char flag_processo, char *nome_processo, int tam_processo, MS *m_secundaria, MP *m_principal){

    P *proc;

    // aqui aloca o processo se ele não existir, ou busca na memória caso já esteja lá
    proc = aloca_processo(m_secundaria, nome_processo);

    if(flag_processo == 'P'){
        imprime_estado_processo(proc); // antes da alteração
        instrucao_cpu();
        imprime_estado_processo(proc); // depois da alteração
    }
    if(flag_processo ==  'I'){
        //estado bloqueado a espera de E/S
        impressao_p(proc);
        instrucao_es();
        impressao_p(proc);
    }
    if(flag_processo == 'C'){
        inicia_processo()
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
        impressao_p(proc);
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

/* operações das estruturas de dados - memória principal */
// amanda
MP *inicializa_mp(int tam_mf, int tam_qm){

    MP *novo;
    novo->tam_mp = tam_mf;
    novo->num_quadros = tam_mf / tam_qm;

    // aqui aloca o vetor de paginas referenciadas e inicializa ele
    novo->pags_refs = (int*)malloc(sizeof(int) * novo->num_quadros);
    if(!novo->pags_refs) exit(1);
    for(int i = 0; i < novo->num_quadros; i++){
        novo->pags_refs[i] = -1;
    }

    novo->fila_lru = NULL;

    novo->tabela_paginas = NULL;

    return novo;
}

// amanda
int busca_pagina_referenciada(MP *m_principal, int end){
    
    for(int i = 0; i < m_principal->num_quadros; i++){
        if(m_principal->pags_refs[i] == end) return 1;
    }
    return 0;
}

// amanda
void insere_pagina(MP *m_principal, P *processo, int end){

    // aqui insere no vetor de paginas
    if(!busca_pagina_referenciada(m_principal, end)){
        for(int i = 0; i < m_principal->num_quadros; i++){
            if(m_principal->pags_refs[i] == -1){
                m_principal->pags_refs[i] = end;
                break;
            }
        }
    }

    // aqui insere a tabela de pags do processo à lista de tabela de pags
    // trocar a estrutura
    TP *novo;
    novo = (*TP)malloc(sizeof(TP) * );

    // aqui insere na fila de paginas ja tratando o caso da pagina ja estar referenciada
    m_principal->fila_lru = insere_fila(m_principal->fila_lru, end);

}

/* operações das estruturas de dados - memória secundária */
// amanda
MS *inicializa_ms(int tamanho){

    novo->tam_ms = tamanho;
    novo->processos = NULL;

    return novo;
}

/* operações das estruturas de dados - tabela de páginas */

TP *inicia_tabela_paginas(P *processo, int tam_processo){
    // RAIO
}

// amanda
int busca_pagina_referenciada(MP *m_principal, int end){
    
    for(int i = 0; i < m_principal->num_quadros; i++){
        if(m_principal->pags_refs[i] == end) return 1;
    }
    return 0;
}

/* operações das estruturas de dados - processo */
// gabi
void busca_pagina(P *processo, int end_logico){  //pra implementar instrucao e tals
//em vez de retornar valor, pode só printar as saídas. importante calcular end_fisico pra isso

    // encontra a pag, ve na tp se ta em mp, se sim otimo e se nao carrega_pag_mp()
    TP * tab_paginas = processo->tabela_paginas;

    //usar conversao do hendel pra encontrar aqui o numero da pagina igualar a k;
    int i = 0;
    while (while i < k){
        tab_paginas = tab_paginas->prox;
    }

    if (tab_paginas->bit_p == 1){
        printf("Página buscada já está da MP"); //pode  fazer instrucao, escrita e leitura;
        //calculo do hendel pra achar o numero do quadro q a pag ta pra retornar valor se quiser;
    }
    else{
        carrega_pag_mp();
    }
}

//gabi tem q mexer aq
void carrega_pag_mp(P* processo, PG* pagina, MP*m_principal){ 

    //processo esta esperando (Novo ou bloqueado)
    int *mp = m_principal->pags_refs[]; //assim q usa ponteiro? sksksks n lembro

    if (!cheia(mp)){ //Caso 1: MP nao esta cheia -- pagina é alocada
        insere(mp, pagina); 
    }
    else{ //Caso 2: A MP esta cheia e aplicaremos a política de substituicao LRU
        printf("A MP está cheia, useremos a política de substituição LRU para carregar a imagem na MP")
        retira(mp);
        insere(mp, pagina);
    }

    printf("A página da imagem do processo X foi carregada para a MP com sucesso\n") //substituir X
    //estado do processo passa a ser pronto
    processo->estado = 'Pronto'
    printf("O processo passou para o estado 'Pronto'\n")
}

// amanda
P *busca_processo_ms(MS *m_secundaria, char *nome_processo){

    P *aux = m_secundaria->processos;
    while(aux != NULL && strcmp(aux->identificador, nome_processo) != 0){
        aux = aux->prox;
    }
    return aux;
}

// amanda
P *aloca_processo(MS *m_secundaria, char *nome_processo, int tam_processo){

    P *aux;

    // checa se o processo já esta alocado na memória
    aux = busca_processo_ms(m_secundaria, nome_processo); // vai ter q trocar
    
    // se não estiver, aloca o processo na memória
    if(!aux){
    
        P *novo = (P*)malloc(sizeof(P));
        strcpy(novo->identificador, nome_processo);
        strcpy(novo->estado_processo, "Novo");
        novo->tam_imagem = tam_processo;
        novo->tab_paginas = inicia_tabela_paginas(novo, tam_processo);
        novo->prox = m_secundaria->processos;
        m_secundaria->processos = novo;

        return novo;
    }   
    return aux;
}

// amanda
LRU *busca_fila(LRU *fila, int end){
    if(!fila) return NULL;

    LRU *aux = fila;
    while(aux != NULL){
        if(aux->end_quadro == end) return aux;
        aux = aux->prox;
    }
    return NULL;
}

// amanda
LRU *insere_fila(LRU *fila, int end){
    // se o elemento não está na fila, entao vamos inseri-lo
    if(!busca_fila(fila, end)){
        LRU *novo;

        novo = (LRU*)malloc(sizeof(LRU));
        novo->end = end;

        if(!fila) return novo;
        LRU *aux = fila;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = novo;
        novo->prox = NULL;
        return fila;
    }
    // se o elemento está na fila, entao buscamos e inserimos no final
    else {
        LRU *ref = NULL, *aux = fila;

        while(aux->prox != NULL){
            if(aux->end == end){
                ref = aux;
            }
            aux = aux->prox;
        }
        aux->prox = ref;
        ref->prox = NULL;
    }
    return fila;
}

// amanda
// como é fila, insere no final
TP *insere_pagina(MP *m_principal, PG pagina, TP *tab, int p, int m, int end){

    TP *novo;

    novo = (TP*)malloc(sizeof(TP));
    novo->bit_p = p;
    novo->bit_m = m;
    novo->end_quadro = end;
    if(novo->tam_preenchido += pagina.tam_pagina <= m_principal->tam_mp) novo->tam_preenchido += pagina.tam_pagina;
    else lru(tab);

    if(!tab) return novo;
    
    TP *aux = tab;
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    
    aux->prox = novo;
    return tab;
}

// amanda
// e remove do início
TP *remove_pagina(TP *tab){
    if(!tab) return NULL;

    TP *aux = tab;

    tab = tab->prox;
    free(aux);
    return tab;
}

// amanda
TP *preenche_fila(MP *m_principal, P *processo, PG pagina){

    TP *aux;
    aux = busca_processo_mp(m_principal, processo);
    if(!aux){
        TP *aux_proc;
        aux = processo->tab_paginas;
        
        while(aux != NULL){
            m_principal->fila_paginas = insere_pagina(m_principal, pagina, aux_proc, aux_proc->bit_p, aux_proc->bit_m, aux_proc->end_quadro);
            aux_proc = aux_proc->prox;
        }
    }
    return aux;
}

// hendel
// acho justo quebrar em funcoes menores (gabi faz)
int MMU (int endereco_logico, int page_size, int qtd_bits_endereco_logico, TP *tabela) {
    int qtd_bits_off_set = casas_decimais_em_binario(page_size);
    int qtd_bits_num_pag = qtd_bits_endereco_logico - qtd_bits_off_set;
    int bin_end_log[qtd_bits_endereco_logico];
    binario(endereco_logico, bin_end_log, qtd_bits_endereco_logico);
    
    // adiciona os bits do off set e da pag
    int bits_off_set[qtd_bits_off_set];
    int bits_num_pag[qtd_bits_num_pag];
    int pos = 0;
    while (pos < qtd_bits_num_pag) {
        bits_num_pag[pos] = bin_end_log[pos];
        pos++;
    }
    int i = 0;
    while (i < qtd_bits_off_set) {
        bits_off_set[i] = bin_end_log[pos];
        i++;
        pos++;
    }

    int off_set = decimal(bits_off_set, qtd_bits_off_set);
    int num_pag = decimal(bits_num_pag, qtd_bits_num_pag);

    TP *pagina = tabela;
    for (int i = 0; i < num_pag; i++) pagina = pagina->prox;
    int endereco_real = (pagina->end_quadro * page_size) + off_set;

    return endereco_real;
}

int casas_decimais_em_binario(int n) {
    int tamanho_binario = 0;
    while (n >= 1) {
        n >>= 1;
        tamanho_binario++;
    }
    return tamanho_binario;
}

// converte de decimal p binario
// n -> valor a ser convertido, *binario é o array int
void binario(int n, int *binario, int tamanho) {
    int i;
    for (i = tamanho - 1; i >= 0; i--) {
        binario[i] = n & 1;
        n >>= 1;
    }
}
// Converte binário em decimal
int decimal(int *binario, int tamanho) {
    int valor = 0;
    for (int i = 0; i < tamanho; i++) {
        valor += binario[i] * pow(2, tamanho - 1 - i);
    }
    return valor;
}

/* operação de término - processo */
//gabi
void halt(P *proc, MP *mp, MS *ms ){ 
    /*
    Raio
    li nos slides q o termino é executado a partir da instrucao halt ai mudei 
    o nome da funcao de termino pra halt pra ficar bonitinho (gabi)
    //Saber qual processo pela estrutura processo como?
    
    pega o endereço e busca na tabela de paginas
    checa se esta na memoria principal
    se sim, remove da memoria principal
    remove da tabela de paginas
    */
    for(int i=0;i<mp->num_quadros; i++){
        mp->vetor_paginas[i]->processo_associado = *proc
    }
}

/* impressões */
//amanda
void imprime_tabela_paginas(TP *tab_pags){

    printf("=======================\n");
    int i = 0;
    TP *aux = tab_pags;
    while(aux != NULL){
        printf("Lacuna %d: \n", i);
        printf("Bit de presença na memória principal: %d \n", tab_pags->bit_p);
        printf("Bit de modificação da página: %d \n", tab_pags->bit_m);
        printf("Endereço do quadro na memória principal: %d \n", tab_pags->end_quadro);
        printf("-------------------------\n");
        aux = aux->prox;
    }
}

// amanda
void imprime_estado_processo(P *processo){
    printf("Dados do processo %s: \n", processo->identificador);
    printf("----------------------\n");
    printf("Estado do processo: %s \n", processo->estado_processo);
    printf("Tamanho do processo: %d \n", processo->tam_imagem);
    printf("Tabela de páginas associada: \n");
    imprime_tabela_paginas(processo->tab_paginas);
    printf("\n");
}

//raian
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

//raian
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