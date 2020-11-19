# This script runs the the OS with qemu's -kernel and 
# thus does not support video mode

set -e
./build.sh

qemu-system-i386 -kernel sysroot/boot/myos.kernel
