.global _start


_start: 
    # Desabilitar todas as cpus, excepto a primeira 
    csrr t0, mhartid # t0 <- mhartid
    bnez t0, park   # if t0 != 0, jump to park
    # a cpu com id 0 é a unica que chega aqui
    la sp, stack_end # sp <- stack_end (sp armazena a base da pilha)
    j entry # jump para a função entry
    
park:
    # Desabilitar todas as cpus, excepto a primeira
    wfi # "dessabilita" a cpu
    j park
