#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack - Nível Mestre
// Tema 3 - Integração Total entre Fila Circular e Pilha de Reserva

#define MAX_FILA 5
#define MAX_PILHA 3

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

// Struct para a pilha de reserva
typedef struct {
    Peca pecas[MAX_PILHA];
    int topo;
} PilhaReserva;

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

// Inicializar a pilha
void inicializarPilha(PilhaReserva *pilha) {
    pilha->topo = -1;
}

// Verificar se a pilha está cheia
int pilhaCheia(PilhaReserva *pilha) {
    return pilha->topo == MAX_PILHA - 1;
}

// Verificar se a pilha está vazia
int pilhaVazia(PilhaReserva *pilha) {
    return pilha->topo == -1;
}

// Inserir peça na pilha (push)
void push(PilhaReserva *pilha, Peca peca) {
    if (pilhaCheia(pilha)) {
        printf("Erro: A pilha de reserva está cheia!\n");
        return;
    }
    pilha->topo++;
    pilha->pecas[pilha->topo] = peca;
}

// Remover peça da pilha (pop)
Peca pop(PilhaReserva *pilha) {
    Peca pecaRemovida;
    if (pilhaVazia(pilha)) {
        printf("Erro: A pilha de reserva está vazia!\n");
        pecaRemovida.tipo = '\0';
        pecaRemovida.id = -1;
        return pecaRemovida;
    }
    pecaRemovida = pilha->pecas[pilha->topo];
    pilha->topo--;
    return pecaRemovida;
}

// Mostrar a pilha de reserva
void mostrarPilha(PilhaReserva *pilha) {
    if (pilhaVazia(pilha)) {
        printf("\n📦 Pilha de Reserva: [VAZIA]\n");
        return;
    }

    printf("\n📦 Pilha de Reserva (Total: %d/%d):\n", pilha->topo + 1, MAX_PILHA);
    printf("┌────────────────────────────────────┐\n");

    for (int i = pilha->topo; i >= 0; i--) {
        printf("│ Tipo: %c | ID: %d", pilha->pecas[i].tipo, pilha->pecas[i].id);
        if (i == pilha->topo) {
            printf(" ← Topo");
        }
        printf("\n");
    }

    printf("└────────────────────────────────────┘\n");
}

// Trocar a peça da frente da fila com o topo da pilha
void trocarFrenteTopo(FilaCircular *fila, PilhaReserva *pilha) {
    if (filaVazia(fila)) {
        printf("\n❌ Não é possível trocar: a fila está vazia!\n");
        return;
    }
    if (pilhaVazia(pilha)) {
        printf("\n❌ Não é possível trocar: a pilha está vazia!\n");
        return;
    }

    // Trocar os elementos
    Peca temp = fila->pecas[fila->frente];
    fila->pecas[fila->frente] = pilha->pecas[pilha->topo];
    pilha->pecas[pilha->topo] = temp;

    printf("\n🔄 Troca realizada com sucesso!\n");
    printf("   Frente da fila ↔️ Topo da pilha\n");
}

// Trocar os 3 primeiros da fila com as 3 peças da pilha
void trocarTresPrimeiros(FilaCircular *fila, PilhaReserva *pilha) {
    if (fila->tamanho < 3) {
        printf("\n❌ Não é possível trocar: a fila tem menos de 3 peças! (Atual: %d)\n", fila->tamanho);
        return;
    }
    if ((pilha->topo + 1) != MAX_PILHA) {
        printf("\n❌ Não é possível trocar: a pilha deve ter exatamente 3 peças! (Atual: %d)\n", pilha->topo + 1);
        return;
    }

    printf("\n🔄 Trocando os 3 primeiros da fila com as 3 peças da pilha...\n");

    // Criar array temporário para as peças da fila
    Peca tempFila[3];

    // Copiar os 3 primeiros da fila
    for (int i = 0; i < 3; i++) {
        int indice = (fila->frente + i) % MAX_FILA;
        tempFila[i] = fila->pecas[indice];
    }

    // Mover peças da pilha para a fila
    for (int i = 0; i < 3; i++) {
        int indice = (fila->frente + i) % MAX_FILA;
        fila->pecas[indice] = pilha->pecas[2 - i]; // Inverte a ordem (pilha é LIFO)
    }

    // Mover peças da fila temporária para a pilha
    for (int i = 0; i < 3; i++) {
        pilha->pecas[i] = tempFila[2 - i]; // Inverte a ordem
    }

    printf("✅ Troca dos 3 primeiros realizada com sucesso!\n");
}

