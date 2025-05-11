#include "uart.h"     // Para usar uart_getchar() e verificar teclas
#include "printf.h"   // Para imprimir na tela
#include "defs.h"     // Outras definições do kernel

#define WIDTH  20     // Largura do "mapa" (área de jogo)
#define HEIGHT 10     // Altura do mapa
#define MAX_LEN 100   // Tamanho máximo da cobrinha

// Direções possíveis da cobrinha
#define UP    0
#define DOWN  1
#define LEFT  2
#define RIGHT 3

// Struct que representa uma posição (coordenadas X e Y)
typedef struct {
    int x;
    int y;
} Pos;

//vetor que representa o corpo da cobrinha
Pos snake[MAX_LEN];;///Cobrihnha
int snake_len = 4; //comprimento inicial da cobrinha
int direction = RIGHT; //direnção inicial 
Pos apple; //poisção da maçã
int score = 0;  // Inicializa a pontuação
int game_over = 0; // Flag de fim de jogo
int sleep_time = 15000000;  // padrão = normal



// Função responsável por desenhar o estado atual do jogo no terminal
// Função responsável por desenhar o estado atual do jogo no terminal
void draw_screen() {
    // Move o cursor para o canto superior esquerdo (linha 1, coluna 1)
    // Isso permite redesenhar o jogo sobre a tela anterior sem precisar limpar tudo
    printf("\033[H"); 

    // ───── Borda superior ─────
    printf("+");                          // Canto superior esquerdo
    for (int x = 0; x < WIDTH; x++)       // Linha horizontal do topo
        printf("-");
    printf("+\n");                        // Canto superior direito + quebra de linha

    // ───── Corpo do mapa ─────
    for (int y = 0; y < HEIGHT; y++) {
        printf("|");  // Borda esquerda da linha atual

        for (int x = 0; x < WIDTH; x++) {
            int printed = 0;  // Flag que indica se já imprimimos algo nesta célula

            // Se esta é a posição da maçã, imprime ela
            if (x == apple.x && y == apple.y) {
                printf("@"); 
                printed = 1;
            }

            // Verifica se essa posição pertence à cobrinha
            for (int i = 0; i < snake_len; i++) {
                if (snake[i].x == x && snake[i].y == y) {
                    // Cabeça da cobrinha recebe 'O', corpo recebe 'o'
                    printf(i == 0 ? "O" : "o");
                    printed = 1;
                    break; // já encontramos e imprimimos, não precisa continuar
                }
            }

            // Se não for maçã nem parte da cobrinha, imprime espaço vazio
            if (!printed) printf(" ");
        }

        printf("|\n");  // Borda direita da linha atual + quebra de linha
    }

    // ───── Borda inferior ─────
    printf("+");
    for (int x = 0; x < WIDTH; x++)
        printf("-");
    printf("+\n");

    // ───── Pontuação ─────
    printf("Score: %d\n", score);  // Mostra o placar do jogador
}

//função para gera uma nova maçã
void generate_apple(){
    //cria nova posição com base na posição da cabeça
    apple.x = (snake[0].x + 5) % WIDTH; // garante que a maçã esteja dentro do mapa
    apple.y = (snake[0].y + 3) % HEIGHT;
}

// Atualiza a posição da cobrinha, verifica colisões e trata o crescimento e pontuação
void move_snake() {
    // Move cada segmento do corpo da cobrinha para a posição do anterior
    // Começamos do final da cobra para o início (de trás pra frente)
    for (int i = snake_len - 1; i > 0; i--)
        snake[i] = snake[i - 1];

    // Move a cabeça da cobrinha conforme a direção atual
    if (direction == UP)    snake[0].y--;
    if (direction == DOWN)  snake[0].y++;
    if (direction == LEFT)  snake[0].x--;
    if (direction == RIGHT) snake[0].x++;

    // Verifica se a cabeça saiu dos limites e aplica teletransporte nas bordas
    // Ex: se sair pelo lado esquerdo, aparece do lado direito
    if (snake[0].x < 0)          snake[0].x = WIDTH - 1;
    else if (snake[0].x >= WIDTH)  snake[0].x = 0;

    if (snake[0].y < 0)          snake[0].y = HEIGHT - 1;
    else if (snake[0].y >= HEIGHT) snake[0].y = 0;

    // Verifica se a cabeça colidiu com o próprio corpo
    for (int i = 1; i < snake_len; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            game_over = 1; // Ativa o fim de jogo
            return;        // Encerra a função
        }
    }

    // Verifica se a cabeça da cobrinha encontrou a maçã
    if (snake[0].x == apple.x && snake[0].y == apple.y) {
        // Aumenta o tamanho da cobrinha, se ainda não atingiu o limite
        if (snake_len < MAX_LEN) 
            snake_len++;

        // Aumenta a pontuação
        score += 10;

        // Gera uma nova maçã em posição diferente
        generate_apple();
    }
}

// Lê comandos do usuário via UART
void handle_input() {
    if (uart_haschar()) {
        char c = uart_getchar();

        if (c == 'w' && direction != DOWN)  direction = UP;
        if (c == 's' && direction != UP)    direction = DOWN;
        if (c == 'a' && direction != RIGHT) direction = LEFT;
        if (c == 'd' && direction != LEFT)  direction = RIGHT;
    }
}

// Delay simples (simula tempo entre os frames)
void sleep_fake() {
    for (volatile int i = 0; i < sleep_time; i++);
}

// Função principal do jogo
void run_snake_game() {


    // Inicializa a cobrinha no meio da tela
    for (int i = 0; i < snake_len; i++) {
        snake[i].x = 5 - i;
        snake[i].y = 5;
    }

    generate_apple();       // Cria a primeira maçã
    printf("\033[2J\033[H");

    // Loop principal do jogo
    while (!game_over) {
        handle_input();     // Lê teclas
        move_snake();       // Atualiza posição da cobrinha
        draw_screen();      // Desenha tudo na tela
        sleep_fake();       // Espera um tempo
    }

       // Fim de jogo
        printf("\033[2J\033[H");
        printf("GAME OVER!\n");
        printf("Pontuação final: %d\n", score);
        printf("\nPressione 'R' para jogar novamente ou 'Q' para sair.\n");
    
   
        while (1) {
           if (uart_haschar()) {
               char c = uart_getchar();
   
               if (c == 'R' || c == 'r') {
                   // Reinicia variáveis
                   snake_len = 4;
                   direction = RIGHT;
                   score = 0;
                   game_over = 0;
                   run_snake_game();  // Reinicia o jogo                    
                } else if (c == 'Q' || c == 'q') {
                   printf("Saindo...\n");
                   for (;;); // trava sistema
                } else {
                    printf("Opção inválida. Pressione 'R' ou 'Q'.\n");
                }
           }
        }
   

    for (;;); // trava sistema após o fim
}
