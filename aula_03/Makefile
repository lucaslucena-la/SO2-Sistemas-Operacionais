PRE = riscv64-linux-gnu-
CC = $(PRE)gcc # Compilador
LD = $(PRE)ld # Linker

CFLAGS = -ffreestanding # compilação sem suporte do sistema operacional
CFLAGS += -march=rv64g -mabi=lp64 # arquitetura RISC-V 64 bits
CFLAGS += -Wall # Queremos todos os warnings!
CFLAGS += -c -g -O0 # compilação sem otimização e com debug (g)

LDFLAGS = -nostdlib  # não usar bibliotecas padrão
LDFLAGS += -Ttext=0x80000000 # endereço de início do programa


kernel: boot.o main.o
	$(LD) $(LDFLAGS) -o kernel boot.o main.o
	
boot.o: boot.s
	$(CC) $(CFLAGS) boot.s

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm -f *.o kernel