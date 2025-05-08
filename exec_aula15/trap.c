#include "defs.h"
#include "proc.h"
#include "memlayout.h"

void trap(uint64 cause, TrapFrame *tf){
    if((long) cause > 0){
        //exceção 
        switch (cause) {
        case 2:
            printf("<trap.c> [CPU#:%d] [mepc#:%p] - Intrução ilegal\n", tf -> hartid );
            tf -> epc = tf-> epc + 4;
            break;
        case 9:
            printf("<trap.c> chamada de sistema\n");
            printf("Syscall recebida - a7 = %d\n", tf->a7);
        
            if(tf -> a7 == 1){
                printf("Olá, disse o kernel\n");
                tf -> epc = tf-> epc + 4;
            }
            else if(tf -> a7 == 2){
                char *s = (char *) tf -> a0;
                for(int i = tf -> a1; i> 0; i--){
                    uartputc(*s);
                    s++;
                }
                tf -> epc = tf-> epc + 4;
            }
            else if(tf->a7 == 3) { // chamada sleep 
                uint64 seg = tf->a0;

                uint64 atual = (volatile uint64)CLINT_MTIME;
                uint64 target_time = atual + (seg * 10000000);  // 10MGZ

                // compara registradores para ver se ja deu o tempo
                *(volatile uint64 *)CLINT_MTIMECMP(0) = target_time;

                while ((volatile uint64)CLINT_MTIME < target_time); // loop busy waiting

                uint64 duracao = ((volatile uint64)CLINT_MTIME - atual) / 10000000;

                tf->a0 = duracao;  // duracao
                tf->epc +=4;

            }
        
        default:
            panic("Exceção não tratada");
            break;
        }
    } else {
        //interrupção assícrona
        uint64 icause = cause & 0x3ff; // 
        switch (icause) {
            case 7://interrupção de temporizador
            //emoji do relogio: \U0001F550
            //TODO: o kernel deve ser interrompido a cada 3 segunds. para cada interrupção imprimir uma mensagen na tela informando o ocorrido
            *(uint64 *)CLINT_MTIMECMP(tf->hartid) = *(uint64 *)CLINT_MTIME + 3 * 10000000;
                        
            //printf("\U0001F550 -- Interrupção do temporizador --\n");
            break;
        default:
            printf(" -- Ocorreu uma interrupção qualquer --\n");
            break;
        
        
        }
    }
}