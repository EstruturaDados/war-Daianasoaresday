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

/*
================================================================================
         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO (NÍVEL MESTRE)
================================================================================

OBJETIVOS:
- Modularizar completamente o código em funções especializadas.
- Implementar um sistema de missões para um jogador.
- Criar função para verificar se a missão foi cumprida.
- Utilizar passagem por referência (ponteiros) para modificar dados e
  passagem por valor/const para leitura.
- Foco em: design, modularização, const correctness, lógica de jogo.

================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

/* --- Constantes Globais --- */
#define TAM_NOME 30
#define TAM_COR 10

/* Tipos de missão */
#define MISSao_CONQUISTAR_N 0
#define MISSao_DESTRUIR_COR 1
#define MISSao_REUNIR_TROPAS 2

/* --- Estrutura de Dados --- */
/* Representa um território do jogo War */
typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

/* Estrutura para representar uma missão de jogador */
typedef struct {
    int tipo;               /* tipo da missão (0,1,2) */
    int alvoNumero;         /* usado em tipo 0 e 2 (quantidade) */
    char alvoCor[TAM_COR];  /* usado em tipo 1 (cor alvo) */
    char descricao[120];    /* texto descritivo da missão */
} Missao;

/* --- Protótipos das Funções --- */

/* Funções de setup e gerenciamento de memória */
Territorio* alocarMapa(int qtd);
void inicializarTerritorios(Territorio *mapa, int qtd, char cores[][TAM_COR], int numCores);
void liberarMemoria(Territorio *mapa, Missao *missao);

/* Funções de interface com o usuário */
void exibirMenuPrincipal(void);
void exibirMapa(const Territorio *mapa, int qtd);
void exibirMissao(const Missao *missao);

/* Funções de lógica principal do jogo */
void faseDeAtaque(Territorio *mapa, int qtd, const char *corJogador);
void simularAtaque(Territorio *atacante, Territorio *defensor);
Missao* sortearMissao(const char *corJogador, char cores[][TAM_COR], int numCores, int qtdTerritorios);
int verificarVitoria(const Territorio *mapa, int qtd, const Missao *missao, const char *corJogador);

/* Função utilitária */
void limparBufferEntrada(void);

/* ========================= FUNÇÃO PRINCIPAL (main) ========================= */
int main(void) {
    /* 1. Configuração Inicial (Setup) */
    setlocale(LC_ALL, "");           /* define locale para português (se suportado) */
    srand((unsigned int) time(NULL));/* semente para rand() */

    int qtdTerritorios = 0;
    int numCores = 2; /* vamos permitir pelo menos 2 cores/jogadores no exemplo */

    /* cores predefinidas para atribuição inicial */
    char coresDisponiveis[6][TAM_COR] = {
        "Azul", "Vermelho", "Verde", "Amarelo", "Preto", "Branco"
    };

    printf("=== PROJETO WAR ESTRUTURADO ===\n");
    printf("Digite o número total de territórios: ");
    if (scanf("%d", &qtdTerritorios) != 1 || qtdTerritorios <= 0) {
        printf("Entrada inválida. Encerrando.\n");
        return 1;
    }
    limparBufferEntrada();

    /* 1.a) Aloca a memória para o mapa do mundo */
    Territorio *mapa = alocarMapa(qtdTerritorios);
    if (!mapa) {
        fprintf(stderr, "Falha na alocação de memória para o mapa.\n");
        return 1;
    }

    /* 1.b) Inicializa territórios (nomes, cores iniciais alternadas, tropas) */
    inicializarTerritorios(mapa, qtdTerritorios, coresDisponiveis, numCores);

    /* 1.c) Define cor do jogador (no exemplo, jogador único é "Azul") e sorteia missão */
    const char corJogador[TAM_COR] = "Azul";
    Missao *missao = sortearMissao(corJogador, coresDisponiveis, numCores, qtdTerritorios);
    if (!missao) {
        fprintf(stderr, "Falha ao alocar missão.\n");
        liberarMemoria(mapa, NULL);
        return 1;
    }

    /* 2. Laço Principal do Jogo (Game Loop) */
    int opcao;
    do {
        printf("\n========================================\n");
        exibirMapa(mapa, qtdTerritorios);
        printf("\nSua cor: %s\n", corJogador);
        exibirMissao(missao);

        exibirMenuPrincipal();
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) { limparBufferEntrada(); opcao = -1; }
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                /* inicia a fase de ataque: pede origem/destino e chama simulação */
                faseDeAtaque(mapa, qtdTerritorios, corJogador);
                break;

            case 2:
                /* verifica se a missão foi cumprida */
                if (verificarVitoria(mapa, qtdTerritorios, missao, corJogador)) {
                    printf("\n🎉 MISSÃO CUMPRIDA! Parabéns, você venceu.\n");
                } else {
                    printf("\nAinda não cumpriu a missão. Continue jogando.\n");
                }
                break;

            case 0:
                printf("Encerrando o jogo. Liberando recursos...\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

        /* pequena pausa para leitura (pressione Enter) */
        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            getchar();
        }

    } while (opcao != 0);

    /* 3. Limpeza: libera memória alocada */
    liberarMemoria(mapa, missao);

    return 0;
}

