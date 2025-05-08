// printf.h
#ifndef PRINTF_H
#define PRINTF_H

// Imprime uma string formatada no terminal (suporta %d, %x, %l, %s, %p, %%)
void printf(char *fmt, ...);

// Finaliza o sistema com uma mensagem de erro
void panic(char *s);

#endif
