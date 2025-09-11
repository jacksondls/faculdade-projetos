#include <stdio.h>

// Estrutura para armazenar os dados da carta
typedef struct {
    char estado[30];
    char codigo[10];
    char nome[30];
    unsigned long int populacao; // agora é unsigned long int
    float area;
    float pib;
    int pontos_turisticos;
    float densidade;
    float pib_per_capita;
    float super_poder;
} Carta;

// Função para calcular os atributos derivados
void calcularAtributos(Carta *c) {
    c->densidade = (float)c->populacao / c->area;
    c->pib_per_capita = c->pib / (float)c->populacao;

    // Super Poder = soma de todos os atributos relevantes
    // (quanto menor a densidade, maior o poder → usamos 1/densidade)
    c->super_poder = (float)c->populacao 
                   + c->area 
                   + c->pib 
                   + (float)c->pontos_turisticos
                   + c->pib_per_capita
                   + (1.0f / c->densidade);
}

// Função para comparar dois atributos e imprimir o vencedor
void compararAtributo(char *nome, float valor1, float valor2, int menorVence) {
    int venceuCarta1;

    if (menorVence) {
        venceuCarta1 = valor1 < valor2; // menor vence
    } else {
        venceuCarta1 = valor1 > valor2; // maior vence
    }

    printf("%s: Carta %d venceu (%d)\n", nome, venceuCarta1 ? 1 : 2, venceuCarta1);
}

int main() {
    Carta c1, c2;

    // Entrada dos dados das duas cartas
    printf("=== Cadastro da Carta 1 ===\n");
    printf("Estado: "); scanf(" %[^\n]", c1.estado);
    printf("Código: "); scanf(" %s", c1.codigo);
    printf("Nome da cidade: "); scanf(" %[^\n]", c1.nome);
    printf("População: "); scanf("%lu", &c1.populacao);
    printf("Área: "); scanf("%f", &c1.area);
    printf("PIB: "); scanf("%f", &c1.pib);
    printf("Número de pontos turísticos: "); scanf("%d", &c1.pontos_turisticos);

    printf("\n=== Cadastro da Carta 2 ===\n");
    printf("Estado: "); scanf(" %[^\n]", c2.estado);
    printf("Código: "); scanf(" %s", c2.codigo);
    printf("Nome da cidade: "); scanf(" %[^\n]", c2.nome);
    printf("População: "); scanf("%lu", &c2.populacao);
    printf("Área: "); scanf("%f", &c2.area);
    printf("PIB: "); scanf("%f", &c2.pib);
    printf("Número de pontos turísticos: "); scanf("%d", &c2.pontos_turisticos);

    // Cálculo dos atributos derivados
    calcularAtributos(&c1);
    calcularAtributos(&c2);

    // Comparação dos atributos
    printf("\n=== Comparação de Cartas ===\n");
    compararAtributo("População", (float)c1.populacao, (float)c2.populacao, 0);
    compararAtributo("Área", c1.area, c2.area, 0);
    compararAtributo("PIB", c1.pib, c2.pib, 0);
    compararAtributo("Pontos Turísticos", (float)c1.pontos_turisticos, (float)c2.pontos_turisticos, 0);
    compararAtributo("Densidade Populacional", c1.densidade, c2.densidade, 1); // menor vence
    compararAtributo("PIB per Capita", c1.pib_per_capita, c2.pib_per_capita, 0);
    compararAtributo("Super Poder", c1.super_poder, c2.super_poder, 0);

    return 0;
}
