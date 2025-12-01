// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
// ============================================================================
//                      PROJETO WAR ESTRUTURADO - NÍVEL NOVATO
// ============================================================================
// Este código organiza um pequeno sistema baseado no jogo War,
// incluindo alocação dinâmica de territórios, exibição, missão
// sorteada e menu básico.
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIOS 5
#define TAM_NOME 50
#define NUM_MISSOES 2

// ============================================================================
// ESTRUTURA DE DADOS PRINCIPAL
// Representa um território: nome, cor (dono) e tropas.
// ============================================================================
typedef struct {
    char nome[TAM_NOME];
    char cor[20];
    int tropas;
} Territorio;

// ============================================================================
// PROTÓTIPOS DAS FUNÇÕES
// ============================================================================

// Setup e memória
Territorio* alocarMapa(int qtd);
void inicializarTerritorios(Territorio *mapa, int qtd);
void liberarMemoria(Territorio *mapa);

// Interface
void exibirMenuPrincipal();
void exibirMapa(const Territorio *mapa, int qtd);
void exibirMissao(int idMissao);

// Lógica principal
void faseDeAtaque(Territorio *mapa, int qtd);
void simularAtaque(Territorio *origem, Territorio *destino);
int sortearMissao();
int verificarVitoria(const Territorio *mapa, int qtd, int idMissao);

// Utilidades
void limparBufferEntrada();

// ============================================================================
// FUNÇÃO PRINCIPAL
// ============================================================================
int main() {
    srand(time(NULL));

    // 1) Allocação dinâmica do mapa
    Territorio *mapa = alocarMapa(MAX_TERRITORIOS);
    if (!mapa) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // 2) Inicializa dados do mapa
    inicializarTerritorios(mapa, MAX_TERRITORIOS);

    // 3) Sorteia missão secreta
    int missao = sortearMissao();

    // 4) Laço principal do jogo
    int opcao;
    do {
        printf("\n====================================\n");
        exibirMapa(mapa, MAX_TERRITORIOS);
        exibirMissao(missao);
        exibirMenuPrincipal();
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                faseDeAtaque(mapa, MAX_TERRITORIOS);
                break;

            case 2:
                if (verificarVitoria(mapa, MAX_TERRITORIOS, missao))
                    printf("\n🎉 Você CUMPRIU sua missão!\n");
                else
                    printf("\nAinda não cumpriu a missão.\n");
                break;

            case 0:
                printf("Saindo do jogo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    // 5) Libera memória
    liberarMemoria(mapa);

    return 0;
}

// ============================================================================
// IMPLEMENTAÇÃO DAS FUNÇÕES
// ============================================================================

// Aloca o vetor de territórios
Territorio* alocarMapa(int qtd) {
    return (Territorio*) calloc(qtd, sizeof(Territorio));
}

// Inicializa os territórios com valores básicos
void inicializarTerritorios(Territorio *mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        snprintf(mapa[i].nome, TAM_NOME, "Território %d", i + 1);
        strcpy(mapa[i].cor, "Azul");
        mapa[i].tropas = 3;
    }
}

// Libera memória
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

// Exibe menu principal
void exibirMenuPrincipal() {
    printf("\n--- MENU ---\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar missão\n");
    printf("0 - Sair\n");
}

// Exibe tabela de territórios
void exibirMapa(const Territorio *mapa, int qtd) {
    printf("\n--- MAPA ATUAL ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d) %-15s | Dono: %-6s | Tropas: %d\n",
               i + 1,
               mapa[i].nome,
               mapa[i].cor,
               mapa[i].tropas);
    }
}

// Exibe a missão sorteada
void exibirMissao(int idMissao) {
    printf("\n--- SUA MISSÃO ---\n");
    switch (idMissao) {
        case 0:
            printf("Conquistar 1 território.\n");
            break;
        case 1:
            printf("Manter todos os seus territórios com pelo menos 3 tropas.\n");
            break;
    }
}

// Interface da fase de ataque
void faseDeAtaque(Territorio *mapa, int qtd) {
    int o, d;

    printf("\nDigite número do território de origem: ");
    scanf("%d", &o);
    printf("Digite número do território de destino: ");
    scanf("%d", &d);
    limparBufferEntrada();

    o--; d--;

    if (o < 0 || o >= qtd || d < 0 || d >= qtd) {
        printf("Índices inválidos!\n");
        return;
    }

    simularAtaque(&mapa[o], &mapa[d]);
}

// Lógica simplificada de batalha
void simularAtaque(Territorio *origem, Territorio *destino) {
    if (origem->tropas < 2) {
        printf("Não há tropas suficientes para atacar!\n");
        return;
    }

    int dadoAtk = rand() % 6 + 1;
    int dadoDef = rand() % 6 + 1;

    printf("\nAtaque lançou: %d | Defesa lançou: %d\n", dadoAtk, dadoDef);

    if (dadoAtk > dadoDef) {
        printf("Vitória no ataque! Destino perde 1 tropa.\n");
        destino->tropas--;

        if (destino->tropas <= 0) {
            printf("🎉 Território CONQUISTADO!\n");
            strcpy(destino->cor, origem->cor);
            destino->tropas = 1;
            origem->tropas--;
        }
    } else {
        printf("Defesa venceu! Origem perde 1 tropa.\n");
        origem->tropas--;
    }
}

// Sorteia missão
int sortearMissao() {
    return rand() % NUM_MISSOES;
}

// Verifica se o jogador venceu
int verificarVitoria(const Territorio *mapa, int qtd, int idMissao) {
    switch (idMissao) {

        case 0: // Conquistar 1 território
            for (int i = 0; i < qtd; i++)
                if (strcmp(mapa[i].cor, "Azul") == 0 && mapa[i].tropas > 3)
                    return 1;
            return 0;

        case 1: // Todos com >= 3 tropas
            for (int i = 0; i < qtd; i++)
                if (mapa[i].tropas < 3)
                    return 0;
            return 1;
    }
    return 0;
}

// Limpa buffer do teclado
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
