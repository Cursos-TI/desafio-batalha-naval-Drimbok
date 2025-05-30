#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Constantes do jogo
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5
#define TAMANHO_HABILIDADE 7  // Tamanho das matrizes de habilidade (deve ser ímpar para ter centro)

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para verificar se a posição do navio reto (horizontal/vertical) é válida
bool posicaoRetoValida(int x, int y, bool vertical, int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    if (vertical) {
        if (x + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return false;
    } else {
        if (y + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return false;
    }
    
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (vertical) {
            if (tabuleiro[x + i][y] != AGUA) return false;
        } else {
            if (tabuleiro[x][y + i] != AGUA) return false;
        }
    }
    
    return true;
}

// Função para verificar se a posição do navio diagonal é válida
bool posicaoDiagonalValida(int x, int y, bool diagonalDescendente, int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    if (diagonalDescendente) {
        if (x + TAMANHO_NAVIO > TAMANHO_TABULEIRO || y + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return false;
    } else {
        if (x + TAMANHO_NAVIO > TAMANHO_TABULEIRO || y - TAMANHO_NAVIO < -1) return false;
    }
    
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (diagonalDescendente) {
            if (tabuleiro[x + i][y + i] != AGUA) return false;
        } else {
            if (tabuleiro[x + i][y - i] != AGUA) return false;
        }
    }
    
    return true;
}

// Função para posicionar um navio reto (horizontal/vertical) no tabuleiro
void posicionarNavioReto(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int x, int y, bool vertical) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (vertical) {
            tabuleiro[x + i][y] = NAVIO;
        } else {
            tabuleiro[x][y + i] = NAVIO;
        }
    }
}

// Função para posicionar um navio diagonal no tabuleiro
void posicionarNavioDiagonal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int x, int y, bool diagonalDescendente) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (diagonalDescendente) {
            tabuleiro[x + i][y + i] = NAVIO;
        } else {
            tabuleiro[x + i][y - i] = NAVIO;
        }
    }
}

// Função para criar matriz de habilidade em formato de Cone
void criarHabilidadeCone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Cone apontando para baixo (origem no topo)
            if (i >= centro && abs(j - centro) <= (i - centro)) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar matriz de habilidade em formato de Cruz
void criarHabilidadeCruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Cruz com origem no centro
            if (i == centro || j == centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar matriz de habilidade em formato de Octaedro (losango)
void criarHabilidadeOctaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Losango com origem no centro
            if (abs(i - centro) + abs(j - centro) <= centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para aplicar uma habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                      int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], 
                      int x, int y) {
    int centro = TAMANHO_HABILIDADE / 2;
    int offset_x = x - centro;
    int offset_y = y - centro;
    
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int tab_x = offset_x + i;
            int tab_y = offset_y + j;
            
            // Verifica se está dentro dos limites do tabuleiro
            if (tab_x >= 0 && tab_x < TAMANHO_TABULEIRO && 
                tab_y >= 0 && tab_y < TAMANHO_TABULEIRO) {
                // Aplica a habilidade apenas se não for navio
                if (habilidade[i][j] == 1 && tabuleiro[tab_x][tab_y] != NAVIO) {
                    tabuleiro[tab_x][tab_y] = HABILIDADE;
                }
            }
        }
    }
}

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Tabuleiro do Batalha Naval com Habilidades:\n\n");
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j); // Cabeçalho das colunas
    }
    printf("\n");
    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i); // Índice da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == NAVIO) {
                printf(" N ");      // Navio
            } else if (tabuleiro[i][j] == HABILIDADE) {
                printf(" H ");      // Área afetada por habilidade
            } else {
                printf(" . ");      // Água
            }
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Inicializa o tabuleiro com água
    inicializarTabuleiro(tabuleiro);
    
    // Posiciona os navios (como no nível anterior)
    posicionarNavioReto(tabuleiro, 2, 3, false);    // Navio horizontal
    posicionarNavioReto(tabuleiro, 5, 7, true);     // Navio vertical
    posicionarNavioDiagonal(tabuleiro, 1, 1, true);  // Navio diagonal descendente
    posicionarNavioDiagonal(tabuleiro, 0, 9, false); // Navio diagonal ascendente
    
    // Cria as matrizes de habilidade
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    
    criarHabilidadeCone(cone);
    criarHabilidadeCruz(cruz);
    criarHabilidadeOctaedro(octaedro);
    
    // Aplica as habilidades ao tabuleiro
    aplicarHabilidade(tabuleiro, cone, 4, 4);       // Cone centrado em (4,4)
    aplicarHabilidade(tabuleiro, cruz, 7, 2);       // Cruz centrada em (7,2)
    aplicarHabilidade(tabuleiro, octaedro, 3, 6);   // Octaedro centrado em (3,6)
    
    // Exibe o tabuleiro com os navios e habilidades
    exibirTabuleiro(tabuleiro);
    
    return 0;
}
