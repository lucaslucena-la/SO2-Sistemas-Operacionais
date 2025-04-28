.section .text
.global mvector

.balign 4
mvector:
    # Rotina para salvar o contexto
    # mscratch é o endereço do trap frame
    csrrw t6, mscratch, t6 # t6 = mscratch, mscratch = t6

    sd ra, 0(t6)
    sd sp, 8(t6)
    sd gp, 16(t6)
    sd tp, 24(t6)
    sd t0, 32(t6)
    sd t1, 40(t6)
    sd t2, 48(t6)
    sd s0, 56(t6)
    sd s1, 64(t6)
    sd a0, 72(t6)
    sd a1, 80(t6)
    sd a2, 88(t6)
    sd a3, 96(t6)
    sd a4, 104(t6)
    sd a5, 112(t6)
    sd a6, 120(t6)
    sd a7, 128(t6)
    sd s2, 136(t6)
    sd s3, 144(t6)
    sd s4, 152(t6)
    sd s5, 160(t6)
    sd s6, 168(t6)
    sd s7, 176(t6)
    sd s8, 184(t6)
    sd s9, 192(t6)
    sd s10, 200(t6)
    sd s11, 208(t6)
    sd t3, 216(t6)
    sd t4, 224(t6)
    sd t5, 232(t6)
    mv t5, t6
    csrrw t6, mscratch, t6 
    sd t6, 240(t5) # Salvar t6

    # salvar na estrutura do trap frame o mhartid
    csrr t0, mhartid # t0 = mhartid
    sd t0, 256(t5) # 256: salta o campo trap stack do trapframe
    # Salvar o conteúdo de mepc no trap frame
    csrr t0, mepc # t0 = mepc
    sd t0, 264(t5) 

    # Saltar para função de tratamento de exceção (trap)
    csrr a0, mcause  # 1º argumento de trap: a causa da exceção
    mv a1, t5        # 2º argumento de trap: endereço do trap frame
    ld sp, 248(t5)   # Nova pilha para atender a exceção/interrupção
    call trap  # Chama a função trap (definida em C)

    # trap retornou, então restaurar o contexto
    
    csrr t6, mscratch # t6 = mscratch

    ld t5, 264(t6) #conteúdo de mepc
    csrw mepc, t5 # mepc <- novo endereço de retorno 

    ld ra, 0(t6)
    ld sp, 8(t6)
    ld gp, 16(t6)
    ld tp, 24(t6)
    ld t0, 32(t6)
    ld t1, 40(t6)
    ld t2, 48(t6)
    ld s0, 56(t6)
    ld s1, 64(t6)
    ld a0, 72(t6)
    ld a1, 80(t6)
    ld a2, 88(t6)
    ld a3, 96(t6)
    ld a4, 104(t6)
    ld a5, 112(t6)
    ld a6, 120(t6)
    ld a7, 128(t6)
    ld s2, 136(t6)
    ld s3, 144(t6)
    ld s4, 152(t6)
    ld s5, 160(t6)
    ld s6, 168(t6)
    ld s7, 176(t6)
    ld s8, 184(t6)
    ld s9, 192(t6)
    ld s10, 200(t6)
    ld s11, 208(t6)
    ld t3, 216(t6)
    ld t4, 224(t6)
    ld t5, 232(t6)
    ld t6, 240(t6) # Recupera t6

    mret 
