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
// Libera memória 

// ============================================================================
//                      PROJETO WAR ESTRUTURADO - NÍVEL AVENTUREIRO
// ============================================================================
// Neste módulo avançamos a implementação do WAR, incluindo:
// - Alocação dinâmica do mapa de territórios
// - Função de ataque modularizada
// - Simulação de dados com rand()
// - Atualização de cor e tropas após batalha
// - Validações de ataque
// - Liberação correta da memória
//
// Este é um passo importante na simulação real do jogo.
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ============================================================================
// ESTRUTURA PRINCIPAL DO PROJETO
// Representa um território do jogo.
// ============================================================================
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ============================================================================
// PROTÓTIPOS DAS FUNÇÕES
// ============================================================================
Territorio* criarMapaDinamico(int qtd);
void inicializarTerritorios(Territorio* mapa, int qtd);
void exibirMapa(const Territorio* mapa, int qtd);

void atacar(Territorio* atacante, Territorio* defensor);

void liberarMemoria(Territorio* mapa);

// ============================================================================
// FUNÇÃO PRINCIPAL
// ============================================================================
int main() {

    srand(time(NULL)); // Algoritmo de aleatoriedade

    int qtd;
    printf("Digite o número total de territórios que deseja criar: ");
    scanf("%d", &qtd);

    // Aloca mapa dinamicamente (calloc zera a memória)
    Territorio* mapa = criarMapaDinamico(qtd);
    if (!mapa) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    inicializarTerritorios(mapa, qtd);

    // LOOP PRINCIPAL
    int escolhaAtk, escolhaDef;

    while (1) {
        printf("\n==================== MAPA ATUAL ====================\n");
        exibirMapa(mapa, qtd);

        printf("\nDigite o número do território atacante (-1 para sair): ");
        scanf("%d", &escolhaAtk);

        if (escolhaAtk == -1) break;

        printf("Agora digite o número do território defensor: ");
        scanf("%d", &escolhaDef);

        // Validação de faixa
        if (escolhaAtk < 0 || escolhaAtk >= qtd ||
            escolhaDef < 0 || escolhaDef >= qtd) {
            printf("Índices inválidos!\n");
            continue;
        }

        Territorio* atacante = &mapa[escolhaAtk];
        Territorio* defensor  = &mapa[escolhaDef];

        // Validação: não atacar território da mesma cor
        if (strcmp(atacante->cor, defensor->cor) == 0) {
            printf("\n❌ Não é possível atacar territórios da mesma cor!\n");
            continue;
        }

        // Chamada da função de ataque
        atacar(atacante, defensor);
    }

    liberarMemoria(mapa);
    return 0;
}

// ============================================================================
// FUNÇÃO: criarMapaDinamico
// Retorna um vetor alocado dinamicamente de Territórios usando calloc.
// ============================================================================
Territorio* criarMapaDinamico(int qtd) {
    return (Territorio*) calloc(qtd, sizeof(Territorio));
}

// ============================================================================
// FUNÇÃO: inicializarTerritorios
// Preenche dados iniciais das estruturas para teste.
// ============================================================================
void inicializarTerritorios(Territorio* mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        snprintf(mapa[i].nome, sizeof(mapa[i].nome), "Territorio_%d", i);
        
        // Alternando cores para testes de ataque
        if (i % 2 == 0)
            strcpy(mapa[i].cor, "Azul");
        else
            strcpy(mapa[i].cor, "Vermelho");

        mapa[i].tropas = rand() % 5 + 2; // Entre 2 e 6 tropas
    }
}

// ============================================================================
// FUNÇÃO: exibirMapa
// Utiliza const para garantir leitura sem modificar dados.
// ============================================================================
void exibirMapa(const Territorio* mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("%2d - %-15s | Cor: %-8s | Tropas: %d\n",
               i,
               mapa[i].nome,
               mapa[i].cor,
               mapa[i].tropas);
    }
}

// ============================================================================
// FUNÇÃO: atacar
// Simula um ataque entre dois territórios usando dados (1 a 6).
//
// REGRAS DO DESAFIO:
// - Se atacante vence: defensor perde, sua cor muda e recebe metade das tropas.
// - Se defensor vence: atacante perde 1 tropa.
// ============================================================================
void atacar(Territorio* atacante, Territorio* defensor) {

    printf("\n===== FASE DE ATAQUE =====\n");
    printf("Atacante: %s (%s) Tropas: %d\n",
           atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s (%s) Tropas: %d\n",
           defensor->nome, defensor->cor, defensor->tropas);

    // Dado de ataque e defesa (1 a 6)
    int dadoAtk = rand() % 6 + 1;
    int dadoDef = rand() % 6 + 1;

    printf("\nDado de ataque: %d\n", dadoAtk);
    printf("Dado de defesa: %d\n", dadoDef);

    if (dadoAtk > dadoDef) {
        printf("\n🎉 O atacante venceu a batalha!\n");

        // Atualização das tropas do defensor
        int tropasTransferidas = atacante->tropas / 2;
        if (tropasTransferidas < 1) tropasTransferidas = 1;

        defensor->tropas = tropasTransferidas;

        // Atualização da cor do defensor
        strcpy(defensor->cor, atacante->cor);

        printf("O território %s foi conquistado!\n", defensor->nome);
        printf("Novas tropas do defensor: %d\n", defensor->tropas);

    } else {
        printf("\n❌ O defensor venceu!\n");
        atacante->tropas--;

        if (atacante->tropas < 0)
            atacante->tropas = 0;

        printf("O atacante perdeu 1 tropa. Tropas restantes: %d\n",
               atacante->tropas);
    }
}

// ============================================================================
// FUNÇÃO: liberarMemoria
// Libera o vetor alocado dinamicamente.
// ============================================================================
void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("\nMemória liberada com sucesso.\n");
}
