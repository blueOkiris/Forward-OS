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