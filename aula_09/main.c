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
    
    memory_init();

    print_memory_statistics();

    int per = perimetro(10,20,30,40);
    per = perimetro(10,20,70,40,90);
    printf("Perimetro do quadradro: %d\n", per);

    printf("Um numero negativo: %d\n", -12343);
    char *ptr = "Hello Word";
    printf("Ponteiro: %p\n", ptr);

    printf("Saudação: %s. seu endereço: (na memória): %p\n", ptr, ptr);
    
    printf("Ola, %\n");

    printf("O simbolodo de porcentagem é: %%");



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


