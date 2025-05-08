// uart.h
#ifndef UART_H
#define UART_H

void uart_init(void);      // Inicializa a UART
void uartputc(int c);      // Envia caractere
int uartgetc(void);        // Lê caractere (ou retorna -1 se não houver)

int uart_haschar(void);


// Função auxiliar: lê caractere disponível (bloqueante)
static inline char uart_getchar() {
    int c;
    do {
        c = uartgetc();
    } while (c == -1); // Espera até receber algo
    return (char)c;
}

#endif
