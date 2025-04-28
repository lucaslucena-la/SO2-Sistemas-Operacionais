#include "defs.h"
#include "proc.h"

void trap(uint64 cause, TrapFrame *tf){
    if((long) cause > 0){
        //exceção 
        switch (cause) {
        case 2:
            printf("<trap.c> [CPU#:%d] [mepc#:%p] - Intrução ilegal\n", tf -> hartid );
            tf -> epc = tf-> epc + 4;
            break;
        case 9:
            printf("<trap.c> [mepc:%p] - chamada de sistema\n", tf -> epc);
            //identifica a chamada de sistema
            if(tf -> a7 == 1){
                printf("Olá, disse o kernel\n");
                tf -> epc = tf-> epc + 4;
            }else if(tf -> a7 == 2){
                //chamada de sistema write 
                char *s = (char *) tf -> a0;
                for(int i = tf -> a1; i> 0; i--){
                    uartputc(*s);
                    s++;
                    
                }
                tf -> epc = tf-> epc + 4;
                
            }
            break;
            //executa a chamada
            //...
        default:
            panic("Exceção não tratada");
            break;
        }
    } else {
        printf(" -- Interrupção --\n");
    }
}