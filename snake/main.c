#include "types.h"
#include "defs.h"
#include "console.h"
#include "riscv.h"
#include "memlayout.h"
#include "snake.h"
#include "uart.h"

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

    puts("\nMenu:\n");
    puts("  [J] Iniciar jogo da cobrinha\n");
    puts("  [Q] Sair (travará o sistema)\n");

    while (1) {
        if (uart_haschar()) {
            c = uart_getchar();

            if (c == 'J' || c == 'j') {
                run_snake_game();
            } else if (c == 'Q' || c == 'q') {
                printf("Saindo...\n");
                for (;;);  // trava sistema
            } else {
                printf("Opção inválida. Pressione 'J' para jogar ou 'Q' para sair.\n");
            }
        }
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