/* ========================= IMPLEMENTAÇÃO DAS FUNÇÕES ========================= */

/* alocarMapa():
   Aloca dinamicamente a memória para o vetor de territórios usando calloc.
   Retorna ponteiro para a memória alocada ou NULL em caso de falha.
*/
Territorio* alocarMapa(int qtd) {
    Territorio *mapa = (Territorio*) calloc((size_t)qtd, sizeof(Territorio));
    return mapa;
}

/* inicializarTerritorios():
   Preenche os dados iniciais de cada território no mapa (nome, cor e tropas).
   Atribui cores alternadas entre as primeiras numCores cores do vetor cores[].
   Esta função modifica o mapa passado por referência (ponteiro).
*/
void inicializarTerritorios(Territorio *mapa, int qtd, char cores[][TAM_COR], int numCores) {
    for (int i = 0; i < qtd; ++i) {
        snprintf(mapa[i].nome, TAM_NOME, "Territorio_%d", i);
        /* alterna cor para distribuir inicialmente */
        int idxCor = i % numCores;
        strncpy(mapa[i].cor, cores[idxCor], TAM_COR - 1);
        mapa[i].cor[TAM_COR - 1] = '\0';
        /* tropas iniciais aleatórias entre 2 e 6 */
        mapa[i].tropas = (rand() % 5) + 2;
    }
}

/* liberarMemoria():
   Libera a memória previamente alocada para o mapa e para a missão usando free.
*/
void liberarMemoria(Territorio *mapa, Missao *missao) {
    if (mapa) {
        free(mapa);
        mapa = NULL;
    }
    if (missao) {
        free(missao);
        missao = NULL;
    }
}

/* exibirMenuPrincipal():
   Imprime na tela o menu de ações disponíveis para o jogador.
*/
void exibirMenuPrincipal(void) {
    printf("\n--- MENU PRINCIPAL ---\n");
    printf("1 - Fase de ataque\n");
    printf("2 - Verificar missão (condição de vitória)\n");
    printf("0 - Sair do jogo\n");
}

