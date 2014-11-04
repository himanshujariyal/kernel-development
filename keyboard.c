/*
 * =====================================================================================
 *
 *       Filename:  keyboard.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Wednesday 15 October 2014 03:39:36  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */


#include <system.h>


unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',		/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,					/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

char line[80];
int k=0;
void line_collector(unsigned char scancode)
{
     putch(kbdus[scancode]);
     if(kbdus[scancode]=='\b'){
         k--;
     }
     else if(kbdus[scancode]=='\n'){ line_parser();}
     else line[k++]=kbdus[scancode];
}

void line_parser()
{   
   int l=k;
   k=0;
   int i;
   if(line[0]=='e' && line[1]=='c' && line[2]=='h' && line[3]=='o'){
       for(i=7; i<l-1 ;i++){
           putch(line[i]);
       } 
       putch('\n');
   }
   else if(line[0]=='w' && line[1]=='a' && line[2]=='s')
       puts("Aye captain! This is your kernel here. :-) \n");
   else if(line[0]=='h' && line[1]=='o' && line[2]=='w')
       puts("Everythings great! I need to grow fast right now! ;-) \n");
   else if(line[0]=='b' && line[1]=='y' && line[2]=='e')
       puts("Oh Captain! My Captain! I will miss you. :'( \n");

   else if((line[0]=='m' || line[0]=='d') && (line[1]=='f' || line[1]=='d'))
   {
     int i=3;
     char c0 = line[0], c1 = line[1];
     while(i<l)
     {
       line[i-3]=line[i];
       i++;
     }
     if(c0=='m' && c1=='f') create_file(line,i-3);
     else if(c0=='m' && c1=='d') create_dir(line,i-3);
     else if(c0=='d' && c1=='f') delete_file(line,i-3);
     else if(c0=='d' && c1=='d') delete_dir(line,i-3);
   }
   else if(line[0]=='l' && (line[1]=='s')) show_contents();

   else{
       int first_number=0;
       int second_number=0;
       char operation;
       i=0;
       while(line[i]!='+' && line[i]!='-' && line[i]!='*' && line[i]!='/' && line[i]!=' ')
       {
           first_number*=10;
           first_number+=(int)(line[i])-48;
           i++;
       }
       while(line[i]==' ') i++;
       operation=line[i++];
       while(line[i]==' ') i++;
       while(i<l)
       {
           second_number*=10;
           second_number+=(int)(line[i]-'0');
           i++;
       }
       int ans;
       if(operation=='+') putint(first_number+second_number);
       if(operation=='-') putint(first_number-second_number);
       if(operation=='*') putint(first_number*second_number);
       if(operation=='/') putint(first_number/second_number);
       putch('\n');
   }
}

void keyboard_handler(struct regs *r)
{
    unsigned char scancode;

    scancode = inportb(0x60);

    if(!(scancode >> 7))
    line_collector(scancode);
}


void keyboard_install()
{
    irq_install_handler(1, keyboard_handler);
}

/* KEYBOARD.C */
extern void keyboard_install();




