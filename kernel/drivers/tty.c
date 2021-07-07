#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "vga.h"
#include "tty.h"
#include "../devices/keyboard.c"
#include <string.h>
#include "../lib/memory.c"


size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
 
void terminal_putchar(char c, int color) 
{
	if(c == '\n')
        {
            terminal_row = terminal_row + 1;
            terminal_column = 0;
		}
	else{
	terminal_putentryat(c, color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}
}

void terminal_write(const char* data, size_t size, int color) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i], color);
}
 
void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data), terminal_color);
}
 
void terminal_writecolour(const char* data, int colour) 
{
	terminal_write(data, strlen(data), colour);
}
 char getchar(){              
    uint8_t code = 0;
    uint8_t key = 0;
    while(1){
      if (kybrd_ctrl_read_status () & KYBRD_CTRL_STATS_MASK_OUT_BUF) {
        code = kybrd_enc_read_buf ();
        if(code <= 0x58){ //is in range??
          key = _kkybrd_scancode_std [code];
          break;
        }
      }
    }
    return key;
}
void getline(char* string, int len){
uint8_t i=0;
  int flag = 0;
  char temp = 0;
  memset(string,0,len);
  while(i<255 && temp != 0x0D){
    temp = getchar();
    if(isascii(temp) && temp != 0x0D){ //0x0D is ENTER
      if(temp == 0x08){   //backspace
        terminal_column--;
        terminal_putentryat(' ',terminal_color, terminal_column, terminal_row); //cancel last char
        i--;
      }else{
      terminal_putchar(temp, 10);
      string[i] = temp;
      i++;}
    }
  }
  string[i] = 0x0A; //endline
}