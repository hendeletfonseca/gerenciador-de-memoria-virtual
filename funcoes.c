#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

/*Tamanho total da Memória física (que deve ser múltiplo de tamanho do quadro) e
Memória Secundária
● Tamanho da página de um processo e quadro de memória;
● Tamanho em bits do endereço lógico.*/

/*P - instrução a ser executada pela CPU
● I - instrução de I/O
● C - criação (submissão de um processo)
● R - pedido de leitura em um endereço lógico
● W - pedido de escrita em um endereço lógico de um dado valor
● T - terminação de processo
*/

/*funcoes:
- void operacao(File *arquivo); {le o arquivo e identifica qual operação será feita}
- void substituicao(fds nao sei o que vai aqui, depois a gente pensa); {realiza a operação de troca das páginas}
- void *mapeamento(int endereco_logico, int *endereco_fisico);
- int MMU(endereco_logico); -- retona o endereco fisico
-
- implementar swapper
- alocar pagina na MP
- implemetar politica de substituicao de pag (LRU)
Atenção, se o quadro escolhido
armazenar uma página (a que será substituída) que foi modificada, a gravação desta
deve ser realizada antes da carga da nova página a ser trazida para memória.

Gerenciador de memoria é um método
*/


typedef struct Processo {
    int id; //ignorar char P
    int bitP;
    int bitM;
    int tam_imagem;
    int nQuadro; //numero do quadro em MP, quando a referida pagina esta em memoria.
} PI;

typedef struct Pagina {
    int tam;
    PI* processo;
} P;

typedef struct TabelaPaginas {
    P* pagina;
    int numPaginas; //Tamanho do vetor Paginas.
    int tamTabela  = numPaginas * (pagina[0]->tam);
} TP;

typedef struct MemoriaPrincipal {
    int tamMemoria;
    int endFisico;
    int* quadroMemoria;
} MP;

typedef struct MemoriaSecundaria {
    int tamMemoria;
    int endLogico;
} MS;

/*Seu sistema GM deve conter as seguintes opções de configuração de mecanismos
associados à memória virtual:
● Tamanho total da Memória física (que deve ser múltiplo de tamanho do quadro) e
Memória Secundária
● Tamanho da página de um processo e quadro de memória;
● Tamanho em bits do endereço lógico.
*/


void configuracoes(int *tam_mf, int *tam_ms, int *tam_pag, int *tam_qm, int *tam_end_logico){
    int aux;

    printf("Digite o tamanho desejado para cada uma das opcoes: \n");
    
    printf("1. Tamanho do quadro de memoria (valor inteiro em KB): \n");
    scanf("%d", &aux);
    aux = aux * 1024;
    (*tam_qm) = aux;

    printf("2. Tamanho da memoria fisica (Deve ser multiplo do tamanho do quadro): \n");
    do {
        scanf("%d", &aux);
    } while (aux % (*tam_qm) == 0);
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
}

void cria_processo(int num_processo, int tamanho_processo) {

}

void executa_processo(int num_processo, char flag, int tamEnd_processo) {
    switch (flag) {

        case 'P':
            
            break;
        
        case 'I':

            break
        case 'C':
            cria_processo(num_processo, tamEnd_processo);
            break;
        case 'R':

            break;
        case 'W':

            break;
        case 'T':

            break;
            
        default:
            break;
    }
}