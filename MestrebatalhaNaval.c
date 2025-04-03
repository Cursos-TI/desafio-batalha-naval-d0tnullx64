#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TAM 10
#define TAM_NAVIO 3
#define TOTAL_NAVIOS 4
#define TAM_HAB 5

// Tipos de navios e habilidades
enum { VERTICAL, HORIZONTAL, DIAG_DIREITA, DIAG_ESQUERDA };
enum { CONE, CRUZ, OCTAEDRO };

void limparTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = 0;
}

bool posicaoOk(int x, int y, int tamanho, int tipo, int tabuleiro[TAM][TAM]) {
    switch (tipo) {
        case VERTICAL:
            if (x + tamanho > TAM) return false;
            for (int i = x; i < x + tamanho; i++)
                if (tabuleiro[i][y] != 0) return false;
            break;
            
        case HORIZONTAL:
            if (y + tamanho > TAM) return false;
            for (int j = y; j < y + tamanho; j++)
                if (tabuleiro[x][j] != 0) return false;
            break;
            
        case DIAG_DIREITA:
            if (x + tamanho > TAM || y + tamanho > TAM) return false;
            for (int k = 0; k < tamanho; k++)
                if (tabuleiro[x + k][y + k] != 0) return false;
            break;
            
        case DIAG_ESQUERDA:
            if (x + tamanho > TAM || y - tamanho + 1 < 0) return false;
            for (int k = 0; k < tamanho; k++)
                if (tabuleiro[x + k][y - k] != 0) return false;
            break;
    }
    return true;
}

void colocarNavio(int tabuleiro[TAM][TAM], int x, int y, int tamanho, int tipo) {
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

// Cria padrões de habilidades
void criarHabilidade(int habilidade[TAM_HAB][TAM_HAB], int tipo) {
    int centro = TAM_HAB / 2;
    
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            habilidade[i][j] = 0;
            
            switch (tipo) {
                case CONE:
                    if (j >= (centro - i) && j <= (centro + i) && i <= centro)
                        habilidade[i][j] = 1;
                    break;
                    
                case CRUZ:
                    if (i == centro || j == centro)
                        habilidade[i][j] = 1;
                    break;
                    
                case OCTAEDRO:
                    if (abs(i - centro) + abs(j - centro) <= centro)
                        habilidade[i][j] = 1;
                    break;
            }
        }
    }
}

// Aplica habilidade no tabuleiro
void usarHabilidade(int tabuleiro[TAM][TAM], int habilidade[TAM_HAB][TAM_HAB], int x, int y) {
    int metade = TAM_HAB / 2;
    
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int posX = x + i - metade;
            int posY = y + j - metade;
            
            if (posX >= 0 && posX < TAM && posY >= 0 && posY < TAM) {
                if (habilidade[i][j] == 1) {
                    tabuleiro[posX][posY] = 5; // 5 = área de habilidade
                }
            }
        }
    }
}

void mostrarTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("Tabuleiro com habilidades:\n");
    printf("0=Água | 3=Navio | 5=Habilidade\n");
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
        {2, 2, VERTICAL}, {5, 5, HORIZONTAL}, 
        {1, 1, DIAG_DIREITA}, {0, 8, DIAG_ESQUERDA}
    };

    for (int i = 0; i < TOTAL_NAVIOS; i++) {
        int x = navios[i][0];
        int y = navios[i][1];
        int tipo = navios[i][2];
        
        if (!posicaoOk(x, y, TAM_NAVIO, tipo, tabuleiro)) {
            printf("Erro ao posicionar navio %d\n", i+1);
            return 1;
        }
        colocarNavio(tabuleiro, x, y, TAM_NAVIO, tipo);
    }

    // Cria e aplica habilidades
    int hab_cone[TAM_HAB][TAM_HAB];
    int hab_cruz[TAM_HAB][TAM_HAB];
    int hab_octaedro[TAM_HAB][TAM_HAB];
    
    criarHabilidade(hab_cone, CONE);
    criarHabilidade(hab_cruz, CRUZ);
    criarHabilidade(hab_octaedro, OCTAEDRO);
    
    usarHabilidade(tabuleiro, hab_cone, 7, 2);
    usarHabilidade(tabuleiro, hab_cruz, 3, 7);
    usarHabilidade(tabuleiro, hab_octaedro, 4, 4);

    mostrarTabuleiro(tabuleiro);
    return 0;
}
