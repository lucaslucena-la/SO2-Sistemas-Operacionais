
// --------------------------------------------------------------------
// Declaração de funções e constantes para serem usadas em várias 
// partes do código do kernel e aplicações de usuário.
// --------------------------------------------------------------------

void uartputc(int c);               // Envia um caractere via UART
int uartgetc();                     // Lê um caractere da UART
void uart_init();                   // Inicializa a UART
int perimetro(int lados, ...);      // Calcula o perímetro de um polígono regular com lados fornecidos
void printf(char *s, ...);          // Imprime texto formatado no console (UART)
void memory_init();                 // Inicializa a gerência de memória
void *kalloc(int pages);            // Aloca memória no kernel
void panic (char *s);               // Exibe mensagem de erro e trava o sistema


// --------------------------------------------------------------------
// Chamadas de sistema disponíveis para o modo usuário.
// Essas funções são "wrappers" para syscalls tratadas pelo kernel.
// --------------------------------------------------------------------

void write(char *s, int n);         // Escreve uma string no console (UART)
void ola();                         // Função exemplo de syscall já implementada

int sleep(int);                 // Suspende a execução por 'sey' segundos (nova syscall)
