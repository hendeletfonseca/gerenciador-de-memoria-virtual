/* Páginas da imagem devem ser carregadas para quadros da MP quando necessário.
Quando o processador requisitar acesso a um endereço virtual/relativo,
um simulador do hardware que mapeia este endereço para o endereço real deve realizar o mapeamento,
resultando no acesso ao endereço real caso a página esteja em memória,
ou em caso de falta de página em MP, realizar os passos necessários para trazer a página para a MP
(alocar um quadro que esteja disponível). Caso não haja disponibilidade,
executar a política de substituição de páginas.*/

//IMPORTANTE
//implementar funcao que faz o mapeamento -- hendel fez isso na branch?
//implementar fila dos prontos e bloqueados

int MMU(){ //componente do hardware que converte o endereco logico em fisico
    //registradores: base e limite serve de algo?
    //nao escrevi certinho as coisas pq quero revisar as estruturas ainda
    return numeroQuadro * tamanhoPagina + deslocamento dentro da pagina
}

DUVIDAS:
//- bit de presenca ta na pagina? se tiver vai facilitar mt pra ver se a pag precisa ser carregada na mp 
//ou se ja esta la. ou ele ta na tp
- como implementar os requisitos de E/S?
//- vetor dinamico ou lista encadeada na fila_mp? 


void carrega_pag_mp(P* processo, PG* pagina, MP*m_principal){ //mp é uma fila!!!
    //processo esta esperando (Novo ou bloqueado)
    fila_mp = m_principal->quadro_paginas

    if (!cheia(fila_mp)){ //Caso 1: MP nao esta cheia -- pagina é alocada
        insere(fila_mp, pagina) 
    }
    else{ //Caso 2: A MP esta cheia e aplicaremos a política de substituicao LRU
        printf("A MP está cheia, useremos a política de substituição LRU para carregar a imagem na MP")
        retira(fila_mp);
        insere(fila_mp, pagina);
    }

    printf("A página da imagem do processo X foi carregada para a MP com sucesso\n") //substituir X
    //estado do processo passa a ser pronto
    processo->estado = 'Pronto'
    printf("O processo passou para o estado 'Pronto'\n")
}