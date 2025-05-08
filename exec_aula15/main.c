#include "types.h"
#include "defs.h"
#include "console.h"
#include "riscv.h"
#include "memlayout.h"

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
        //emoji do pato
        "\U0001F986"
        PURPLE 
        BOLD 
        " POS -  Patos Operating System \U0001F525 \n"
        RESET_COLOR);
    
    puts(ORANGE BOLD " UFMT - Universidade Federal de Mato Grosso \n" RESET_COLOR);
    puts(ORANGE BOLD " Curso de Ciência da Computação \n" RESET_COLOR);
    puts(ORANGE BOLD " Disciplina de Sistemas Operacionais \n" RESET_COLOR);
    printf("O tempo do sistema na main (MTIME): %d\n", *(uint64 *)CLINT_MTIME);// Mostra o tempo do sistema
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

            case 'D':
                printf("Vou chamar sleep(2)...\n");
                int t = sleep(2);
                printf("Voltei do sleep: %d segundos\n", t);
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
    //MSTATUS.MPIE = 1; 
    x =r_mstatus();
    x = x | MSTATUS_MPIE; // Habilita interrupções no modo-S
    w_mstatus(x); 

    //habilita interrupção do temporizador
    x = r_mie();
    x = x | (1L << 7); // Habilita interrupção do temporizador
    w_mie(x);  

    //configurar uma interrup~ção p=de temporidazodr daqui a 3 segundos
    uint64 mtimecmp = *(uint64 *)CLINT_MTIME + 3 * 10000000;// 3 segundos
    *(uint64 *)CLINT_MTIMECMP(0) = mtimecmp; // Configura o temporizador

    //Retorna para a main
    asm volatile ("mret");  
    // main();
}