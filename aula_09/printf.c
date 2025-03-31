#include "types.h"
#include "defs.h"
#include <stdarg.h>

static char *digits = "0123456789ABCDEF";

void printlng(long val, int base){
    
    long l;
    char s[66];
    int i = 0;

    if(val < 0){
        l = -val;
    }else{
        l = val;
    }

    if (l == 0){
        s[0] = '0';

    }else{
        while (l)
        {
            s[i++] = digits[l % base];
            l = l / base;

        }

        if(val < 0 ){
            s[i++] = '-';
        }

        if(base == 16){
            s[i++] = 'x';
            s[i++] = '0';

        }else if(base == 2){
            s[i++] = 'b';
            s[i++] = '0';
        }

        while (i>0) {
            uartputc(s[--i]);
        }
        
    }
}

void printptr(void  *ptr) {
    

    // Usa a função printlng para imprimir o endereço em hexadecimal (base 16)
    printlng((long)ptr, 16);

}

void printf(char *s, ...){
    va_list ap;//argumentos variaveis 
    char *str;
    int c;

    va_start(ap, s);//inicializa a lista de armuentos varáveis

    for(; (c = *s) != 0;s++){
        if(c != '%'){
            uartputc(c);
            continue;
        }
        c = *++s; //próximo caracter depois de %
        if(c == 0){
            break;
        }else{
            switch (c){
                case '%':
                    uartputc('%');
                    break;

                case 'd': 
                    printlng(va_arg(ap,int),10);
                    break;

                case 'x':
                    printlng(va_arg(ap, int),16); 
                    break;

                case 'l':
                    printlng(va_arg(ap, long),16); 
                    break;

                case 's': 
                    str = va_arg(ap, char*);
                    while (*str)
                    {
                        uartputc(*str++);
                    }
                    
                    break;

                case 'p': 
                    printptr(va_arg(ap, void*));
                    break;
                default:
                    uartputc(c);
                    break;
            }
        }
    }

}
