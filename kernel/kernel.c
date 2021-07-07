#include "drivers/tty.c"
#include "initialization/ais.c"

/*
                S U S KERNEL
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣤⣤⣤⣀⣀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⠟⠉⠉⠉⠉⠉⠉⠉⠙⠻⢶⣄⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⣷⡀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⡟⠀⣠⣶⠛⠛⠛⠛⠛⠛⠳⣦⡀⠀⠘⣿⡄⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⠁⠀⢹⣿⣦⣀⣀⣀⣀⣀⣠⣼⡇⠀⠀⠸⣷⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⡏⠀⠀⠀⠉⠛⠿⠿⠿⠿⠛⠋⠁⠀⠀⠀⠀⣿
       ⠀⠀⢠⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⡇⠀
       ⠀⠀⣸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀
⠀⠀⠀⠀⠀⠀⠀⠀⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣧⠀
⠀⠀⠀⠀⠀⠀⠀⢸⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⠀
⠀⠀⠀⠀⠀⠀⠀⣾⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠀
⠀⠀⠀⠀⠀⠀⠀⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠀
⠀⠀⠀⠀⠀⠀⢰⣿⠀⠀⠀⠀⣠⡶⠶⠿⠿⠿⠿⢷⣦⠀⠀⠀⠀⠀⠀⠀⣿⠀
⠀⠀⣀⣀⣀⠀⣸⡇⠀⠀⠀⠀⣿⡀⠀⠀⠀⠀⠀⠀⣿⡇⠀⠀⠀⠀⠀⠀⣿⠀
⣠⡿⠛⠛⠛⠛⠻⠀⠀⠀⠀⠀⢸⣇⠀⠀⠀⠀⠀⠀⣿⠇⠀⠀⠀⠀⠀⠀⣿⠀
⢻⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⡟⠀⠀⢀⣤⣤⣴⣿⠀⠀⠀⠀⠀⠀⠀⣿⠀
⠈⠙⢷⣶⣦⣤⣤⣤⣴⣶⣾⠿⠛⠁⢀⣶⡟⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡟⠀
             ⠀⠀⠀⠈⣿⣆⡀⠀⠀⠀⠀⠀⠀⢀⣠⣴⡾⠃⠀
⠀⠀⠀⠀⠀            ⠈⠛⠻⢿⣿⣾⣿⡿⠿⠟⠋⠁⠀⠀⠀

Author: z3r0memory
Based on: OSDev wiki Bare Bones tutorial

*/



int get_command(){
  int cmd = 1;
  char string[10];
  getline(string, 10);
  execute_command(string);
  memset(string,0,10);
  terminal_writestring("\n");
  return cmd;
}

void execute_command(const char* cmd1){
  if(strcmp(cmd1,"reboot\x0D")==1){
       reboot();
  }
  else if(strcmp(cmd1,"afetch\x0D")==1){
      terminal_writecolour("\nOS", 13);
      terminal_writecolour(": AmogOS", 15);
      terminal_writecolour("\nKernel", 13);
      terminal_writecolour(": 0.0.1-amogkernel-i386", 15);
      terminal_writecolour("\nShell", 13);
      terminal_writecolour(": AShell", 15);
  }
  else if(strcmp(cmd1,"help\x0D")==1){
      terminal_writecolour("\nhelp", 13);
      terminal_writecolour(": List all commands", 15);
      terminal_writecolour("\nclear", 13);
      terminal_writecolour(": Clear the screen", 15);
      terminal_writecolour("\nreboot", 13);
      terminal_writecolour(": Reboot system", 15);
      terminal_writecolour("\nafetch", 13);
      terminal_writecolour(": Get some os info", 15);
  }
  else if(strcmp(cmd1,"clear\x0D")==1){
      terminal_initialize();
  }
  else if(strcmp(cmd1,"test2\x0D")==1){
      int a = 100;
      int b = a / 0;
      int c = 100 / 0;
      terminal_writestring("\n");
      terminal_writestring(c);
  }
  else{
    terminal_writestring("\nash: unknown command");
  }
  PrintShell();
  get_command();
}


void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();
 
	/* Newline support is left as an exercise. */
	terminal_writestring(" AmogKernel v1\n");
    terminal_writestring(" :: starting AIS\n");
    startAIS();
    get_command();
}