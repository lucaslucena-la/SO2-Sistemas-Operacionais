.section .text

.balign 4
mvector:
    # rotina para salvar o contexto
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
    mv t5, t6 # t5 = t6
    csrrw t6, mscratch, t6
    sd t6, 240(t6)

    # salvar na estrutura do trapframe o mhartid
    csrr t0, mhartid
    sd t0, 256(t5)

    # salvar o conteúdo de mepc no trap frame
    csrr t1, mepc
    sd t1, 264(t5)
