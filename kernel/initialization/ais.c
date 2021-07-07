#include <stddef.h>
#include "../drivers/tty.c"
#include "../lib/memory.h"
static uint32_t idt_location = 0;
extern uint32_t kernel_end = 0;
extern uint32_t kernel_base = 0;
/* Required Declarations */
void idt_register_interrupt(uint8_t i, uint32_t callback)
{
	
	*(uint16_t*)(idt_location + 8*i + 0) = (uint16_t)(callback & 0x0000ffff);
	*(uint16_t*)(idt_location + 8*i + 2) = (uint16_t)0x8;
	*(uint8_t*) (idt_location + 8*i + 4) = 0x00;
	*(uint8_t*) (idt_location + 8*i + 5) = 0x8e;//0 | IDT_32BIT_INTERRUPT_GATE | IDT_PRESENT;
	*(uint16_t*)(idt_location + 8*i + 6) = (uint16_t)((callback & 0xffff0000) >> 16);
	
	return;
}

void ExceptionHandler(){
	terminal_writestring("\n\nkernel panic: exception occured; cannot handle\n\n");
    asm("hlt");
}
void startAIS(){
    terminal_writecolour("\n\n   AIS", 10);
    terminal_writecolour(" 0.1 ", 11);
    terminal_writecolour("is starting up AmogOS\n\n", 7);
    terminal_writecolour("\n * ", 10);
    terminal_writecolour("Memory init sequnce: ", 15);
    mm_init(&kernel_end);
    terminal_writestring(" finished"); 
    terminal_writecolour("\n * ", 10);
    terminal_writecolour("Terminal already initialized:", 15); 
    terminal_writestring(" skipping...\n");
    terminal_writecolour(" * ", 10);
    terminal_writecolour("Videobuffer: 0xB8000", 15); 
    terminal_writecolour("\n * ", 10);
    terminal_writecolour("Interrupt Handler Service initialization sequence: ", 15); 
    int i;
    for (i = 1; i < 15; ++i)
    {
        idt_register_interrupt(i, (uint32_t)ExceptionHandler);
    }
    terminal_writestring(" finished...");
    terminal_writecolour("\n * ", 10);
    terminal_writecolour("AmogOS (i386) 0.1 is ready for usage! ", 15); 
    terminal_writecolour("\n\nroot@amogos ", 10);
    terminal_writecolour("$ ", 9);
    terminal_writecolour("", 15);
}