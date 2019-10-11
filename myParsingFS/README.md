# myParsingFS
Usage : ./a.out [filesystemtype] -> ./a.out /dev/ramdisk

# example step
1. [ramdisk] make
2. [ramdisk] insmod ramdisk.ko
3. [ramdisk] mkfs.fat -F 32 /dev/ramdisk
4. [ramdisk] mkdir ./mnt
4. [ramdisk] mount /dev/ramdisk ./mnt
5. [myparsingFs] make
6. [myparsingFs] ./a.out /dev/ramdisk
