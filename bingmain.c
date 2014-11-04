/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Wednesday 15 October 2014 02:08:15  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <system.h>
size_t strlen(const char *str)
{
    size_t retval;
    for(retval = 0; *str != '\0'; str++) retval++;
    return retval;
}

unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

void bingmain()
{

    init_video();
    gdt_install();
    idt_install();
    irq_install(); 
    keyboard_install();

    all_dirs[0].name[0] = 'r';
    all_dirs[0].name[1] = 'o';
    all_dirs[0].name[2] = 'o';
    all_dirs[0].name[3] = 't';
    all_dirs[0].size = 4;
    all_dirs[0].max_files = 0;
    all_dirs[0].max_dirs = 0;
    current_dir = all_dirs[0];
    total_dirs=1;
    total_files=0;


 __asm__ __volatile__ ("sti");
    settextcolor(0x1, 0x0);
    puts("                         Welcome to  BingOS! \n");
    settextcolor(0xf, 0x0);

    int i=0;
    puts("Currently into ");
    while(i<current_dir.size)
    {
       putch(current_dir.name[i]);
       i++;
    }
    puts(" directory\n");

    for (;;);


}
