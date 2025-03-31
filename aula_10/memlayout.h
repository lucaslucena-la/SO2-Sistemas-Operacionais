//neste arquivo irá conter vários endereços de memória que são utilizados pelo kernel do xv6 para alocar memória para os processos e para o kernel.

#define UART 0x10000000L 
#define KERNEL_START 0x80000000L
#define MEMORY_LENGTH 128*1024*1024 //128MB
#define PAGE_SIZE 4096 //4KB
