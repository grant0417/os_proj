HOST=i386-elf
HOSTARCH=i386

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include
LIBDIR?=$(EXEC_PREFIX)/lib

CFLAGS=-ffreestanding -Wall -Wextra -O2 -g
LIBC_CFLAGS=$(CFLAGS) -D__is_libc 
LIBK_CFLAGS=$(CFLAGS) -D__is_libk
LIBS=-nostdlib -lgcc 

ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

KERNEL_OBJS=$(KERNEL_ARCH_OBJS) kernel/kernel.o

FREEOBJS=\
stdio/printf.o \
stdio/putchar.o \
stdio/puts.o \
stdlib/abort.o \
string/memcmp.o \
string/memcpy.o \
string/memmove.o \
string/memset.o \
string/strlen.o \

HOSTEDOBJS=\
$(ARCH_HOSTEDOBJS) \
 
OBJS=\
$(FREEOBJS) \
$(HOSTEDOBJS) \

LIBK_OBJS=$(FREEOBJS:.o=.libk.o)

BINARIES=libk.a

.PHONY: all clean install install-headers install-libs
.SUFFIXES: .o .libk.o .c .S

all: $(BINARIES)

libc.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)
 
libk.a: $(LIBK_OBJS)
	$(AR) rcs $@ $(LIBK_OBJS)

.S.o:
	$(AS) -MD -c $< -o $@ $(LIBC_CFLAGS)

.c.o: 
	$(CC) -MD -c $< -o $@ -std=gnu99 $(LIBC_CFLAGS)
 
.c.libk.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(LIBK_CFLAGS)
 
.S.libk.o:
	$(CC) -MD -c $< -o $@ $(LIBK_CFLAGS)
 
clean:
	rm -f $(BINARIES) *.a
	rm -f $(OBJS) $(LIBK_OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) $(LIBK_OBJS:.o=.d) *.d */*.d */*/*.d
 
install: install-headers install-libs
 
install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.
 
install-libs: $(BINARIES)
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp $(BINARIES) $(DESTDIR)$(LIBDIR)
 
-include $(OBJS:.o=.d)
-include $(LIBK_OBJS:.o=.d)

