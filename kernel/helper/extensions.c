#include <string.h>
#include "../drivers/tty.h"
#include <cpuid.h>

 inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
    /* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * The  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

 inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}
int strcmp(const char *str1, const char *str2){
  int res = 1;
  int i = 0;
  if(strlen(str1) == strlen(str2)){
    while(str1[i] != 0x0A && str2[i] != 0x0A){
      if(str1[i] != str2[i]){
        res = 0;
      }
      i++;
    }
  }else{res = 0;}
  return res;
}

void PrintShell(){
        terminal_writecolour("\nroot@amogos ", 10);
    terminal_writecolour("$ ", 11);
    terminal_writecolour("", 15);
}

void reboot()
{
    uint8_t good = 0x02;
    while (good & 0x02)
        good = inb(0x64);
    outb(0x64, 0xFE);
    for(;;);
}
