HOST=i386-elf
HOSTARCH=i386

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

CFLAGS=-ffreestanding -Wall -Wextra -O2 -g -D__is_kernel 
LIBS=-nostdlib -lk -lgcc 

ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

KERNEL_OBJS=$(KERNEL_ARCH_OBJS) kernel/kernel.o

OBJS=\
$(ARCHDIR)/crti.o\
$(ARCHDIR)/crtbegin.o\
$(KERNEL_OBJS)\
$(ARCHDIR)/crtend.o\
$(ARCHDIR)/crtn.o\

LINK_LIST=\
$(LDFLAGS) \
$(ARCHDIR)/crti.o\
$(ARCHDIR)/crtbegin.o\
$(KERNEL_OBJS)\
$(LIBS)\
$(ARCHDIR)/crtend.o\
$(ARCHDIR)/crtn.o\

ARCHDIR=arch/$(HOSTARCH)

.PHONY: all clean install install-headers install-kernel
.SUFFIXES: .o .c .S

all: myos.kernel

.S.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS)

.c.o: 
	$(CC) -MD -c $< -o $@ -std=gnu99 $(CFLAGS)

$(ARCHDIR)/crtbegin.o $(ARCHDIR)/crtend.o:
	OBJ=`$(CC) $(CFLAGS) --print-file-name=$(@F)` && cp "$$OBJ" $@

myos.kernel: $(ARCHDIR)/linker.ld $(OBJS)
	$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(LINK_LIST)
	grub-file --is-x86-multiboot myos.kernel

run: myos.kernel
	qemu-system-i386 -kernel myos.kernel

clean:
	rm -f myos.kernel
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-kernel
 
install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.
 
install-kernel: myos.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp myos.kernel $(DESTDIR)$(BOOTDIR)
 
-include $(OBJS:.o=.d)

