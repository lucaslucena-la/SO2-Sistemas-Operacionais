//copiar o caracter para a posição de memória do UART (0x1000000)

#define UART_REG 0x10000000
void putc(char c){
    volatile char *reg = (char*)  UART_REG;
    *reg = c;
}


void puts(char *s){
    while(*s){
        putc(*s++);
    }
}

// inicio do programa
void entry(){
    puts("- Olá mundo, disse o kernel");

}