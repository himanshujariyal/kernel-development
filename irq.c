/*
 * =====================================================================================
 *
 *       Filename:  irq.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Wednesday 15 October 2014 03:26:51  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <system.h>


extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();




void *irq_routines[16] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};



void irq_install_handler(int irq, void (*handler)(struct regs *r))
{
    irq_routines[irq] = handler;
}

void irq_uninstall_handler(int irq)
{
    irq_routines[irq] = 0;
}


void irq_remap(void)
{
    outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    outportb(0x21, 0x0);
    outportb(0xA1, 0x0);
}




void irq_install()
{
    irq_remap();

    idt_set_gate(32, (unsigned long)irq0, 0x08, 0x8E);
    idt_set_gate(33, (unsigned long)irq1, 0x08, 0x8E);
    idt_set_gate(34, (unsigned long)irq2, 0x08, 0x8E);
    idt_set_gate(35, (unsigned long)irq3, 0x08, 0x8E);
    idt_set_gate(36, (unsigned long)irq4, 0x08, 0x8E);
    idt_set_gate(37, (unsigned long)irq5, 0x08, 0x8E);
    idt_set_gate(38, (unsigned long)irq6, 0x08, 0x8E);
    idt_set_gate(39, (unsigned long)irq7, 0x08, 0x8E);
    idt_set_gate(40, (unsigned long)irq8, 0x08, 0x8E);
    idt_set_gate(41, (unsigned long)irq9, 0x08, 0x8E);
    idt_set_gate(42, (unsigned long)irq10, 0x08, 0x8E);
    idt_set_gate(43, (unsigned long)irq11, 0x08, 0x8E);
    idt_set_gate(44, (unsigned long)irq12, 0x08, 0x8E);
    idt_set_gate(45, (unsigned long)irq13, 0x08, 0x8E);
    idt_set_gate(46, (unsigned long)irq14, 0x08, 0x8E);
    idt_set_gate(47, (unsigned long)irq15, 0x08, 0x8E);
}


void irq_handler(struct regs *r)
{
    void (*handler)(struct regs *r);

    handler = irq_routines[r->int_no - 32];
    if (handler)
    {
        handler(r);
    }

    if (r->int_no >= 40)
    {
        outportb(0xA0, 0x20);
    }

    outportb(0x20, 0x20);
}


