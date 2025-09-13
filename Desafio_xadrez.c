#include <stdio.h>

/* ========================
   Funções Recursivas
   ======================== */

// Torre: movimento vertical ou horizontal
void moverTorre(int casas, int direcao) {
    if (casas == 0) return; // caso base

    switch (direcao) {
        case 1: printf("Cima\n"); break;
        case 2: printf("Baixo\n"); break;
        case 3: printf("Esquerda\n"); break;
        case 4: printf("Direita\n"); break;
    }

    moverTorre(casas - 1, direcao); // chamada recursiva
}

// Bispo: diagonal -> usa recursão e loops aninhados
void moverBispo(int casas) {
    if (casas == 0) return; // caso base

    // loop externo: vertical
    for (int v = 0; v < 1; v++) {
        // loop interno: horizontal
        for (int h = 0; h < 1; h++) {
            printf("Cima e Direita\n");
        }
    }

    moverBispo(casas - 1); // recursão
}

// Rainha: combina Torre + Bispo (recursivo)
void moverRainha(int casas) {
    if (casas == 0) return; // caso base

    printf("Cima\n");          // como Torre
    printf("Cima e Direita\n"); // como Bispo

    moverRainha(casas - 1); // recursão
}

/* ========================
   Loops complexos - Cavalo
   ======================== */

// Cavalo: 2 para cima e 1 para direita
void moverCavalo(int movimentos) {
    for (int i = 0; i < movimentos; i++) {
        for (int passo = 1; passo <= 3; passo++) {
            if (passo <= 2) {
                printf("Cima\n");
            } else {
                printf("Direita\n");
            }

            // controle de fluxo
            if (passo == 2) continue; // força continuar no loop
            if (passo == 3) break;    // encerra após completar o "L"
        }
        printf("---\n"); // separador de cada movimento do cavalo
    }
}

/* ========================
   Função principal
   ======================== */

int main() {
    int casasTorre = 3;
    int casasBispo = 2;
    int casasRainha = 2;
    int movimentosCavalo = 2;

    printf("=== Movimento da Torre ===\n");
    moverTorre(casasTorre, 1); // 1 = cima
    printf("\n");

    printf("=== Movimento do Bispo ===\n");
    moverBispo(casasBispo);
    printf("\n");

    printf("=== Movimento da Rainha ===\n");
    moverRainha(casasRainha);
    printf("\n");

    printf("=== Movimento do Cavalo ===\n");
    moverCavalo(movimentosCavalo);
    printf("\n");

    return 0;
}
