.global _start

# mhartid é o reg. que contém o ID da CPU
_start:
csrr t0, mhartid  # Copia o ID da CPU para t0
bnez t0, park # t0 é igual a zero? se sim, pula para park: if (t0 != 0) goto park

la sp, stack_end # carra o endereço de stack_end para sp
j entry # pula para a função entry em C

park:
   wfi
   j park

