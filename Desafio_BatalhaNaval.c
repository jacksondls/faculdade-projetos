#include <stdio.h>

#define N 10      // tamanho do tabuleiro 10x10
#define SK 5      // tamanho das matrizes de habilidade (5x5)
#define WATER 0
#define SHIP 3
#define AFFECT 5

/* Função para inicializar o tabuleiro com água (0) e alguns navios (3) de exemplo */
void inicializarTabuleiro(int tab[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            tab[i][j] = WATER;

    // Colocando alguns navios de exemplo (valor 3)
    tab[2][2] = SHIP;
    tab[2][3] = SHIP;
    tab[5][7] = SHIP;
    tab[6][7] = SHIP;
    tab[7][7] = SHIP;
}

/* Imprime o tabuleiro no console (números separados por espaço) */
void imprimirTabuleiro(int tab[N][N]) {
    printf("\nTabuleiro (0=Água, 3=Navio, 5=Área afetada):\n\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/* =========================
   Funções que constroem as matrizes de habilidade (SK x SK)
   Cada função preenche skill[SK][SK] com 0 ou 1 usando loops e condicionais.
   O centro da matriz é (cx, cy) = (SK/2, SK/2).
   ========================= */

/* Constrói um cone apontando para baixo.
   Exemplo em SK=5 (apenas as 3 primeiras linhas usadas para o cone):
   0 0 1 0 0
   0 1 1 1 0
   1 1 1 1 1
*/
void construirCone(int skill[SK][SK]) {
    int cx = SK/2; // coluna central
    for (int r = 0; r < SK; r++) {
        for (int c = 0; c < SK; c++) {
            // Inicializa com 0
            skill[r][c] = 0;

            /* Condicional que cria um "cone" para baixo:
               Para r = 0 -> só a coluna central
               Para r = 1 -> coluna central ±1
               Para r = 2 -> coluna central ±2 (toda a linha)
               Para r > 2 -> mantemos 0 (fora do cone)
               Isso usa condicionais nos loops aninhados. */
            if (r == 0 && c == cx) skill[r][c] = 1;
            else if (r == 1 && (c >= cx-1 && c <= cx+1)) skill[r][c] = 1;
            else if (r == 2 && (c >= cx-2 && c <= cx+2)) skill[r][c] = 1;
            else skill[r][c] = 0;
        }
    }
}

/* Constrói uma cruz com ponto de origem no centro:
   Para SK=5:
   0 0 1 0 0
   0 0 1 0 0
   1 1 1 1 1
   0 0 1 0 0
   0 0 1 0 0
*/
void construirCruz(int skill[SK][SK]) {
    int cx = SK/2;
    int cy = SK/2;
    for (int r = 0; r < SK; r++) {
        for (int c = 0; c < SK; c++) {
            // vertical (mesma coluna do centro) ou horizontal (mesma linha do centro)
            if (c == cx || r == cy) skill[r][c] = 1;
            else skill[r][c] = 0;
        }
    }
}

/* Constrói um "octaedro" visto de frente — modelado como um losango/diamante:
   Usamos a distância de Manhattan ao centro: abs(r-cy)+abs(c-cx) <= raio
   Para SK=5 e raio=2 teremos:
   0 0 1 0 0
   0 1 1 1 0
   1 1 1 1 1
   0 1 1 1 0
   0 0 1 0 0
*/
void construirOctaedro(int skill[SK][SK]) {
    int cx = SK/2;
    int cy = SK/2;
    int raio = SK/2; // para SK=5 -> raio = 2
    for (int r = 0; r < SK; r++) {
        for (int c = 0; c < SK; c++) {
            int manhattan = abs(r - cy) + abs(c - cx);
            if (manhattan <= raio) skill[r][c] = 1;
            else skill[r][c] = 0;
        }
    }
}

/* =========================
   Sobreposição da matriz de habilidade no tabuleiro
   origemLinha e origemCol definem onde o centro da skill ficará no tabuleiro.
   A sobreposição deve respeitar limites do tabuleiro.
   Se a posição do tabuleiro for WATER (0) e skill[r][c] == 1 -> marcamos AFFECT (5).
   Se já houver SHIP (3), mantemos 3 (decisão para manter visibilidade dos navios).
   ========================= */
void sobreporSkill(int tab[N][N], int skill[SK][SK], int origemLinha, int origemCol) {
    int cx = SK/2;
    int cy = SK/2;

    // percorre a matriz skill
    for (int r = 0; r < SK; r++) {
        for (int c = 0; c < SK; c++) {
            if (skill[r][c] == 1) {
                // calcula coordenada correspondente no tabuleiro (centro alinhado)
                int linhaTab = origemLinha + (r - cy);
                int colTab   = origemCol  + (c - cx);

                // verifica limites do tabuleiro
                if (linhaTab >= 0 && linhaTab < N && colTab >= 0 && colTab < N) {
                    // só marcamos se for água; se já tiver navio (3) mantemos 3
                    if (tab[linhaTab][colTab] == WATER) {
                        tab[linhaTab][colTab] = AFFECT;
                    }
                    // se for SHIP, mantemos 3 para visualizar navios; alternativa seria marcar combinação
                }
            }
        }
    }
}

/* =========================
   Função principal
   ========================= */
int main() {
    int tabuleiro[N][N];
    inicializarTabuleiro(tabuleiro);

    // Matrizes de habilidade (SK x SK)
    int cone[SK][SK];
    int cruz[SK][SK];
    int octaedro[SK][SK];

    // Construção dinâmica das matrizes com loops e condicionais
    construirCone(cone);
    construirCruz(cruz);
    construirOctaedro(octaedro);

    // Definindo pontos de origem no tabuleiro para cada habilidade (linha, coluna)
    // (estas posições são definidas diretamente no código conforme solicitado)
    int origemConeLinha = 1, origemConeCol = 4;    // exemplo: perto do topo
    int origemCruzLinha = 5, origemCruzCol = 5;    // exemplo: centro-direita
    int origemOctLinha  = 7, origemOctCol  = 2;    // exemplo: parte inferior-esquerda

    // Sobrepõe cada habilidade ao tabuleiro
    sobreporSkill(tabuleiro, cone, origemConeLinha, origemConeCol);
    sobreporSkill(tabuleiro, cruz, origemCruzLinha, origemCruzCol);
    sobreporSkill(tabuleiro, octaedro, origemOctLinha, origemOctCol);

    // Exibe as matrizes de habilidade (opcional, para debug/visualizar a forma)
    printf("Matriz CONE (1=afeta, 0=não afeta):\n");
    for (int i = 0; i < SK; i++) {
        for (int j = 0; j < SK; j++) printf("%d ", cone[i][j]);
        printf("\n");
    }
    printf("\n");

    printf("Matriz CRUZ (1=afeta, 0=não afeta):\n");
    for (int i = 0; i < SK; i++) {
        for (int j = 0; j < SK; j++) printf("%d ", cruz[i][j]);
        printf("\n");
    }
    printf("\n");

    printf("Matriz OCTAEDRO (1=afeta, 0=não afeta):\n");
    for (int i = 0; i < SK; i++) {
        for (int j = 0; j < SK; j++) printf("%d ", octaedro[i][j]);
        printf("\n");
    }
    printf("\n");

    // Imprime o tabuleiro final com áreas afetadas marcadas
    imprimirTabuleiro(tabuleiro);

    return 0;
}