int main() {
    FilaCircular fila;
    PilhaReserva pilha;
    int opcao;

    // Inicializar gerador de números aleatórios
    srand(time(NULL));

    // Inicializar a fila e a pilha
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Preencher a fila com 5 peças iniciais
    printf("🎮 Bem-vindo ao Tetris Stack - Nível Mestre!\n");
    printf("Inicializando fila com 5 peças...\n");

    for (int i = 0; i < MAX_FILA; i++) {
        Peca novaPeca = gerarPeca();
        enqueue(&fila, novaPeca);
    }

    mostrarFila(&fila);
    mostrarPilha(&pilha);

    // Loop principal do jogo
    do {
        printf("\n╔═══════════════════════════════════════════════╗\n");
        printf("║            MENU PRINCIPAL - NÍVEL MESTRE      ║\n");
        printf("╠═══════════════════════════════════════════════╣\n");
        printf("║ 1 - Jogar peça (remover da frente)            ║\n");
        printf("║ 2 - Reservar peça (enviar para pilha)         ║\n");
        printf("║ 3 - Usar peça reservada (remover da pilha)    ║\n");
        printf("║ 4 - Trocar frente da fila com topo da pilha   ║\n");
        printf("║ 5 - Trocar 3 primeiros da fila com pilha      ║\n");
        printf("║ 0 - Sair                                      ║\n");
        printf("╚═══════════════════════════════════════════════╝\n");
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
                    mostrarPilha(&pilha);
                } else {
                    printf("\n❌ Não há peças para jogar!\n");
                }
                break;
            }
            case 2: {
                if (!filaVazia(&fila) && !pilhaCheia(&pilha)) {
                    Peca pecaReservada = dequeue(&fila);
                    push(&pilha, pecaReservada);
                    printf("\n📦 Peça reservada: Tipo %c | ID %d\n", pecaReservada.tipo, pecaReservada.id);

                    // Inserir nova peça automaticamente na fila
                    Peca novaPeca = gerarPeca();
                    enqueue(&fila, novaPeca);
                    printf("➕ Nova peça adicionada na fila: Tipo %c | ID %d\n", novaPeca.tipo, novaPeca.id);

                    mostrarFila(&fila);
                    mostrarPilha(&pilha);
                } else if (pilhaCheia(&pilha)) {
                    printf("\n❌ A pilha de reserva está cheia! (Máximo: %d peças)\n", MAX_PILHA);
                } else {
                    printf("\n❌ Não há peças na fila para reservar!\n");
                }
                break;
            }
            case 3: {
                if (!pilhaVazia(&pilha)) {
                    Peca pecaUsada = pop(&pilha);
                    printf("\n✅ Peça reservada usada: Tipo %c | ID %d\n", pecaUsada.tipo, pecaUsada.id);

                    mostrarFila(&fila);
                    mostrarPilha(&pilha);
                } else {
                    printf("\n❌ Não há peças na pilha de reserva!\n");
                }
                break;
            }
            case 4: {
                trocarFrenteTopo(&fila, &pilha);
                if (!filaVazia(&fila) && !pilhaVazia(&pilha)) {
                    mostrarFila(&fila);
                    mostrarPilha(&pilha);
                }
                break;
            }
            case 5: {
                trocarTresPrimeiros(&fila, &pilha);
                if (fila.tamanho >= 3 && (pilha.topo + 1) == MAX_PILHA) {
                    mostrarFila(&fila);
                    mostrarPilha(&pilha);
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
