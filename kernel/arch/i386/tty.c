#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "vga.h"
#include "port.h"

#define SCREEN_CTRL 0x3D4
#define SCREEN_DATA 0x3D5

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
size_t terminal_color;
uint16_t* terminal_buffer;

void terminal_enablecursor(uint8_t cursor_start, uint8_t cursor_end) {
  byte_out(SCREEN_CTRL, 0x0A);
	byte_out(SCREEN_DATA, (byte_in(SCREEN_DATA) & 0xC0) | cursor_start);
 
	byte_out(SCREEN_CTRL, 0x0B);
	byte_out(SCREEN_DATA, (byte_in(SCREEN_DATA) & 0xE0) | cursor_end);
}

void terminal_cursordisable() {
  byte_out(SCREEN_CTRL, 0x0A);
  byte_out(SCREEN_DATA, 0x20);
}

size_t terminal_getcursorposition() {
  byte_out(SCREEN_CTRL, 14);
  int position = byte_in(SCREEN_DATA);
  position = position << 8;
  byte_out(SCREEN_CTRL, 15);
  position += byte_in(SCREEN_DATA);
  return position;
}

void terminal_setcursorposition(size_t index){
  byte_out(SCREEN_CTRL, 14);
  byte_out(SCREEN_DATA, (unsigned char)(index >> 8));
  byte_out(SCREEN_CTRL, 15);
  byte_out(SCREEN_DATA, (unsigned char)(index & 0xff));
}

void terminal_initialize(void) {
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  terminal_buffer = (uint16_t*) 0xB8000;
  terminal_enablecursor(0, 15);
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      terminal_buffer[index] = vga_entry(' ', terminal_color);
    }
  }
}

void terminal_setcolor(uint8_t color) {
  terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
  const size_t index = y * VGA_WIDTH + x;
  terminal_buffer[index] = vga_entry(c, color);
  terminal_setcursorposition(index + 1);
}

void terminal_putchar(char c) {
  if (c == '\n' || c == '\r') {
    terminal_row += 1;
    terminal_column = 0;
  } else if (c == '\t') {
    terminal_putchar(' ');
    terminal_putchar(' ');
    terminal_putchar(' ');
    terminal_putchar(' ');
  } else {
    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH) {
     terminal_column = 0;
      if (++terminal_row == VGA_HEIGHT) {
        terminal_row = 0;
      }
    }
  }
}

void terminal_write(const char* data, size_t size) {
  for (size_t i = 0; i < size; i++) {
    terminal_putchar(data[i]);
  }
}

void terminal_writestring(const char* data) {
  terminal_write(data, strlen(data));
}

void terminal_scroll(size_t lines) {
  // Moves lines
  for (size_t y = lines; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index_from = y * VGA_WIDTH + x;
      const size_t index_replace = (y - lines) * VGA_WIDTH + x;
      terminal_buffer[index_replace] = terminal_buffer[index_from];
    }
  }
  // Clear bottom lines
  for (size_t y = VGA_HEIGHT - lines; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index_clear = y * VGA_WIDTH + x;
      terminal_buffer[index_clear] = vga_entry(' ', terminal_color);
    }
  }

  terminal_row -= lines;
}

