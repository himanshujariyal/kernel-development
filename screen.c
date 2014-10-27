/*
 * =====================================================================================
 *
 *       Filename:  screen.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Wednesday 15 October 2014 02:11:19  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <system.h>

unsigned short *textmemptr;
int attrib = 0x0F;
int csr_x = 0, csr_y = 0;
int blue_att = 0x01;
int red_att = 0x04;


void scroll(void)
{
    unsigned blank, temp;

    blank = 0x20 | (attrib << 8);

    if(csr_y >= 25)
    {
        temp = csr_y - 25 + 1;
        memcpy (textmemptr, textmemptr + temp * 80, (25 - temp) * 80 * 2);

        memsetw (textmemptr + (25 - temp) * 80, blank, 80);
        csr_y = 25 - 1;
    }
}


void move_csr(void)
{
    unsigned temp;

/*     The equation for finding the index in a linear
    *  chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    temp = csr_y * 80 + csr_x;
    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);

}


void cls()
{
    unsigned blank;
    int i;

    /* Again, we need the 'short' that will be used to
    *  represent a space with color */
    blank = 0x20 | (attrib << 8);

    /* Sets the entire screen to spaces in our current
    *  color */
    for(i = 0; i < 25; i++)
        memsetw (textmemptr + i * 80, blank, 80);

    /* Update out virtual cursor, and then move the
    *  hardware cursor */
    csr_x = 0;
    csr_y = 0;
    move_csr();
}


void putch(unsigned char c)
{
    unsigned short *where;
    unsigned att = attrib << 8;
    /* Handle a backspace, by moving the cursor back one space */
    if(c == 0x08)
    {
        if(csr_x > 9 ) {
            csr_x--;
            where = textmemptr + csr_y*80 + csr_x;
            *where = ' ' | att;
        }

    }
    /* Handles a tab by incrementing the cursor's x, but only
    *  to a point that will make it divisible by 8 */
    else if(c == 0x09)
    {
        csr_x = (csr_x + 8) & ~(8 - 1);
    }
    /* Handles a 'Carriage Return', which simply brings the
    *  cursor back to the margin */
    else if(c == '\r')
    {
        csr_x = 0;
    }
    /* We handle our newlines the way DOS and the BIOS do: we
    *  treat it as if a 'CR' was also there, so we bring the
    *  cursor to the margin and we increment the 'y' value */
    else if(c == '\n')
    {
        csr_x = 0;
        csr_y++;
        scroll();
        settextcolor(0x4,0x0);
        puts("guest:~$ ");
        settextcolor(0xf,0x0);
    }
    /* Any character greater than and including a space, is a
    *  printable character. The equation for finding the index
    *  in a linear chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    else if(c >= ' ')
    {
        where = textmemptr + (csr_y * 80 + csr_x);
        *where = c | att;	/* Character AND attributes: color */
        csr_x++;
    }

    /* If the cursor has reached the edge of the screen's width, we
    *  insert a new line in there */
    if(csr_x >= 80)
    {
        csr_x = 0;
        csr_y++;
    }

    /* Scroll the screen if needed, and finally move the cursor */
    scroll();
    move_csr();
}


void puts(unsigned char *text)
{
    int i;

    for (i = 0; i < strlen((const char*)text); i++)
    {
        putch(text[i]);
    }
}
char r[20];
void putint(int n){
     if(n==0) putch('0');
    else{
        int i=0;
        int t;
        while(n!=0){
            t=n%10;
            n=n/10;
            r[i++]=(t+'0');
        }
        int j;
        for(j=i-1;j>=0;j--) putch(r[j]);

    }
}


void settextcolor(unsigned char forecolor, unsigned char backcolor)
{
    /* Top 4 bytes are the background, bottom 4 bytes
    *  are the foreground color */
    attrib = (backcolor << 4) | (forecolor & 0x0F);
}


void init_video(void)
{
    textmemptr = (unsigned short *)0xB8000;
    cls();
}


