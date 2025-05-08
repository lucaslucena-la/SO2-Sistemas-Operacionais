#include "types.h"

// declaração de funções e constantes para serem usadas em várias partes do código
void uartputc(int c);
int uartgetc();
void uart_init();
int perimetro(int lados, ...); //calcula o perímetro de um polígono regular
void printf(char *s, ...);
void memory_init();
void *kalloc(int pages);
void panic (char *s);


//chamadas de sistemas
void write(char *s, int n);
void ola();

//plic
uint32 plic_claim();
void plic_complete(uint32 irq);
void plic_init();

//console
void console_handler();