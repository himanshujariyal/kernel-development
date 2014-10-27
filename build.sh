nasm -f elf -o binaries/start.o start.asm

gcc -m32 -I./include -c -o binaries/main.o main.c

gcc -m32 -I./include -c -o binaries/screen.o screen.c

gcc -m32 -I./include -c -o binaries/gdt.o gdt.c

gcc -m32 -I./include -c -o binaries/idt.o idt.c

gcc -m32 -I./include -c -o binaries/irq.o irq.c

gcc -m32 -I./include -c -o binaries/keyboard.o keyboard.c

cd binaries/ 

ld -m elf_i386 -T link.ld -o kernel start.o main.o screen.o gdt.o idt.o irq.o keyboard.o

rm *.o


