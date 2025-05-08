.global ola
.global write
.global sleep

# void ola()
ola:
    li a7, 1       # syscall ola
    ecall
    ret

# void write(char *s, int n)
write:
    li a7, 2       # syscall write
    ecall
    ret

sleep:
    li a7, 3      # número da syscall
    ecall
    ret


