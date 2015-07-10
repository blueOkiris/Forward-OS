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

#include "system.h"

char *vidptr = (char*)0xb8000;
int index = 0;
char attr = 0x07;
int term_ind = 10;
char command[80*25];
int cmd_ind = 0;
int is_cmd = 0;

int pt_s = 0;
int is_shift = 0;
int strt = 1;

int reg[26];

void clear_command() {
	int i = 0;
	while(i < 80*25) {
		command[i] = '\0';
		i++;
	}
	
	cmd_ind = 0;
}

void is_cmd_on() {
	is_cmd = 1;
}

void is_cmd_off() {
	is_cmd = 0;
}

void run_command() {
	is_cmd = 1;
	int size = str_len(command);
	if(str_startswith(command, "hlt") == 1) {
		text_color(BLACK, BLACK);
		clear_screen();
		halt();
	} else if(str_startswith(command, "println")) {
		putslns(command, 8, size);
	} else if(str_startswith(command, "printvln")) {
		if(letti(command[9]) != -1)
			putnumln(reg[letti(command[9])]);
	} else if(str_startswith(command, "printv")) {
		if(letti(command[7]) != -1)
			putnumln(reg[letti(command[7])]);
	} else if(str_startswith(command, "print")) {
		putss(command, 6, size);
	} else if (str_startswith(command, "clear")) {
		clear_screen();
		index = 0;
    } else if(str_startswith(command, "setv")) {
		if(letti(command[5]) != -1) {
			int r = letti(command[5]);
			
			int i = 0;
			while(i < 7) {
				command[i] = ' ';
				i++;
			}
			
			reg[r] = atoi(command);
		}
	} else if(str_startswith(command, "add")) {
		if(letti(command[4])!=-1 && letti(command[6])!=-1)
			reg[letti(command[4])] += reg[letti(command[6])];
	} else if(str_startswith(command, "sub")) {
		if(letti(command[4])!=-1 && letti(command[6])!=-1)
			reg[letti(command[4])] -= reg[letti(command[6])];
	} else if(str_startswith(command, "mul")) {
		if(letti(command[4])!=-1 && letti(command[6])!=-1)
			reg[letti(command[4])] *= reg[letti(command[6])];
	} else if(str_startswith(command, "div")) {
		if(letti(command[4])!=-1 && letti(command[6])!=-1)
			reg[letti(command[4])] /= reg[letti(command[6])];
	} else if(str_startswith(command, "mod")) {
		if(letti(command[4])!=-1 && letti(command[6])!=-1)
			reg[letti(command[4])] %= reg[letti(command[6])];
	} else if(str_startswith(command, "cc") == 1) {
		if(str_startswith(command, "cc help")) {
			putsln("Colors:");
			putsln(">>> BLACK       :: 0");
			putsln(">>> BLUE        :: 1");
			putsln(">>> GREEN       :: 2");
			putsln(">>> CYAN        :: 3");
			putsln(">>> RED         :: 4");
			putsln(">>> MAGENTA     :: 5");
			putsln(">>> BROWN       :: 6");
			putsln(">>> LT GRAY     :: 7");
			putsln(">>> DK GRAY     :: 8");
			putsln(">>> LT BLUE     :: 9");
			putsln(">>> LT GREEN    :: A");
			putsln(">>> LT CYAN     :: B");
			putsln(">>> LT RED      :: C");
			putsln(">>> LT MAGENTA  :: D");
			putsln(">>> LT BROWN    :: E");
			putsln(">>> WHITE       :: F");
		} else {
			char b = command[4];
			char f = command[3];
			if(f > '@' && b > '@')
				text_color(f - '0', b - 55);
			else if(f > '@')
				text_color(f - 55, b - '0');
			else if(b > '@')
				text_color(f - '0', b - 55);
			else
				text_color(f - '0', b - '0');
		}
	} else if(str_startswith(command, "help") == 1) {
		putsln("Commands:");
		putsln(">>> hlt          :: halts cpu");
		putsln(">>> cc fb|help   :: change text color - (fore, back)");
		putsln(">>> print text   :: print out a piece of text");
		putsln(">>> printv let   :: print out the value of variable let");
		putsln(">>> printvln let :: print out the value of variable let with a line after");
		putsln(">>> println text :: print out a piece of text with a line");
		putsln(">>> clear        :: Clears the screen");
		putsln(">>> setv let val :: set variable let to val");
		putsln(">>> add base set :: adds base to set and stores in base");
		putsln(">>> sub base set :: subtracts base from set and stores in base");
		putsln(">>> mul base set :: multiplies base by set and stores in base");
		putsln(">>> div base set :: divides base by set and stores in set");
		putsln(">>> mod base set :: divides base by set and stores remainder in set");
		putsln(">>> println text :: print out a piece of text with a line");
		putsln(">>> help         :: show help command");
	} else {
		puts(">>> Unknown command: ");
		putsln(command);
		putsln(">>> Try help.");
	}
	clear_command();
	
	is_cmd = 0;
}

