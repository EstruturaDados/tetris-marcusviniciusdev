#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack - Nível Novato
// Tema 3 - Fila Circular de Peças

#define MAX_FILA 5

// Struct para representar uma peça
typedef struct {
    char tipo;
    int id;
} Peca;

// Struct para a fila circular
typedef struct {
    Peca pecas[MAX_FILA];
    int frente;
    int tras;
    int tamanho;
} FilaCircular;

// Contador global de IDs
int contadorId = 1;

// Função para gerar uma peça aleatória
Peca gerarPeca() {
    Peca novaPeca;
    char tipos[] = {'I', 'O', 'T', 'L'};
    novaPeca.tipo = tipos[rand() % 4];
    novaPeca.id = contadorId++;
    return novaPeca;
}

// Inicializar a fila circular
void inicializarFila(FilaCircular *fila) {
    fila->frente = 0;
    fila->tras = -1;
    fila->tamanho = 0;
}

// Verificar se a fila está cheia
int filaCheia(FilaCircular *fila) {
    return fila->tamanho == MAX_FILA;
}

// Verificar se a fila está vazia
int filaVazia(FilaCircular *fila) {
    return fila->tamanho == 0;
}

// Inserir peça na fila (enqueue)
void enqueue(FilaCircular *fila, Peca peca) {
    if (filaCheia(fila)) {
        printf("Erro: A fila está cheia!\n");
        return;
    }
    fila->tras = (fila->tras + 1) % MAX_FILA;
    fila->pecas[fila->tras] = peca;
    fila->tamanho++;
}

// Remover peça da fila (dequeue)
Peca dequeue(FilaCircular *fila) {
    Peca pecaRemovida;
    if (filaVazia(fila)) {
        printf("Erro: A fila está vazia!\n");
        pecaRemovida.tipo = '\0';
        pecaRemovida.id = -1;
        return pecaRemovida;
    }
    pecaRemovida = fila->pecas[fila->frente];
    fila->frente = (fila->frente + 1) % MAX_FILA;
    fila->tamanho--;
    return pecaRemovida;
}

// Mostrar a fila atual
void mostrarFila(FilaCircular *fila) {
    if (filaVazia(fila)) {
        printf("\n🎮 Fila de Peças: [VAZIA]\n");
        return;
    }

    printf("\n🎮 Fila de Peças (Total: %d):\n", fila->tamanho);
    printf("┌────────────────────────────────────┐\n");

    int i, indice;
    for (i = 0; i < fila->tamanho; i++) {
        indice = (fila->frente + i) % MAX_FILA;
        printf("│ [%d] Tipo: %c | ID: %d", i + 1, fila->pecas[indice].tipo, fila->pecas[indice].id);
        if (i == 0) {
            printf(" ← Próxima");
        }
        printf("\n");
    }

    printf("└────────────────────────────────────┘\n");
}

int main() {
    FilaCircular fila;
    int opcao;

    // Inicializar gerador de números aleatórios
    srand(time(NULL));

    // Inicializar a fila
    inicializarFila(&fila);

    // Preencher a fila com 5 peças iniciais
    printf("🎮 Bem-vindo ao Tetris Stack - Nível Novato!\n");
    printf("Inicializando fila com 5 peças...\n");

    for (int i = 0; i < MAX_FILA; i++) {
        Peca novaPeca = gerarPeca();
        enqueue(&fila, novaPeca);
    }

    mostrarFila(&fila);

    // Loop principal do jogo
    do {
        printf("\n╔════════════════════════════════════╗\n");
        printf("║         MENU PRINCIPAL             ║\n");
        printf("╠════════════════════════════════════╣\n");
        printf("║ 1 - Jogar peça (remover da frente) ║\n");
        printf("║ 0 - Sair                           ║\n");
        printf("╚════════════════════════════════════╝\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                if (!filaVazia(&fila)) {
                    Peca pecaJogada = dequeue(&fila);
                    printf("\n✅ Peça jogada: Tipo %c | ID %d\n", pecaJogada.tipo, pecaJogada.id);

                    // Inserir nova peça automaticamente
                    Peca novaPeca = gerarPeca();
                    enqueue(&fila, novaPeca);
                    printf("➕ Nova peça adicionada: Tipo %c | ID %d\n", novaPeca.tipo, novaPeca.id);

                    mostrarFila(&fila);
                } else {
                    printf("\n❌ Não há peças para jogar!\n");
                }
                break;
            }
            case 0:
                printf("\n👋 Saindo do jogo. Até logo!\n");
                break;
            default:
                printf("\n❌ Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
