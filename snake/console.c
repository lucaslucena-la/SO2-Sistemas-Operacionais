#include "defs.h"
#include "riscv.h"

void console_handler(){
    int c; 

    //1. Obter caractere do teclado
    c = uartgetc();
    if(c == -1) {
        return;
    }
    switch(c) {
        case 'I':
            r_mstatus();
            printf("O tratador de exeções me deixou voltar");
            break;
        case 'S':
            ola();
            break;
        case 'W':
            write("UFMT", 2);
            break;
        case '\r': // Enter
            uartputc('\r'); //retorno de carro
            uartputc('\n'); //nova linha
            break;
        case 0x7f: // DEL
            uartputc('\b'); //backspace
            uartputc(' ');
            uartputc('\b');
            break;
        // case 'a':
        //     puts("\x1B[3B"); // ANSI para mover o cursor para baixo
        //     break;
        default:
            uartputc(c);
            break;
    }
    //3. Faz outra coisa qualquer
}