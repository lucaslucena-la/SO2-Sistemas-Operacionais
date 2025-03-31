
// declaração de funções para ser usadas em outros arquivos
void uartputc(int c);
int uartgetc();
void uart_init();
int perimetro(int , ...);
void printf(char *, ...);
void memory_init();
void print_memory_statistics();
void *kalloc();
void* kalloc2();
void kfree(void *ptr);
void kstrcpy(char *s, void *ptr);