int atoi(char *str) {
	int res = 0; // Initialize result
	int i = 0;
	while(str[i] != '\0') {
		if(str[i] - '0' < 10 && str[i] - '0' >= 0) {
			res = res*10 + str[i] - '0';
		}
		i++;
	}
	return res;
}

int letti(char let) {
	switch(let) {
		case 'a':
			return 0;
		break;
		case 'b':
			return 1;
		break;
		case 'c':
			return 2;
		break;
		case 'd':
			return 3;
		break;
		case 'e':
			return 4;
		break;
		case 'f':
			return 5;
		break;
		case 'g':
			return 6;
		break;
		case 'h':
			return 7;
		break;
		case 'i':
			return 8;
		break;
		case 'j':
			return 9;
		break;
		case 'k':
			return 10;
		break;
		case 'l':
			return 11;
		break;
		case 'm':
			return 12;
		break;
		case 'n':
			return 13;
		break;
		case 'o':
			return 14;
		break;
		case 'p':
			return 15;
		break;
		case 'q':
			return 16;
		break;
		case 'r':
			return 17;
		break;
		case 's':
			return 18;
		break;
		case 't':
			return 19;
		break;
		case 'u':
			return 20;
		break;
		case 'v':
			return 21;
		break;
		case 'w':
			return 22;
		break;
		case 'x':
			return 23;
		break;
		case 'y':
			return 24;
		break;
		case 'z':
			return 25;
		break;
	}
	
	return -1;
}

void putnum(int num) {
	int res = num;
	
    if (res==0) 
		putch('0');
    else {
        if (res<0) { 
			putch('-');
			res=-res; 
		}
		
        /*Largest num is `2,147,483,64(7|8)`*/
        char temp[10];
        int i = 0;
        do {
            temp[i++] = res%10 + '0';
            res /= 10;
        } while(res);
		
        while (--i>=0) {
            putch(temp[i]);
        }
    }
}

void putnumln(int num) {
	int res = num;
	
    if (res==0) 
		putch('0');
    else {
        if (res<0) { 
			putch('-');
			res=-res; 
		}
		
        /*Largest num is `2,147,483,64(7|8)`*/
        char temp[10];
        int i = 0;
        do {
            temp[i++] = res%10 + '0';
            res /= 10;
        } while(res);
		
        while (--i>=0) {
            putch(temp[i]);
        }
    }
	
	putsln("");
}

char get_attr(int ind) {
	return vidptr[ind*2+1];
}

int str_len(char *str) {
	int i = 0;
	while(str[i] != '\0') {
		i++;
	}
	return i;
}

void set_up_terminal() {
	char c = attr;
	text_color(RED, BLACK);
	puts("terminal:>");
	term_ind = index;
	clear_command();
	attr = c;
}

