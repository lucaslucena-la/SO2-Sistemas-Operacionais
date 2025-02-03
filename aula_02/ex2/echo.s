.section .data
msg:
#.ascii "Olá, mundo!"
String: .space  10

.global _start
.section .text
 _start:

# Ler do teclado 

# 1. Escolher a syscall que lê string

    li a7, 63 # Read
    li a0, 0 # stdin 
    la a1, String # endereço do buffer
    li a2, 10 # máximo de caracteres para ler 

# 2. Chama o kernel     

ecall 

 # para a quantidade de bytes a serem lidos para o registrador a2
 mv a2, a0




# 1. Carregar os argumentos para a chamada de sistema write

    li a0, 1 # descritor de arquivo para saída padrão (terminal) a0 = 1
    la a1, String # a1 = recebe endereço inicial da string
   # li a2, a0  # tamanho da string a ser impressa 

# 2. Escolher a syscall
    li a7, 64

# 3. Chamar a syscall write 
    ecall # transfere a execução p/ o kernel 

# 4. Queremos sair do programa. Invocara  syscall exit
li a0, 0  # return 0 
li a7, 94 # call exit 
 
 ecall # give the cpu back





