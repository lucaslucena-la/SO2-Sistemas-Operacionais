// inicio do programa
#include "types.h"
#include "defs.h"
#include "console.h"

void puts(char *s){
    while(*s){
        uartputc(*s++);
        
    }
}

void entry(){
    int c;// caracter lido
    uart_init();
    puts(CLS TOP_LEFT ORANGE BOLD BACKGROUND_COLOR "UFMT-""\u26f0 LOS - Lucena Operating System\n" RESET_COLOR);

    int per = perimetro(10,20,30,40);
    per = perimetro(10,20,70,40,90);
    
    //1. obter o caracter do teclado
    while(1){
        c = uartgetc();
        if(c == -1){
            continue;
        }
        //2. se o caracter for diferente de -1, enviar o caracter para o terminal

        switch (c){
            case '\r': //enter
                uartputc('\r');//retorno de carro
                uartputc('\n');//nova linha
                break;

            case 0x7f://del
                uartputc('\b');//basckspace
                uartputc(' ');
                uartputc('\b');//basckspace
                break;
            case 'a':
                puts("\x1B[3B");
                break;
            default:
                uartputc(c);
                break;
        
        }

        //3. faz outra coisa qualquer
    
    
    
    }

    
    
    
}


