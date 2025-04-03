#include <stdio.h>
#include <stdbool.h>

#define TAM 10
#define TAM_NAVIO 3

// Preenche o tabuleiro com 0 (água)
void limparTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Verifica se o navio cabe na posição escolhida
bool cabeNavio(int x, int y, int tamanho, bool vertical, int tabuleiro[TAM][TAM]) {
    if (vertical) {
        if (x + tamanho > TAM) return false;
        for (int i = x; i < x + tamanho; i++) {
            if (tabuleiro[i][y] != 0) return false;
        }
    } else {
        if (y + tamanho > TAM) return false;
        for (int j = y; j < y + tamanho; j++) {
            if (tabuleiro[x][j] != 0) return false;
        }
    }
    return true;
}

// Coloca um navio no tabuleiro
void colocarNavio(int tabuleiro[TAM][TAM], int x, int y, int tamanho, bool vertical) {
    if (vertical) {
        for (int i = x; i < x + tamanho; i++) {
            tabuleiro[i][y] = 3; // 3 representa navio
        }
    } else {
        for (int j = y; j < y + tamanho; j++) {
            tabuleiro[x][j] = 3;
        }
    }
}

// Mostra o tabuleiro na tela
void mostrarTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("Tabuleiro:\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    
    // Prepara o tabuleiro vazio
    limparTabuleiro(tabuleiro);
    
    // Navio vertical na posição (2,4)
    if (cabeNavio(2, 4, TAM_NAVIO, true, tabuleiro)) {
        colocarNavio(tabuleiro, 2, 4, TAM_NAVIO, true);
    } else {
        printf("Posição inválida para navio vertical!\n");
        return 1;
    }
    
    // Navio horizontal na posição (5,1)
    if (cabeNavio(5, 1, TAM_NAVIO, false, tabuleiro)) {
        colocarNavio(tabuleiro, 5, 1, TAM_NAVIO, false);
    } else {
        printf("Posição inválida para navio horizontal!\n");
        return 1;
    }
    
    // Exibe o resultado
    mostrarTabuleiro(tabuleiro);
    
    return 0;
}
