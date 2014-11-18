//a example about libqd and libqrencode ,it can make a qrencode png picture which can be decoded by a qrdecode scan software
//gcc qrcode.c -o qrcode -l gd -l qrencode
//./qrencode
#include <gd.h>
#include <qrencode.h>
#include <stdio.h>
#include <stdlib.h>
#include<stddef.h>
gdImagePtr qrcode_png (QRcode * code,int fg_color[3],int bg_color[3],int size,int margin);
int main ()
{
    char * encoded_content = "test";
    int version = 3;
    QRecLevel level = 2;
    QRencodeMode hint = QR_MODE_8;
    int casesensitive =1;
    int int_bg_color[3] = {255,255,255} ;
    int int_fg_color [3] = {0,0,0};
    int size = 100;
    int margin = 2;
    FILE * out = fopen("testgd.png","w+");
    if (out == NULL)
    {
        printf ("can not open the file testgd.png\n");
        return 0;
    }
    QRcode * code = QRcode_encodeString (encoded_content,version,level,hint,casesensitive);
    if (code == NULL)
    {
        printf("some error happened when encode the string\n");
        return 1;
    }
    gdImagePtr im = qrcode_png(code,int_fg_color,int_bg_color,size,margin) ;
    gdImagePng(im,out);
    QRcode_free (code);
    gdImageDestroy(im);
    fclose(out);
    return 0;
}
gdImagePtr qrcode_png(QRcode *code, int fg_color[3], int bg_color[3], int size, int margin)
{
    int code_size = size / code->width;
    code_size = (code_size == 0)  ? 1 : code_size;
    int img_width = code->width * code_size + 2 * margin;
    gdImagePtr img = gdImageCreate (img_width,img_width);
    int img_fgcolor =  gdImageColorAllocate(img,fg_color[0],fg_color[1],fg_color[2]);
    int img_bgcolor = gdImageColorAllocate(img,bg_color[0],bg_color[1],bg_color[2]);
    gdImageFill(img,0,0,img_bgcolor);
    u_char *p = code->data;
    int x,y ,posx,posy;
    for (y = 0 ; y < code->width ; y++)
    {
        for (x = 0 ; x < code->width ; x++)
        {
            if (*p & 1)
            {
                posx = x * code_size + margin;
                posy = y * code_size + margin;
                gdImageFilledRectangle(img,posx,posy,posx + code_size,posy + code_size,img_fgcolor);
            }
            p++;
        }
    }
    return img;
}
