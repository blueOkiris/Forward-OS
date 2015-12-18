/* *************************************************************************** */
/*    This file is part of Forward OS.                                         */
/*                                                                             */
/*    Forward OS is free software: you can redistribute it and/or modify       */
/*    it under the terms of the GNU General Public License as published by     */
/*    the Free Software Foundation, either version 3 of the License, or        */
/*    (at your option) any later version.                                      */
/*                                                                             */
/*    Batch Interpret is distributed in the hope that it will be useful,       */
/*    but WITHOUT ANY WARRANTY; without even the implied warranty of           */
/*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            */
/*    GNU General Public License for more details.                             */
/*                                                                             */
/*    You should have received a copy of the GNU General Public License        */
/*    along with Batch Interpret. If not, see <http://www.gnu.org/licenses/>.  */
/* *************************************************************************** */


// Just used for defining all functions so everything can be used
#ifndef __SYSTEM.H
#define __SYSTEM.H

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 0x08

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHT_GRAY 7
#define DARK_GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define LIGHT_RED 12
#define LIGHT_MAGENTA 13
#define LIGHT_BROWN 14
#define WHITE 15

#define MAX_VIDPTR 80*25

struct regs
{
    unsigned int gs, fs, es, ds;
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	unsigned int int_no, err_code;
	unsigned int eip, cs, eflags, useresp, ss;
};

extern void *memcpy(void *dest, const void *src, int count);
extern void *memset(void *dest, char val, int count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
extern int letti(char let);
extern int atoi(char *str);
extern void putnum(int num);
extern int write_port(int a, int b);
extern int read_port(int a);

extern char getch(int ind);
extern void scroll(char c);
extern char get_attr(int ind);
extern int halt();
extern int str_startswith(char *one, char *two);
extern int str_len(char *str);

extern void putch(char c);
extern void puts(char *str);
extern void putsln(char *str);
extern void putss(char *str, int beg, int end);
extern void putslns(char *str, int beg, int end);
extern void clear_screen();
extern void text_color(unsigned char forecolor, unsigned char backcolor);//done

extern void run_command();
extern void set_up_terminal();
extern void move_cursor(int a, int b);
extern void is_cmd_on();
extern void is_cmd_off();
extern void clear_command();

extern void gdt_install();
extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);

extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
extern void idt_install();

extern void isrs_install();

extern void timer_install();
extern void timer_wait(int ticks);

extern void keyboard_install();

extern void irq_install_handler(int irq, void (*handler)(struct regs *r));
extern void irq_uninstall_handler(int irq);
extern void irq_install();

#endif
