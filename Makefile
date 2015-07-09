# ############################################################################ #
#    This file is part of Forward OS.                                          #
#                                                                              #
#    Batch Interpret is free software: you can redistribute it and/or modify   #
#    it under the terms of the GNU General Public License as published by      #
#    the Free Software Foundation, either version 3 of the License, or         #
#    (at your option) any later version.                                       #
#                                                                              #
#    Batch Interpret is distributed in the hope that it will be useful,        #
#    but WITHOUT ANY WARRANTY; without even the implied warranty of            #
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             #
#    GNU General Public License for more details.                              #
#                                                                              #
#    You should have received a copy of the GNU General Public License         #
#    along with Batch Interpret. If not, see <http://www.gnu.org/licenses/>.   #
# ############################################################################ #

CC = gcc
CFLAGS = -m32 -c -w
ASM = nasm
ASMFLAGS = -f elf32
LINK = ld
LINKFLAGS = -m elf_i386 -T
MKDIR_P = mkdir -p
MV = mv
CP = cp
ISODIR = isodir
OUTDIR = bin

.PHONY: directories

all: directories kernel.bin forwardos.iso
	${MV} kernel.bin ${OUTDIR}

kernel.bin: start.o main.o system.o gdt.o idt.o isrs.o irq.o timer.o kb.o
	${LINK} ${LINKFLAGS} src/link.ld -o kernel.bin src/start.o src/main.o src/system.o src/gdt.o src/idt.o src/isrs.o src/irq.o src/timer.o src/kb.o
	${CP} kernel.bin ${OUTDIR}

start.o: src/start.asm
	${ASM} ${ASMFLAGS} -o src/start.o src/start.asm

main.o: src/main.c
	${CC} ${CFLAGS} src/main.c -o src/main.o

system.o: src/system.c
	${CC} ${CFLAGS} src/system.c -o src/system.o

gdt.o: src/gdt.c
	${CC} ${CFLAGS} src/gdt.c -o src/gdt.o

idt.o: src/idt.c
	${CC} ${CFLAGS} src/idt.c -o src/idt.o

isrs.o: src/isrs.c
	${CC} ${CFLAGS} src/isrs.c -o src/isrs.o

irq.o: src/irq.o
	${CC} ${CFLAGS} src/irq.c -o src/irq.o

timer.o: src/timer.c
	${CC} ${CFLAGS} src/timer.c -o src/timer.o

kb.o: src/kb.c
	${CC} ${CFLAGS} src/kb.c -o src/kb.o

forwardos.iso: kernel.bin
	${MKDIR_P} ${ISODIR}
	${MKDIR_P} ${ISODIR}/boot
	${CP} ${OUTDIR}/kernel.bin ${ISODIR}/boot/kernel.bin
	${MKDIR_P} ${ISODIR}/boot/grub
	${CP} grub.cfg ${ISODIR}/boot/grub/grub.cfg
	grub-mkrescue -o forwardos.iso ${ISODIR}

directories: ${OUTDIR}

${OUTDIR}:
	${MKDIR_P} ${OUTDIR}

clean:
	rm *.iso src/*.o
	rm -rf bin isodir
