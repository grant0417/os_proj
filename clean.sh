set -e

PROJECTS="libc kernel"
SYSROOT="sysroot"
ISODIR="isodir"

for PROJECT in $PROJECTS; do
  (cd $PROJECT && DESTDIR="$SYSROOT" make clean)
done

rm -rf $SYSROOT $ISODIR *.iso
