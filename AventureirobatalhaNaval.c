#include <stdio.h>
#include <stdbool.h>

#define TAM 10
#define TAM_NAVIO 3
#define TOTAL_NAVIOS 4

// Tipos de navios
enum { VERTICAL, HORIZONTAL, DIAG_DIREITA, DIAG_ESQUERDA };

void limparTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Verifica se o navio pode ser colocado
bool posicaoOk(int x, int y, int tamanho, int tipo, int tabuleiro[TAM][TAM]) {
    switch (tipo) {
        case VERTICAL:
            if (x + tamanho > TAM) return false;
            for (int i = x; i < x + tamanho; i++) {
                if (tabuleiro[i][y] != 0) return false;
            }
            break;
            
        case HORIZONTAL:
            if (y + tamanho > TAM) return false;
            for (int j = y; j < y + tamanho; j++) {
                if (tabuleiro[x][j] != 0) return false;
            }
            break;
            
        case DIAG_DIREITA:
            if (x + tamanho > TAM || y + tamanho > TAM) return false;
            for (int k = 0; k < tamanho; k++) {
                if (tabuleiro[x + k][y + k] != 0) return false;
            }
            break;
            
        case DIAG_ESQUERDA:
            if (x + tamanho > TAM || y - tamanho + 1 < 0) return false;
            for (int k = 0; k < tamanho; k++) {
                if (tabuleiro[x + k][y - k] != 0) return false;
            }
            break;
    }
    return true;
}

// Adiciona um navio ao tabuleiro
void adicionarNavio(int tabuleiro[TAM][TAM], int x, int y, int tamanho, int tipo) {
    switch (tipo) {
        case VERTICAL:
            for (int i = x; i < x + tamanho; i++) tabuleiro[i][y] = 3;
            break;
            
        case HORIZONTAL:
            for (int j = y; j < y + tamanho; j++) tabuleiro[x][j] = 3;
            break;
            
        case DIAG_DIREITA:
            for (int k = 0; k < tamanho; k++) tabuleiro[x + k][y + k] = 3;
            break;
            
        case DIAG_ESQUERDA:
            for (int k = 0; k < tamanho; k++) tabuleiro[x + k][y - k] = 3;
            break;
    }
}

void mostrarTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("Tabuleiro com navios diagonais:\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    limparTabuleiro(tabuleiro);

    // Posiciona os navios
    int navios[4][3] = {
        {2, 2, VERTICAL},     // Vertical em (2,2)
        {5, 5, HORIZONTAL},   // Horizontal em (5,5)
        {1, 1, DIAG_DIREITA}, // Diagonal direita em (1,1)
        {0, 8, DIAG_ESQUERDA} // Diagonal esquerda em (0,8)
    };

    for (int i = 0; i < TOTAL_NAVIOS; i++) {
        int x = navios[i][0];
        int y = navios[i][1];
        int tipo = navios[i][2];
        
        if (!posicaoOk(x, y, TAM_NAVIO, tipo, tabuleiro)) {
            printf("Navio %d em posição inválida!\n", i+1);
            return 1;
        }
        adicionarNavio(tabuleiro, x, y, TAM_NAVIO, tipo);
    }

    mostrarTabuleiro(tabuleiro);
    return 0;
}
