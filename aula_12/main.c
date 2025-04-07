// inicio do programa
#include "types.h"
#include "defs.h"
#include "console.h"
#include "riscv.h"

extern void mvector(); 

void puts(char *s){
    while(*s){
        uartputc(*s++);
        
    }
}

void main(){
    int c;// caracter lido
    uart_init();
    puts(CLS TOP_LEFT ORANGE BOLD BACKGROUND_COLOR "UFMT-""\u26f0 LOS - Lucena Operating System\n" RESET_COLOR);
    
    print_memory_statistics();

    // Teste da função kalloc2 (alocação de múltiplas páginas)
    printf("\n---------------------------------\n");
    printf("Testando kalloc2...\n");
    int num_pages = 3;
    void *ptr_kalloc2 = kalloc2(num_pages);
    if (ptr_kalloc2) {
        printf("Memória alocada com sucesso em %p para %d páginas\n", ptr_kalloc2, num_pages);
    } else {
        printf("Falha na alocação de %d páginas!\n", num_pages);
    }

    // Adicionando um printf para mostrar o status da alocação
    printf("Verificação pós-alocação: ponteiro %p\n", ptr_kalloc2);

    printf("\nAlocando mais uma página...\n");
    void *ptr_kalloc2_extra = kalloc2(1);
    if (ptr_kalloc2_extra) {
        printf("Memória alocada com sucesso em %p \n", ptr_kalloc2_extra);
    } else {
        printf("Falha na alocação\n");
    }

    // Adicionando um printf para mostrar o status da segunda alocação
    printf("Verificação pós-alocação: ponteiro %p\n", ptr_kalloc2_extra);

    // Teste da função kfree (liberação de memória) das memórias alocadas anteriormente
    printf("\nLiberando a memória alocada...\n");
    if (ptr_kalloc2) {
        kfree(ptr_kalloc2);
        printf("Memória liberada com sucesso em %p\n", ptr_kalloc2);
    } else {
        printf("Nenhuma memória foi alocada para liberar.\n");
    }

    // Liberando também a segunda alocação
    printf("\nLiberando a segunda memória alocada...\n");
    if (ptr_kalloc2_extra) {
        kfree(ptr_kalloc2_extra);
        printf("Memória liberada com sucesso em %p\n", ptr_kalloc2_extra);
    } else {
        printf("Nenhuma memória foi alocada para liberar.\n");
    }

    
    // Teste da função kstrcpy (cópia de string para memória alocada)
    printf("\n---------------------------------\n");
    printf("Testando kstrcpy...\n");
    char *source_str = "Hello, UFMT!";
    char *dest_str = (char *)kalloc();
    if (dest_str) {
        kstrcpy(source_str, dest_str);
        printf("String copiada: %s\n", dest_str);
        kfree(dest_str);
    } else {
        printf("Falha na alocação para cópia da string!\n");
    }

    printf("\n---------------------------------\n");


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

void entry(){
    memory_init();
    w_mtvec((uint64) mvector);

    printf("Endereço do vetor de interrupção: %p\n", mvector);
    w_mepc((uint64)main);

    uint64 x = r_mstatus();
    x = x & ~MSTATUS_MPP_MASK; // limpa os bits de mpp
    x = x | MSTATUS_MPP_M;
    w_mstatus(x);

    asm volatile ("mret");

    main();
}


