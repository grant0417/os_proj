.set ALIGN,    1<<0
.set MEMINFO,  1<<1
.set VIDINFO,  0<<2
.set FLAGS,    ALIGN | MEMINFO | VIDINFO  
.set MAGIC,    0x1BADB002       
.set CHECKSUM, -(MAGIC + FLAGS) 

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM
.long 0, 0, 0, 0, 0
.long 1 # EGA text mode
.long 80, 25, 0 # columns, rows
#.long 0 # EGA video mode
#.long 1024, 768, 24 # width, height, depth

 
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:
 
.section .text
.global _start
.type _start, @function
_start:

    mov $stack_top, %esp
 
    call _init

	  call kernel_main
  
  	cli
1:	hlt
  	jmp 1b
 
.size _start, . - _start
