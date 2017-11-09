git pull
rmmod usb_mouse
make clean
make
rmmod usbhid
insmod usb-mouse.ko