/* exibirMapa():
   Mostra o estado atual de todos os territórios no mapa, formatado como tabela.
   Usa 'const' para garantir que a função apenas leia os dados do mapa.
*/
void exibirMapa(const Territorio *mapa, int qtd) {
    printf("\n--- MAPA ATUAL ---\n");
    printf("%-4s %-15s %-10s %-7s\n", "IDX", "NOME", "COR", "TROPAS");
    for (int i = 0; i < qtd; ++i) {
        printf("%-4d %-15s %-10s %-7d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

/* exibirMissao():
   Exibe a descrição da missão atual do jogador com base na struct Missao.
*/
void exibirMissao(const Missao *missao) {
    printf("\n--- SUA MISSÃO ---\n");
    if (!missao) {
        printf("Nenhuma missão atribuída.\n");
        return;
    }
    printf("%s\n", missao->descricao);
}

/* faseDeAtaque():
   Gerencia a interface para a ação de ataque: solicita territórios de origem e destino,
   valida entradas (propriedade do território e faixa) e chama simularAtaque() para executar a batalha.
*/
void faseDeAtaque(Territorio *mapa, int qtd, const char *corJogador) {
    int idxOrigem = -1, idxDestino = -1;

    printf("\n--- FASE DE ATAQUE ---\n");
    printf("Digite o índice do território de origem (ou -1 para cancelar): ");
    if (scanf("%d", &idxOrigem) != 1) { limparBufferEntrada(); printf("Entrada inválida.\n"); return; }
    limparBufferEntrada();
    if (idxOrigem == -1) { printf("Ataque cancelado.\n"); return; }

    printf("Digite o índice do território de destino: ");
    if (scanf("%d", &idxDestino) != 1) { limparBufferEntrada(); printf("Entrada inválida.\n"); return; }
    limparBufferEntrada();

    /* validação de índices */
    if (idxOrigem < 0 || idxOrigem >= qtd || idxDestino < 0 || idxDestino >= qtd) {
        printf("Índices fora da faixa válida.\n");
        return;
    }
    if (idxOrigem == idxDestino) {
        printf("Origem e destino devem ser territórios diferentes.\n");
        return;
    }

    Territorio *origem = &mapa[idxOrigem];
    Territorio *destino = &mapa[idxDestino];

    /* validação: jogador só pode atacar a partir de território de sua própria cor */
    if (strcmp(origem->cor, corJogador) != 0) {
        printf("Você só pode atacar a partir de territórios que pertençam à sua cor (%s).\n", corJogador);
        return;
    }

    /* validação: não atacar território da mesma cor */
    if (strcmp(origem->cor, destino->cor) == 0) {
        printf("Não é permitido atacar território da mesma cor.\n");
        return;
    }

    /* validação: precisa ter pelo menos 2 tropas para realizar um ataque efetivo */
    if (origem->tropas < 2) {
        printf("Tropas insuficientes para atacar (mínimo de 2 tropas requerido no território de origem).\n");
        return;
    }

    /* chama a simulação de ataque */
    simularAtaque(origem, destino);
}

/* simularAtaque():
   Executa a lógica de uma batalha entre dois territórios.
   Regras:
   - Rola um dado (1..6) para atacante e defensor.
   - Se atacante > defensor:
        - atacante vence: transfere cor para defensor e transfere metade (atacante->tropas / 2)
          de tropas para o defensor (pelo menos 1). Atacante perde as tropas transferidas.
   - Caso contrário:
        - defensor vence: atacante perde 1 tropa.
   A função modifica diretamente as structs passadas por ponteiro.
*/
void simularAtaque(Territorio *atacante, Territorio *defensor) {
    printf("\nSimulando ataque: %s (%s, %d tropas) -> %s (%s, %d tropas)\n",
           atacante->nome, atacante->cor, atacante->tropas,
           defensor->nome, defensor->cor, defensor->tropas);

    int dadoAtk = rand() % 6 + 1;
    int dadoDef = rand() % 6 + 1;
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtk, dadoDef);

    if (dadoAtk > dadoDef) {
        printf("Atacante venceu!\n");
        /* calcula tropas transferidas: metade das tropas do atacante */
        int tropasTransferidas = atacante->tropas / 2;
        if (tropasTransferidas < 1) tropasTransferidas = 1;

        /* atualiza defensor: ganha cor e recebe tropas transferidas */
        strncpy(defensor->cor, atacante->cor, TAM_COR - 1);
        defensor->cor[TAM_COR - 1] = '\0';
        defensor->tropas = tropasTransferidas;

        /* atualiza atacante: perde as tropas transferidas */
        atacante->tropas -= tropasTransferidas;
        if (atacante->tropas < 0) atacante->tropas = 0;

        printf("Território %s conquistado! Nova cor: %s, tropas: %d\n",
               defensor->nome, defensor->cor, defensor->tropas);
        printf("Tropas restantes no atacante %s: %d\n", atacante->nome, atacante->tropas);
    } else {
        printf("Defensor venceu!\n");
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
        printf("Atacante perdeu 1 tropa. Tropas restantes: %d\n", atacante->tropas);
    }
}

/* sortearMissao():
   Sorteia e retorna (aloca dinamicamente) uma Missao para o jogador.
   Para simplificar há 3 tipos:
   - conquistar N territórios (tipo 0)
   - destruir uma cor alvo (tipo 1)
   - reunir X tropas no total (tipo 2)
   A função usa as cores disponíveis para escolher um alvo possível no tipo 1.
*/
Missao* sortearMissao(const char *corJogador, char cores[][TAM_COR], int numCores, int qtdTerritorios) {
    Missao *m = (Missao*) malloc(sizeof(Missao));
    if (!m) return NULL;

    int tipo = rand() % 3;
    m->tipo = tipo;
    m->alvoNumero = 0;
    m->alvoCor[0] = '\0';
    m->descricao[0] = '\0';

    if (tipo == MISSao_CONQUISTAR_N) {
        int alvo = (qtdTerritorios / 3) + (rand() % 3); /* meta razoável */
        if (alvo < 1) alvo = 1;
        m->alvoNumero = alvo;
        snprintf(m->descricao, sizeof(m->descricao), "Conquistar %d territorios.", alvo);
    } else if (tipo == MISSao_DESTRUIR_COR) {
        /* escolhe uma cor que não seja do jogador, se possível */
        int escolha = (rand() % numCores);
        /* garante que não escolha a cor do jogador */
        int tent = 0;
        while (strcmp(cores[escolha], corJogador) == 0 && tent < 10) {
            escolha = rand() % numCores;
            tent++;
        }
        strncpy(m->alvoCor, cores[escolha], TAM_COR - 1);
        m->alvoCor[TAM_COR - 1] = '\0';
        snprintf(m->descricao, sizeof(m->descricao), "Eliminar a cor %s do mapa.", m->alvoCor);
    } else { /* MISSao_REUNIR_TROPAS */
        int alvo = (qtdTerritorios) + (rand() % (qtdTerritorios / 2 + 1)); /* meta de tropas */
        if (alvo < 1) alvo = 1;
        m->alvoNumero = alvo;
        snprintf(m->descricao, sizeof(m->descricao), "Reunir ao menos %d tropas no total.", alvo);
    }

    return m;
}

/* verificarVitoria():
   Verifica se o jogador cumpriu os requisitos de sua missão atual.
   Implementa a lógica para cada tipo de missão:
   - tipo 0: contar territórios com cor do jogador e comparar com alvoNumero
   - tipo 1: verificar se existe algum território com a cor alvo (se existir -> não cumprida)
   - tipo 2: somar tropas nos territórios do jogador e comparar com alvoNumero
   Retorna 1 se cumprida, 0 caso contrário.
*/
int verificarVitoria(const Territorio *mapa, int qtd, const Missao *missao, const char *corJogador) {
    if (!missao || !mapa) return 0;

    if (missao->tipo == MISSao_CONQUISTAR_N) {
        int cont = 0;
        for (int i = 0; i < qtd; ++i)
            if (strcmp(mapa[i].cor, corJogador) == 0) cont++;
        return (cont >= missao->alvoNumero) ? 1 : 0;
    }
    else if (missao->tipo == MISSao_DESTRUIR_COR) {
        for (int i = 0; i < qtd; ++i)
            if (strcmp(mapa[i].cor, missao->alvoCor) == 0) return 0; /* ainda existe */
        return 1; /* não encontrou -> cumprida */
    }
    else if (missao->tipo == MISSao_REUNIR_TROPAS) {
        int soma = 0;
        for (int i = 0; i < qtd; ++i)
            if (strcmp(mapa[i].cor, corJogador) == 0) soma += mapa[i].tropas;
        return (soma >= missao->alvoNumero) ? 1 : 0;
    }

    return 0;
}

/* limparBufferEntrada():
   Função utilitária para limpar o buffer de entrada do teclado (stdin),
   evitando problemas com leituras consecutivas de scanf e getchar.
*/
void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { /* descarta */ }
}
