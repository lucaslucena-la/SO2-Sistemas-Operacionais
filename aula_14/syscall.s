.global ola
.global write

ola:
    li a7, 1 # syscall ola
    ecall
    ret

# write(char *s, int n)
write:
    li a7, 2
    ecall
    ret
