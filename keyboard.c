/*
 * =====================================================================================
 *
 *       Filename:  keyboard.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Wednesday 15 October 2014 03:39:36  IST
 *       Revision:  5 Movember 2014
 *       Compiler:  gcc
 *
 *         Author:  Himanshu jariyal,
 *   Organization:
 *
 * =====================================================================================
 */


#include <system.h>

unsigned char keystatus[6] =
{
  0,//Alt  56
  0,//Control  29
  0,//left shift 42 
  0,//right shift 54
  0,//capslock 58
  0,//numlock 69
};
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
    0,	/* Alt 56*/
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

unsigned char kbdusShift[128] =
{
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*', /* 9 */
  '(', ')', '_', '+', '\b', /* Backspace */
  '\t',     /* Tab */
  'Q', 'W', 'E', 'R', /* 19 */
  'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\n',   /* Enter key */
    0,      /* 29   - Control */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', /* 39 */
 '\'', '~',   0,    /* Left shift */
 '\\', 'Z', 'X', 'C', 'V', 'B', 'N',      /* 49 */
  'M', '<', '>', '?',   0,          /* Right shift */
  '*',
    0,  /* Alt 56*/
  ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
  '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
  '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};

char line[80];
int k=0;
void line_collector(unsigned char scancode)
{       

  // 0,//Alt  56
  // 0,//Control  29
  // 0,//left shift 42 
  // 0,//right shift 54
  // 0,//capslock 58
  // 0,//numlock 69
        
        if(kbdus[scancode]=='\b'){
           k--;
           putch(kbdus[scancode]);
        }
        else if(kbdus[scancode]=='\n'){ line_parser();}
        else if(scancode == 56){
          //alt do nothing
          keystatus[0]='1';

        }
        else if(scancode == 29){
          //cntrl do nothing
          keystatus[1]='1';

        }
        else if(scancode == 42){
          //left shift
          keystatus[2]='1';
          //puts("shift ");
        }
        else if(scancode == 54){
          //right shift
          keystatus[3]='1';
        }
        else if(scancode == 58){
          //capslock
          if(keystatus[4] == '0'){
            keystatus[4]='1';  
          }
          else{
            keystatus[4]='0';
          }
        }
        else if(scancode == 69){
          //numlock
          keystatus[5]='1';
        }
        else {
          if(keystatus[2] =='1' || keystatus[3]=='1'){
            putch(kbdusShift[scancode]);
            line[k++]=kbdusShift[scancode];
            //puts("special");
          }
          else{
            putch(kbdus[scancode]);
            line[k++]=kbdus[scancode];
            //puts("normal");
          }
        }
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
       //char line[80] = {0};
   }
}

void keyboard_handler(struct regs *r)
{
    unsigned char scancode;

    scancode = inportb(0x60);
    // 0,//Alt  56
    // 0,//Control  29
    // 0,//left shift 42 
    // 0,//right shift 54
    // 0,//capslock 58
    // 0,//numlock 69
    if(scancode & 0x80){

      scancode &= ~(1 << 7);
        // putch('\n');
        // putch(kbdus[scancode]);
        // putch('\n');
        // released key 
        if(scancode == 56){
          //alt do nothing
          keystatus[0]='0';
          //puts("altreleased");
        }
        else if(scancode == 29){
          //cntrl do nothing
          keystatus[1]='0';
          //puts("cntrlreleased");
        }
        else if(scancode == 42){
          //left shift
          keystatus[2]='0';
          //puts("shiftreleased ");
        }
        else if(scancode == 54){
          //right shift
          keystatus[3]='0';
          //puts("rshiftreleased ");
        }
        else if(scancode == 58){
          //capslock
          if(keystatus[4] == '0'){
            keystatus[4]='1';  
          }
          else{
            keystatus[4]='0';
          }
        }
        else if(scancode == 69){
          //numlock
          keystatus[5]='0';
          //puts("released");
        }
        else{
          //do nothing
           //puts("releaunknown");
        }
    }
    else{
      line_collector(scancode);
    }
}


void keyboard_install()
{
    irq_install_handler(1, keyboard_handler);
}

/* KEYBOARD.C */
extern void keyboard_install();


