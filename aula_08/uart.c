//Driver para interação com o dispositivo UART 
//UART é um dispositivo de comunicação serial que é utilizado para comunicação entre dispositivos.         
#include "types.h"
#include "memlayout.h"  


//endereços de memória para o dispositivo UART
#define RHR  0 //para leitura de dados
#define THR  0 //para escrita de dados
#define IER  1 //para habilitar interrupções
#define FCR  2 //para controlar a FIFO
#define ISR  2 //para ler o status das interrupções
#define LCR  3 //para controlar a linha
#define LSR  5 //para ler o status da linha

void write_reg(uint64, char); 
char read_reg(uint64);

void uart_init(){
    //habilita a FIFO
    write_reg(FCR, 0x01);
    //habilita a interrupção
    write_reg(IER, 0x01);
    
}

// função para escrever no registrador do dispositivo UART
void write_reg(uint64 reg, char c){
    uint8 *base = (uint8 *) UART;
    *(base + reg) = c;

}

// função para ler o registrador do dispositivo UART
char read_reg(uint64 reg){
    uint8 *base = (uint8 *) UART;
    return *(base + reg);
}

//escrita de um caractere no terminal (via Uart)

void uartputc(int c){
    //verificar se o caracter anterior foi enviado
    while( (read_reg(LSR) & (1<<5)) == 0) //byte anterior não foi enviado
    ;
    write_reg(THR, c);

}

//obter caractere do teclado (via Uart)
int uartgetc(){
    int c;
    //vericar se há caracter disponivel

    c = read_reg(LSR);

    if((c & 0x01) == 0){//não há caracter disponivel
        return -1;
    }else{
        c = read_reg(RHR);
        return c;
    }

}