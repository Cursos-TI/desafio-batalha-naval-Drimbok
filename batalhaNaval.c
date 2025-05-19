#include <stdio.h>
#include <stdbool.h>

// Constantes do jogo
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

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
    // Verifica se o navio cabe no tabuleiro a partir da posição (x,y)
    if (vertical) {
        if (x + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return false;
    } else {
        if (y + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return false;
    }
    
    // Verifica se não há sobreposição com outros navios
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
    // Verifica se o navio cabe no tabuleiro a partir da posição (x,y)
    if (diagonalDescendente) {
        if (x + TAMANHO_NAVIO > TAMANHO_TABULEIRO || y + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return false;
    } else {
        if (x + TAMANHO_NAVIO > TAMANHO_TABULEIRO || y - TAMANHO_NAVIO < -1) return false;
    }
    
    // Verifica se não há sobreposição com outros navios
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

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Tabuleiro do Batalha Naval:\n\n");
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j); // Cabeçalho das colunas
    }
    printf("\n");
    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i); // Índice da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == NAVIO) {
                printf(" N "); // Representação do navio
            } else {
                printf(" . "); // Representação da água
            }
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Inicializa o tabuleiro com água
    inicializarTabuleiro(tabuleiro);
    
    // Posiciona o primeiro navio (horizontal)
    int navio1_x = 2, navio1_y = 3;
    bool navio1_vertical = false;
    
    if (posicaoRetoValida(navio1_x, navio1_y, navio1_vertical, tabuleiro)) {
        posicionarNavioReto(tabuleiro, navio1_x, navio1_y, navio1_vertical);
    } else {
        printf("Posição inválida para o navio 1 (horizontal)!\n");
        return 1;
    }
    
    // Posiciona o segundo navio (vertical)
    int navio2_x = 5, navio2_y = 7;
    bool navio2_vertical = true;
    
    if (posicaoRetoValida(navio2_x, navio2_y, navio2_vertical, tabuleiro)) {
        posicionarNavioReto(tabuleiro, navio2_x, navio2_y, navio2_vertical);
    } else {
        printf("Posição inválida para o navio 2 (vertical)!\n");
        return 1;
    }
    
    // Posiciona o terceiro navio (diagonal descendente)
    int navio3_x = 1, navio3_y = 1;
    bool navio3_diagonalDescendente = true;
    
    if (posicaoDiagonalValida(navio3_x, navio3_y, navio3_diagonalDescendente, tabuleiro)) {
        posicionarNavioDiagonal(tabuleiro, navio3_x, navio3_y, navio3_diagonalDescendente);
    } else {
        printf("Posição inválida para o navio 3 (diagonal descendente)!\n");
        return 1;
    }
    
    // Posiciona o quarto navio (diagonal ascendente)
    int navio4_x = 0, navio4_y = 9;
    bool navio4_diagonalDescendente = false;
    
    if (posicaoDiagonalValida(navio4_x, navio4_y, navio4_diagonalDescendente, tabuleiro)) {
        posicionarNavioDiagonal(tabuleiro, navio4_x, navio4_y, navio4_diagonalDescendente);
    } else {
        printf("Posição inválida para o navio 4 (diagonal ascendente)!\n");
        return 1;
    }
    
    // Exibe o tabuleiro com os navios posicionados
    exibirTabuleiro(tabuleiro);
    
    return 0;
}