void putch(char c) {
	scroll(c);
	
	if(c == '\n') {
		is_shift = 0;
		int i = index/2;
		i += 80;
		while(i % 80 > 0) {
			i--;
		}
		
		index = i*2;
		move_cursor((index/2)%80, (index/2)/80);
		
		if(strt == 0)
			run_command();
		
		char r = attr;
		
		if(strt == 0) {
			text_color(RED, BLACK);
			is_cmd = 1;
			puts("terminal:>");
			is_cmd = 0;
			term_ind = index;
		} else {
			strt = 0;
		}
		
		attr = r;
	} if(c == '\r') {
		if(is_shift == 0)
			is_shift = 1;
		else if(is_shift == 1)
			is_shift = 0;
	} else {
		if(c == '\t') {
			putch(' ');
			putch(' ');
			putch(' ');
			putch(' ');
		} else if(c == '\b') {
			if(index > term_ind) {
				index -= 2;
				vidptr[index] = ' ';
				vidptr[index + 1] = attr;
				
				if(is_cmd == 0) {
					cmd_ind--;
					command[cmd_ind] = '\0';
				}
				
				move_cursor((index/2)%80, (index/2)/80);
			}
		} else if(c >= ' '){
			if(is_shift == 1 && strt == 0) {
				if(c > '`')
					c = c - 32;
				else
					c = c - 16;
			}
			vidptr[index] = c;
			vidptr[index+1] = attr;
			
			if(is_cmd == 0) {
				command[cmd_ind] = c;
				cmd_ind++;
			}
			
			index += 2;
			
			move_cursor((index/2)%80, (index/2)/80);
		}
	}
}

char getch(int ind) {
	return vidptr[ind];
}

void text_color(unsigned char forecolor, unsigned char backcolor) {
	attr = (backcolor << 4) | (forecolor & 0x0F);
}

int str_startswith(char *one, char *two) {
	int ol = str_len(one);
	int tl = str_len(two);
	
	if(tl > ol) {
		return 0;
	} else {
		int i = 0;
		while(i < tl) {
			if(one[i] != two[i])
				return 0;
			i++;
		}
		
		return 1;
	}
}

void clear_screen(void)
{
	int i = 0;
	while (i < 80*25*2) {
		vidptr[i] = ' ';
		i++;
		vidptr[i] = attr;
		i++;
	}
}

void puts(char *str) {
	pt_s = 1;
	int length = str_len(str);
	int i =0;
	while(i < length) {
		putch(str[i]);
		i++;
	}
	pt_s = 0;
}

void putsln(char *str) {
	pt_s = 1;
	int length = str_len(str);
	int i =0;
	while(i < length) {
		putch(str[i]);
		i++;
	}
	
	strt = 1;
	putch('\n');
	pt_s = 0;
}

void putss(char *str, int beg, int end) {
	pt_s = 1;
	int i = beg;
	while(i < end) {
		putch(str[i]);
		i++;
	}
	pt_s = 0;
}

void putslns(char *str, int beg, int end) {
	pt_s = 1;
	int i = beg;
	while(i < end) {
		putch(str[i]);
		i++;
	}
	
	strt = 1;
	putch('\n');
	pt_s = 0;
}

void move_cursor(int col, int row) {
	unsigned short position=(row*80) + col;
	
	// cursor LOW port to vga INDEX register
	write_port(0x3D4, 0x0F);
	write_port(0x3D5, (unsigned char)(position&0xFF));
	// cursor HIGH port to vga INDEX register
	write_port(0x3D4, 0x0E);
	write_port(0x3D5, (unsigned char )((position>>8)&0xFF));
 }

void scroll(char c)
{
    if(index >= 80*25*2) {
		index = 0;
		while(index < 80*24*2) {
			vidptr[index] = vidptr[index + 160];
			vidptr[index + 1] = vidptr[index + 161];
			index += 2;
		}
		
		index = 80*24*2;
		
		while(index < 80*25*2) {
			putch(' ');
		}
		
		index = 80*24*2;
		
		if(pt_s == 0)
			putch(c);
		
		move_cursor((index/2)%80, (index/2)/80);
	}
}

void *memcpy(void *dest, const void *src, int count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

void *memset(void *dest, char val, int count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}
