// inicio do programa
#include "types.h"
#include "defs.h"

void puts(char *s){
    while(*s){
        uartputc(*s++);
        
    }
}

void entry(){
    int c;// caracter lido
    puts(" \u26f0 LOS - Lucena Operating System\n");

    //1. obter o caracter do teclado
    //2. se o caracter for diferente de -1, enviar o caracter para o terminal
    //3. faz outra coisa qualquer

    while(1){
        c = uartgetc();
        if(c != -1){
            uartputc(c);
        }
    }
}


