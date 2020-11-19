#include <kernel/tty.h>
#include <stdio.h>

#if defined (__linux__)
#error "You are not using a cross-compiler, this will likely cause issues"
#endif

#if !defined (__i386__)
#error "The compiler must be at least a i386-elf compiler"
#endif


int kernel_main(void) {
  terminal_initialize();
  terminal_writestring("Hello, kernel World!\nMore text\n\nSome more too!!!");
  terminal_scroll(2);
  terminal_writestring("More text after scroll\nLots of text\n\tIndented text");
  terminal_writestring("\t\tDouble Indented text\tMore text\nHello");
  //__asm__("int $4");
  return 0xDEADBEEF;
}

