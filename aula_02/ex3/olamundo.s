.section .data
msg:
.ascii "Olá, mundo!"

.global _start
.section .text
 _start:
# 1. carregar os argumentos para a chamada de sistema write

    li a0, 1 # descritor de arquivo para saída padrão (terminal) a0 = 1
    la a1, msg # a1 = recebe endereço inicial da string
    li a2, 12 # tamanho da string a ser impressa 

# a7 = 64 (write)
li a7, 64
# 2. chamar a syscall write 
ecall # transfere a execução p/ o kernel 


# Queremos sair do programa. Invocar  syscall exit
li a0, 0 #return 0 
li a7, 94 # call exit 
 
 ecall # give the cpu back





