AS = riscv64-linux-gnu-as
LD = riscv64-linux-gnu-ld 
olamundo.x: olamundo.o
	$(LD) -o olamundo.x olamundo.o
run: olamundo.x
	./olamundo.x
olamundo.o: olamundo.s
	$(AS) -o olamundo.o olamundo.s

clean:
	rm -rf olamundo.o olamundo.x