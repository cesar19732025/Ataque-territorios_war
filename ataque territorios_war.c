#include <stdio.h>
#include <string.h>

/*
    Programa: Cadastro de Territórios
    Autor: [Seu Nome]
    Descrição:
        Este programa demonstra o uso de struct em C para armazenar informações
        sobre territórios em um jogo ou simulação. Ele permite o cadastro de 5
        territórios, armazenando o nome, a cor do exército e a quantidade de tropas.
        Após o cadastro, todos os territórios são exibidos na tela.
*/

// Definição da estrutura que representa um território
struct Territorio {
    char nome[30];     // Nome do territorio
    char cor[10];      // Cor do exercito associado
    int tropas;        // Quantidade de tropas alocadas
};

int main() {
    // Declaração de um vetor para armazenar 5 territórios

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
    Programa: Simulação de Ataques entre Territórios
    Autor: [Seu Nome]
    Descrição:
        - Aloca dinamicamente um vetor de Territorio (usando calloc).
        - Permite cadastro de N territórios (nome, cor, tropas).
        - Permite ao jogador escolher atacante e defensor para simular ataque
          via dados (1..6) usando rand().
        - Se atacante vencer: defensor muda de cor para a do atacante e recebe
          metade das tropas do atacante (transferência).
        - Se atacante perder: atacante perde 1 tropa.
        - Tudo é manipulado por ponteiros e memória liberada no fim.
*/

/* Definição da estrutura Territorio */
typedef struct {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército (dono)
    int tropas;      // Quantidade de tropas
} Territorio;

/* Protótipos */
Territorio* alocarTerritorios(int n);
void cadastrarTerritorios(Territorio* mapa, int n);
void exibirTerritorios(Territorio* mapa, int n);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);
int lerInteiro(const char* prompt, int min, int max);

int main() {
    srand((unsigned int)time(NULL)); // Garantir aleatoriedade para rand()

    printf("=== SISTEMA DE TERRITORIOS (SIMULACAO DE ATAQUES) ===\n");

    int n = lerInteiro("Informe o numero total de territorios: ", 1, 200);

    /* Alocação dinâmica do vetor de territórios */
    Territorio* mapa = alocarTerritorios(n);
    if (!mapa) {
        fprintf(stderr, "Erro: memoria insuficiente.\n");
        return 1;
    }

    /* Cadastro */
    cadastrarTerritorios(mapa, n);

    /* Menu interativo: exibir, atacar, sair */
    int opcao;
    do {
        printf("\nMenu:\n");
        printf(" 1 - Exibir territorios\n");
        printf(" 2 - Realizar ataque\n");
        printf(" 3 - Sair\n");
        opcao = lerInteiro("Escolha uma opcao: ", 1, 3);

        if (opcao == 1) {
            exibirTerritorios(mapa, n);
        } else if (opcao == 2) {
            exibirTerritorios(mapa, n);
            int atk_idx = lerInteiro("Indice do territorio atacante (1..n): ", 1, n) - 1;
            int def_idx = lerInteiro("Indice do territorio defensor (1..n): ", 1, n) - 1;

            /* Validacoes:
               - indices diferentes
               - cores diferentes (nao atacar proprio territorio)
               - atacante deve ter tropas suficientes (pelo menos 1).
               Opcional: exigir >1 tropa para transferir metade; aqui permitimos ataque
               se tiver >=1 tropa, mas se tiver 1 tropa a transferencia sera 0 e nao sera permitida.
            */
            Territorio* atacante = mapa + atk_idx;
            Territorio* defensor = mapa + def_idx;

            if (atk_idx == def_idx) {
                printf("Erro: atacante e defensor sao o mesmo territorio.\n");
                continue;
            }
            if (strcmp(atacante->cor, defensor->cor) == 0) {
                printf("Erro: nao e permitido atacar um territorio da propria cor.\n");
                continue;
            }
            if (atacante->tropas <= 0) {
                printf("Erro: atacante nao possui tropas suficientes para atacar.\n");
                continue;
            }

            /* Realiza o ataque (passando ponteiros) */
            atacar(atacante, defensor);

            /* Exibe os dois territorios envolvidos após o ataque */
            printf("\n>>> Estado apos o ataque <<<\n");
            printf("Atacante '%s' - Cor: %s - Tropas: %d\n", atacante->nome, atacante->cor, atacante->tropas);
            printf("Defensor  '%s' - Cor: %s - Tropas: %d\n", defensor->nome, defensor->cor, defensor->tropas);
        }
    } while (opcao != 3);

    /* Liberar memoria */
    liberarMemoria(mapa);

    printf("Programa finalizado. Memoria liberada.\n");
    return 0;
}

