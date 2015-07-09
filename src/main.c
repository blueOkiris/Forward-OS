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

const char *welcome_str = "Welcome to Forward OS!!\n";

int main() {
	gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    timer_install();
    keyboard_install();

    __asm__ __volatile__ ("sti");
	
	is_cmd_on();
	text_color(WHITE, BLACK);
	clear_screen();
	text_color(BLUE, WHITE);
	puts(welcome_str);
	timer_wait(18);
	set_up_terminal();
	text_color(LIGHT_GRAY, BLACK);
	is_cmd_off();
	
	while(1) ;
	
	return;
}
