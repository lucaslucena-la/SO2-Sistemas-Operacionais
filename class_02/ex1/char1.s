.global first_char

first_char:
    lb a0, 0(a0) # read first byte of the address in the a0 register
    # 0 + adress passed (a0)
    ret 
    