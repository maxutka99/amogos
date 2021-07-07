

all:
	gcc -c kernel/kernel.c -o output/kernel.o -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	nasm -felf32 boot/boot.asm -o output/boot.o
	gcc -m32 -T linker.ld -o output/myos.bin -ffreestanding -O2 -nostdlib output/boot.o output/kernel.o -lgcc
	qemu-system-x86_64 -kernel output/myos.bin

build:
	gcc -c kernel/kernel.c -o output/kernel.o -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	nasm -felf32 boot/boot.asm -o output/boot.o
	gcc -m32 -T linker.ld -o output/myos.bin -ffreestanding -O2 -nostdlib output/boot.o output/kernel.o -lgcc

run:
	qemu-system-x86_64 -kernel output/myos.bin