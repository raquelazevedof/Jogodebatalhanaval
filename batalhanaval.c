#include <stdio.h>

#define TAM 10
#define NAVIO 3
#define NAVIO_VALOR 3
#define AGUA 0
#define AREA_HABILIDADE 5

// Inicializa o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = AGUA;
}

// Verifica se pode posicionar um navio ortogonal (horizontal ou vertical)
int podeColocarOrto(int tabuleiro[TAM][TAM], int lin, int col, char direcao) {
    if (direcao == 'H') {
        if (col + NAVIO > TAM) return 0;
        for (int i = 0; i < NAVIO; i++)
            if (tabuleiro[lin][col + i] != AGUA) return 0;
    } else if (direcao == 'V') {
        if (lin + NAVIO > TAM) return 0;
        for (int i = 0; i < NAVIO; i++)
            if (tabuleiro[lin + i][col] != AGUA) return 0;
    }
    return 1;
}

// Posiciona navio ortogonal
void posicionarOrto(int tabuleiro[TAM][TAM], int lin, int col, char direcao) {
    for (int i = 0; i < NAVIO; i++) {
        if (direcao == 'H') tabuleiro[lin][col + i] = NAVIO_VALOR;
        else if (direcao == 'V') tabuleiro[lin + i][col] = NAVIO_VALOR;
    }
}

// Verifica se pode posicionar navio diagonal
int podeColocarDiagonal(int tabuleiro[TAM][TAM], int lin, int col, char tipo) {
    if (tipo == '\\') {
        if (lin + NAVIO > TAM || col + NAVIO > TAM) return 0;
        for (int i = 0; i < NAVIO; i++)
            if (tabuleiro[lin + i][col + i] != AGUA) return 0;
    } else if (tipo == '/') {
        if (lin + NAVIO > TAM || col - NAVIO + 1 < 0) return 0;
        for (int i = 0; i < NAVIO; i++)
            if (tabuleiro[lin + i][col - i] != AGUA) return 0;
    }
    return 1;
}

// Posiciona navio diagonal
void posicionarDiagonal(int tabuleiro[TAM][TAM], int lin, int col, char tipo) {
    for (int i = 0; i < NAVIO; i++) {
        if (tipo == '\\') tabuleiro[lin + i][col + i] = NAVIO_VALOR;
        else if (tipo == '/') tabuleiro[lin + i][col - i] = NAVIO_VALOR;
    }
}

// Cria uma matriz de habilidade Cone (5x5)
void criarHabilidadeCone(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            habilidade[i][j] = (j >= 2 - i && j <= 2 + i) ? 1 : 0;
}

// Cria uma matriz de habilidade Cruz (5x5)
void criarHabilidadeCruz(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            habilidade[i][j] = (i == 2 || j == 2) ? 1 : 0;
}

// Cria uma matriz de habilidade Octaedro (5x5)
void criarHabilidadeOctaedro(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            habilidade[i][j] = (abs(i - 2) + abs(j - 2) <= 2) ? 1 : 0;
}

// Sobrepõe a habilidade no tabuleiro, centrando no ponto de origem
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[5][5], int origemLin, int origemCol) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int lin = origemLin - 2 + i;
            int col = origemCol - 2 + j;
            if (lin >= 0 && lin < TAM && col >= 0 && col < TAM && habilidade[i][j] == 1) {
                if (tabuleiro[lin][col] == AGUA)
                    tabuleiro[lin][col] = AREA_HABILIDADE;
            }
        }
    }
}

// Exibe o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("TABULEIRO:\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == AGUA) printf("~ ");
            else if (tabuleiro[i][j] == NAVIO_VALOR) printf("N ");
            else if (tabuleiro[i][j] == AREA_HABILIDADE) printf("* ");
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // Posiciona navios ortogonais
    if (podeColocarOrto(tabuleiro, 1, 1, 'H'))
        posicionarOrto(tabuleiro, 1, 1, 'H');
    if (podeColocarOrto(tabuleiro, 5, 7, 'V'))
        posicionarOrto(tabuleiro, 5, 7, 'V');

    // Posiciona navios diagonais
    if (podeColocarDiagonal(tabuleiro, 2, 2, '\\'))
        posicionarDiagonal(tabuleiro, 2, 2, '\\');
    if (podeColocarDiagonal(tabuleiro, 0, 9, '/'))
        posicionarDiagonal(tabuleiro, 0, 9, '/');

    // Criação das habilidades
    int cone[5][5], cruz[5][5], octaedro[5][5];
    criarHabilidadeCone(cone);
    criarHabilidadeCruz(cruz);
    criarHabilidadeOctaedro(octaedro);

    // Aplicação das habilidades
    aplicarHabilidade(tabuleiro, cone, 7, 2);      // Origem da habilidade Cone
    aplicarHabilidade(tabuleiro, cruz, 4, 4);      // Origem da habilidade Cruz
    aplicarHabilidade(tabuleiro, octaedro, 6, 6);  // Origem da habilidade Octaedro

    // Exibe o resultado final
    exibirTabuleiro(tabuleiro);
    return 0;
}