a-example-about-libqd-and-libqrencode
=====================================

a example about libqd and libqrencode ,it can make a qrencode png picture which can be decoded by a qrdecode scan software 
gcc qrcode.c -o qrcode -l gd -l qrencode 
./qrencode
