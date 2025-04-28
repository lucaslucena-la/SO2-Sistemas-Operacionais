PRE = riscv64-linux-gnu-
CC = $(PRE)gcc # Compilador
LD = $(PRE)ld # Linker
QEMU = qemu-system-riscv64 # Emulador

CFLAGS = -ffreestanding # compilação sem suporte do sistema operacional
CFLAGS += -march=rv64g -mabi=lp64 # arquitetura RISC-V 64 bits
CFLAGS += -Wall # Queremos todos os warnings!
CFLAGS += -c -g -O0 # compilação sem otimização e com debug (g)

LDFLAGS = -nostdlib  # não usar bibliotecas padrão
# LDFLAGS += -Ttext=0x80000000 # endereço de início do programa
LDFLAGS += -Tkernel.ld # Script para o linker

OBJ = boot.o \
	  main.o \
	  uart.o \
	  perimetro.o \
	  printf.o \
	  memory.o \
	  trap_handler.o \
	  trap.o \
	  syscall.o

kernel: $(OBJ)
	$(LD) $(LDFLAGS) -o kernel $(OBJ)
	
%.o: %.c
	$(CC) $(CFLAGS) $<

%.o: %.s
	$(CC) $(CFLAGS) $<

clean:
	rm -f *.o kernel

run:
	$(QEMU) -append 'console=ttyS0'  -nographic -serial mon:stdio -smp 4 -machine virt -bios none -kernel kernel
