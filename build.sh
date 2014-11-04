nasm -f elf -o binaries/head.o head.asm

gcc -m32 -I./include -c -o binaries/bingmain.o bingmain.c

gcc -m32 -I./include -c -o binaries/screen.o screen.c

gcc -m32 -I./include -c -o binaries/gdt.o gdt.c

gcc -m32 -I./include -c -o binaries/mm.o mm.c

gcc -m32 -I./include -c -o binaries/interrupts.o interrupts.c

gcc -m32 -I./include -c -o binaries/int_req.o int_req.c

gcc -m32 -I./include -c -o binaries/fs.o fs.c

gcc -m32 -I./include -c -o binaries/keyboard.o keyboard.c


cd binaries/ 

ld -m elf_i386 -T link.ld -o kernel head.o mm.o bingmain.o screen.o gdt.o interrupts.o int_req.o keyboard.o fs.o

rm *.o


