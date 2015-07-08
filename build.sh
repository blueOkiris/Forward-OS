#!/bin/bash
if test "`whoami`" != "root" ; then
	echo "You must be logged in as root to build (for loopback mounting)"
	echo "Enter 'su' or 'sudo bash' to switch to root"
	exit
fi

echo ">>> Assembling kernel..."
echo ">>> gcc main.c..."
gcc -m32 -c -w  src/main.c -o src/main.o
echo ">>> gcc system.c..."
gcc -m32 -c -w  src/system.c -o src/system.o
echo ">>> gcc gdt.c..."
gcc -m32 -c -w  src/gdt.c -o src/gdt.o
echo ">>> gcc idt.c..."
gcc -m32 -c -w  src/idt.c -o src/idt.o
echo ">>> gcc isrs.c..."
gcc -m32 -c -w  src/isrs.c -o src/isrs.o
echo ">>> gcc irq.c..."
gcc -m32 -c -w  src/irq.c -o src/irq.o
echo ">>> gcc timer.c..."
gcc -m32 -c -w  src/timer.c -o src/timer.o
echo ">>> gcc kb.c..."
gcc -m32 -c -w  src/kb.c -o src/kb.o
echo ">>> nasm start.asm..."
nasm -f elf32 -o src/start.o src/start.asm
echo ">>> linking..."
ld -m elf_i386 -T src/link.ld -o kernel.bin src/start.o src/main.o src/system.o src/gdt.o src/idt.o src/isrs.o src/irq.o src/timer.o src/kb.o
echo ">>> moving kernel to bin..."
mv kernel.bin bin/
echo ">>> cleaning up object files..."
rm -r src/*.o
echo ">>> done. "
echo ">>> Press enter to continue..."
read

echo ">>> Creating iso..."
mkdir -p isodir
mkdir -p isodir/boot
cp bin/kernel.bin isodir/boot/kernel.bin
mkdir -p isodir/boot/grub
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o forwardos.iso isodir
echo ">>> Press enter to continue..."
read

echo ">>> Running system..."
qemu-system-i386 -cdrom forwardos.iso
