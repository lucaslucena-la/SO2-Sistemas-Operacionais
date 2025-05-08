#include "types.h"
#include "defs.h"
#include <stdarg.h> // para funções com número variável de argumentos

static char *digits = "0123456789abcdef"; // dígito para ascii

void
printlng(long val, int base) {
    long l;
    char s[66];
    int i = 0;
    if (val < 0) 
        l = -val;
    else 
        l = val;
    if (l == 0)
        s[0] = '0';
    while(l != 0) {
        s[i++] = digits[l % base];
        l = l / base; // divisão inteira
    }
    if (val < 0)
        s[i++] = '-';
    if (base == 16) {
        s[i++] = 'x';
        s[i++] = '0';
    }
    if (base == 2) {
        s[i++] = 'b';
        s[i++] = '0';
    }
    while(i > 0) {
        uartputc(s[--i]);
    }
}

void 
printptr(void *ptr){
    printlng((long)ptr, 16);
}

void
printf(char *s, ...) {
    va_list ap; // argumentos variáveis
    int c; 
    char *str;

    va_start(ap, s); // inicializa a lista de argumentos variáveis
    for (; (c = *s) != 0; s++){
        if (c != '%') {
           uartputc(c);
           continue; 
        }
        c = *++s; // próximo caractere depois de %
        if (c == 0) {
            break; // string mal formada. Ex: printf("Hello, %")
        }
        switch(c) {
            case '%':
                uartputc('%');
                break;
            case 'd': //imprime inteiro
                printlng(va_arg(ap, int), 10);
                break;
            case 'x': // imprime inteiro na base 16
                printlng(va_arg(ap, int), 16);
                break;
            case 'l': // imprime long na base 10
                printlng(va_arg(ap, long), 10);
                break;
            case 's':
                str = va_arg(ap, char *);
                while(*str) {
                    uartputc(*str++);
                }
                break;
            case 'p': //imprime ponteiro
                printptr(va_arg(ap, void *));
                break;
            default:
                uartputc(c);
                break;
        }
    }   
}

void panic (char *s){
    printf("Panic: %s\n", s);
    while(1) {
        // loop infinito
    }
}


