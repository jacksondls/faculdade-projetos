#include <stdio.h>

// Estrutura da carta
typedef struct {
    char nome[30];
    unsigned long int populacao;
    float area;
    float pib;
    int pontos_turisticos;
    float densidade;
    float pib_per_capita;
} Carta;

// Função para calcular atributos derivados
void calcularAtributos(Carta *c) {
    c->densidade = (float)c->populacao / c->area;
    c->pib_per_capita = c->pib / (float)c->populacao;
}

// Função para exibir os atributos de uma carta
void mostrarCarta(Carta c) {
    printf("\n--- Carta: %s ---\n", c.nome);
    printf("População: %lu\n", c.populacao);
    printf("Área: %.2f\n", c.area);
    printf("PIB: %.2f\n", c.pib);
    printf("Pontos Turísticos: %d\n", c.pontos_turisticos);
    printf("Densidade Demográfica: %.2f\n", c.densidade);
    printf("PIB per Capita: %.2f\n", c.pib_per_capita);
}

// Função para exibir o menu de atributos
void mostrarMenu(int ignorar) {
    printf("\nEscolha um atributo para comparar:\n");
    if (ignorar != 1) printf("1 - População\n");
    if (ignorar != 2) printf("2 - Área\n");
    if (ignorar != 3) printf("3 - PIB\n");
    if (ignorar != 4) printf("4 - Pontos Turísticos\n");
    if (ignorar != 5) printf("5 - Densidade Demográfica\n");
    if (ignorar != 6) printf("6 - PIB per Capita\n");
    printf("Opção: ");
}

// Função para pegar o valor do atributo escolhido
float valorAtributo(Carta c, int opcao) {
    switch(opcao) {
        case 1: return (float)c.populacao;
        case 2: return c.area;
        case 3: return c.pib;
        case 4: return (float)c.pontos_turisticos;
        case 5: return c.densidade;
        case 6: return c.pib_per_capita;
        default: return -1; // erro
    }
}

// Função para imprimir o nome do atributo
const char* nomeAtributo(int opcao) {
    switch(opcao) {
        case 1: return "População";
        case 2: return "Área";
        case 3: return "PIB";
        case 4: return "Pontos Turísticos";
        case 5: return "Densidade Demográfica";
        case 6: return "PIB per Capita";
        default: return "Inválido";
    }
}

int main() {
    Carta c1 = {"Brasil", 214000000, 8516000, 2200000000000, 50};
    Carta c2 = {"Argentina", 46000000, 2780000, 600000000000, 30};

    // Calcula atributos derivados
    calcularAtributos(&c1);
    calcularAtributos(&c2);

    // Mostra cartas cadastradas
    mostrarCarta(c1);
    mostrarCarta(c2);

    int atributo1, atributo2;

    // Escolha do primeiro atributo
    mostrarMenu(0);
    scanf("%d", &atributo1);

    // Escolha do segundo atributo (sem repetir o primeiro)
    do {
        mostrarMenu(atributo1);
        scanf("%d", &atributo2);
        if (atributo2 == atributo1) {
            printf("⚠ Você já escolheu esse atributo. Escolha outro!\n");
        }
    } while (atributo2 == atributo1);

    // Pega valores dos atributos escolhidos
    float v1a1 = valorAtributo(c1, atributo1);
    float v2a1 = valorAtributo(c2, atributo1);
    float v1a2 = valorAtributo(c1, atributo2);
    float v2a2 = valorAtributo(c2, atributo2);

    // Regra: densidade demográfica → menor vence
    int venceu1_a1 = (atributo1 == 5) ? (v1a1 < v2a1) : (v1a1 > v2a1);
    int venceu1_a2 = (atributo2 == 5) ? (v1a2 < v2a2) : (v1a2 > v2a2);

    // Soma dos atributos
    float soma1 = v1a1 + v1a2;
    float soma2 = v2a1 + v2a2;

    // Determina vencedor final
    int vencedorFinal = (soma1 > soma2) ? 1 : (soma2 > soma1 ? 2 : 0);

    // Exibição do resultado
    printf("\n===== RESULTADO =====\n");
    printf("%s vs %s\n", c1.nome, c2.nome);

    printf("\nComparação do atributo %s:\n", nomeAtributo(atributo1));
    printf("%s: %.2f | %s: %.2f → Venceu: %s\n",
           c1.nome, v1a1, c2.nome, v2a1, venceu1_a1 ? c1.nome : c2.nome);

    printf("\nComparação do atributo %s:\n", nomeAtributo(atributo2));
    printf("%s: %.2f | %s: %.2f → Venceu: %s\n",
           c1.nome, v1a2, c2.nome, v2a2, venceu1_a2 ? c1.nome : c2.nome);

    printf("\nSoma dos atributos:\n");
    printf("%s: %.2f | %s: %.2f\n", c1.nome, soma1, c2.nome, soma2);

    if (vencedorFinal == 0)
        printf("\nResultado Final: EMPATE!\n");
    else
        printf("\nResultado Final: %s venceu a rodada!\n", vencedorFinal == 1 ? c1.nome : c2.nome);

    return 0;
}