/* Aloca dinamicamente um vetor de Territorio com calloc e retorna o ponteiro */
Territorio* alocarTerritorios(int n) {
    Territorio* mapa = (Territorio*) calloc((size_t)n, sizeof(Territorio));
    return mapa; /* NULL se falhar */
}

/* Função para cadastro dos territorios.
   Usa ponteiro (mapa) e preenche cada posicao */
void cadastrarTerritorios(Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        Territorio* t = mapa + i; // acesso via ponteiro
        printf("\nCadastro do %do territorio:\n", i + 1);

        printf("Nome (sem espacos) (max 29 chars): ");
        if (scanf("%29s", t->nome) != 1) {
            /* limpar buffer e definir nome padrao se falhar */
            strcpy(t->nome, "Territorio");
        }

        printf("Cor do exercito (max 9 chars): ");
        if (scanf("%9s", t->cor) != 1) {
            strcpy(t->cor, "Neutro");
        }

        t->tropas = lerInteiro("Quantidade de tropas (>=0): ", 0, 1000000);
    }
}

/* Exibe todos os territorios do mapa. Acessa por ponteiros. */
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n=== TERRITORIOS CADASTRADOS ===\n");
    for (int i = 0; i < n; i++) {
        Territorio* t = mapa + i;
        printf("Indice %d:\n", i + 1);
        printf(" Nome: %s\n", t->nome);
        printf(" Cor do exercito: %s\n", t->cor);
        printf(" Tropas: %d\n", t->tropas);
        printf("-------------------------------------\n");
    }
}

/*
    Função de ataque:
    - Recebe ponteiros para atacante e defensor.
    - Simula uma rolagem de dado (1..6) para cada um usando rand().
    - Se atacante ganhar (valor maior): defensor muda de dono (cor) para a do atacante,
      e recebe metade (inteiro) das tropas do atacante — ou seja:
         transfer = atacante->tropas / 2;
         defensor->tropas = transfer;
         atacante->tropas -= transfer;
      (Garantimos que transfer >= 1 para que a mudança faça sentido; se transfer == 0,
       consideramos o ataque inválido e o atacante perde 1 tropa).
    - Se atacante perder (ou empatar), atacante perde 1 tropa (min 0).
*/
void atacar(Territorio* atacante, Territorio* defensor) {
    int dado_atk = (rand() % 6) + 1; // 1..6
    int dado_def = (rand() % 6) + 1; // 1..6

    printf("\nRolagem: Atacante '%s' (cor %s) -> Dado: %d\n", atacante->nome, atacante->cor, dado_atk);
    printf("         Defensor  '%s' (cor %s) -> Dado: %d\n", defensor->nome, defensor->cor, dado_def);

    if (dado_atk > dado_def) {
        /* atacante vence */
        int transfer = atacante->tropas / 2; // metade inteira das tropas do atacante
        if (transfer <= 0) {
            /* não dá pra transferir tropas; atacante perde 1 tropa */
            printf("Atacante venceu a rolagem, mas nao havia tropas suficientes para transferir.\n");
            if (atacante->tropas > 0) atacante->tropas -= 1;
            return;
        }

        /* Transferir cor e tropas para o defensor */
        strncpy(defensor->cor, atacante->cor, sizeof(defensor->cor) - 1);
        defensor->cor[sizeof(defensor->cor) - 1] = '\0';

        /* Atualiza tropas do defensor e do atacante */
        defensor->tropas = transfer;
        atacante->tropas -= transfer;

        /* Garantia: atacante nao pode ficar negativo */
        if (atacante->tropas < 0) atacante->tropas = 0;

        printf("Resultado: Atacante venceu! Territorio '%s' agora pertence a '%s' e recebeu %d tropas.\n",
               defensor->nome, defensor->cor, defensor->tropas);
    } else {
        /* Empate ou defensor vence */
        printf("Resultado: Atacante perdeu (ou empatou). Atacante perde 1 tropa.\n");
        if (atacante->tropas > 0) atacante->tropas -= 1;
    }
}

/* Libera a memoria alocada para o mapa */
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

/* Le um inteiro com prompt e valida entre min e max */
int lerInteiro(const char* prompt, int min, int max) {
    int valor;
    int ok;
    do {
        printf("%s", prompt);
        ok = (scanf("%d", &valor) == 1);
        if (!ok) {
            /* limpar buffer */
            int c;
            while ((c = getchar()) != EOF && c != '\n');
            printf("Entrada invalida. Tente novamente.\n");
            continue;
        }
        if (valor < min || valor > max) {
            printf("Valor fora do intervalo (%d..%d). Tente novamente.\n", min, max);
            ok = 0;
        }
    } while (!ok);
    return valor;
}
