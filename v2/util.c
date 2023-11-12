#include <stdio.h>
#include <stdlib.h>

char* converteIntParaBinario(int numero) {
    // Tamanho máximo de uma representação binária de 32 bits
    int tamanho = 32;
    
    // Alocar espaço para a string binária
    char* binario = (char*)malloc(tamanho + 1);  // +1 para o caractere nulo
    
    // Verificar se a alocação foi bem-sucedida
    if (binario == NULL) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        exit(EXIT_FAILURE);
    }
    
    // Inicializar a string binária com caracteres '0'
    for (int i = 0; i < tamanho; ++i) {
        binario[i] = '0';
    }
    binario[tamanho] = '\0';  // Adicionar o caractere nulo no final
    
    // Preencher a representação binária
    for (int i = tamanho - 1; i >= 0; --i) {
        if (numero & 1) {
            binario[i] = '1';
        }
        numero >>= 1;  // Deslocar para a direita
    }
    
    return binario;
}