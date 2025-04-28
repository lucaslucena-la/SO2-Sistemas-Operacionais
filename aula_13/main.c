#include "types.h"
#include "defs.h"
#include "console.h"
#include "riscv.h"

extern void mvector(); // Rotina definida em assembly (trap_handler.s)

void puts(char *s) {
    while (*s) {
        uartputc(*s);
        s++;
    }
}

void main() {
    int c; // caractere
    uart_init(); // Configura o dispositivo de comunicação serial UART
    puts(CLS 
        TOP_LEFT 
        "\u26f0" 
        PURPLE 
        BOLD 
        " ROS - Roncador Operating System \U0001F525 \n"
        RESET_COLOR);
    printf("Kernel start: %x\n", 0x80000000UL);
    printf("Endereço do vetor de interrupção: %p\n", mvector);
    int per = perimetro(3, 10, 20, 30); //triângulo
    per = perimetro(4, 10, 20, 30, 40); //quadrado
    
    //puts("Permímetro do quadrado: ");
    //printlng(per, 10);
    
    printf("Perímetro do quadrado: %d. Um número negativo: %d\n", per, -123);
    
    char *ptr = "Hello, World!";

    printf("Saudação: %s. Seu endereço: (na memória): %p\n", ptr, ptr);
    printf("Ola,%");
    printf("\nO símbolo de porcentagem é %%.\n");
    
    for(;;){ //while(1)
        //1. Obter caractere do teclado
        c = uartgetc();
        if(c == -1) {
            continue;
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
}

void entry() {
// Queremos executar a função main no modo S
    memory_init(); // Inicializa a lista de descritores do heap
    w_mtvec((uint64) mvector); // Configura o vetor de interrupção
    
    w_mepc((uint64) main); // Configura o endereço de retorno
    uint64 x = r_mstatus();
    x = x & ~MSTATUS_MPP_MASK; // Limpa os bits MPP
    // Configura o modo de privilégio p/ Supervisor
    x = x | MSTATUS_MPP_S;
    w_mstatus(x); 
    //Retorna para a main
    asm volatile ("mret");  
    // main();
}