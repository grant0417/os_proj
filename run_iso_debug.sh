set -e
./iso.sh

qemu-system-i386 -s -cdrom myos.iso & gdb -ex "target remote localhost:1234" -ex "symbol-file sysroot/boot/myos.kernel" -ex 'break kernel_main' -tui 
