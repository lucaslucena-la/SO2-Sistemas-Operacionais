// uart.h
#ifndef UART_H
#define UART_H

void uart_init(void);      // Inicializa a UART
void uartputc(int c);      // Envia caractere
int uartgetc(void);        // Lê caractere (ou retorna -1 se não houver)
int uart_haschar(void);
char uart_getchar();




#endif
