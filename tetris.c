#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define TAM_FILA 5 // Tamanho fixo da fila

// --------------------------------------------------------
// Struct que representa cada peça
// 
typedef struct{
    char nome;      // Índice do primeiro elemento
    int id;      // Identificador único
} Peca;

// --------------------------------------------------------
// Fila circular
// --------------------------------------------------------
typedef struct{
    Peca itens[TAM_FILA];
    int frente;      // Índice do primeiro elemento
    int tras;        // Índice do último elemento
    int quantidade;  // Número de elementos na fila
} Fila;

// --------------------------------------------------------
// Função que inicializa a fila
// --------------------------------------------------------
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->quantidade = 0;
}

// --------------------------------------------------------
// Função que gera automaticamente uma peça nova
// --------------------------------------------------------
Peca gerarPeca(int id) {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = id;

    return p;
}

// --------------------------------------------------------
// Verifica se a fila está cheia
// --------------------------------------------------------
int filaCheia(Fila *f) {
    return f->quantidade == TAM_FILA;
}

// --------------------------------------------------------
// Verifica se a fila está vazia
// --------------------------------------------------------
int filaVazia(Fila *f) {
    return f->quantidade == 0;
}

// --------------------------------------------------------
// Enfileirar (inserir nova peça)
// --------------------------------------------------------
void enqueue(Fila *f, Peca p) {
    if(filaCheia(f)) {
        printf("A fila está cheia! Não é possível inserir uma nova peça.\n");
        return;
    }

    f->tras = (f->tras + 1) % TAM_FILA;
    f->itens[f->tras] = p;
    f->quantidade++;

    printf("Peça [%c %d] inserida com sucesso.\n", p.nome, p.id);
}

// --------------------------------------------------------
// Desenfileirar (jogar peça)
// --------------------------------------------------------
void dequeue(Fila *f) {
    if(filaVazia(f)) {
        printf("A fila está vazia! Nenhuma peça para jogar.\n");
        return;
    }

    Peca removida = f->itens[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    f->quantidade--;

    printf("Peça jogada: [%c %d]\n", removida.nome, removida.id);
}

// --------------------------------------------------------
// Exibir estado atual da fila
// --------------------------------------------------------
void exibirFila(Fila *f) {
    printf("\n--- Fila de Peças ---\n");

    if(filaVazia(f)) {
        printf("(vazia)\n");
        return;
    }

    int i = f->frente;

    for (int cont = 0; cont < f->quantidade; cont++) {
        Peca p = f->itens[i];
        printf("[%c %d] ", p.nome, p.id);
        i = (i + 1)  % TAM_FILA;
    }

    printf("\n");
}

// --------------------------------------------------------
// Programa principal
// --------------------------------------------------------
int main() {
    Fila fila;
    inicializarFila(&fila);

    srand(time(NULL));

    int idAtual = 0;

    // Inicializa fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca(idAtual++));
    }

    int opcao;

    do {
        exibirFila(&fila);

        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue(&fila);
                break;

            case 2:
                enqueue(&fila, gerarPeca(idAtual++));
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}