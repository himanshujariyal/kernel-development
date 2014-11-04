/*
 * =====================================================================================
 *
 *       Filename:  idt.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Wednesday 15 October 2014 03:03:35  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         A
 *         uthor:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <system.h>


extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();




struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed));


struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));


struct idt_entry idt[256];
struct idt_ptr idtp;


extern void idt_load();


void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
    /* The interrupt routine's base address */
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;

    /* The segment or 'selector' that this IDT entry will use
    *  is set here, along with any access flags */
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}



void idt_install()
{
    /* Sets the special IDT pointer up, just like in 'gdt.c' */
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = &idt;
    
    memset(&idt, 0, sizeof(struct idt_entry) * 256);

    idt_set_gate(0, (unsigned long)isr0, 0x08, 0x8E);
    idt_set_gate(1, (unsigned long)isr1, 0x08, 0x8E);
    idt_set_gate(2, (unsigned long)isr2, 0x08, 0x8E);
    idt_set_gate(3, (unsigned long)isr3, 0x08, 0x8E);
    idt_set_gate(4, (unsigned long)isr4, 0x08, 0x8E);
    idt_set_gate(5, (unsigned long)isr5, 0x08, 0x8E);
    idt_set_gate(6, (unsigned long)isr6, 0x08, 0x8E);
    idt_set_gate(7, (unsigned long)isr7, 0x08, 0x8E);
    idt_set_gate(8, (unsigned long)isr8, 0x08, 0x8E);
    idt_set_gate(9, (unsigned long)isr9, 0x08, 0x8E);
    idt_set_gate(10, (unsigned long)isr10, 0x08, 0x8E);
    idt_set_gate(11, (unsigned long)isr11, 0x08, 0x8E);
    idt_set_gate(12, (unsigned long)isr12, 0x08, 0x8E);
    idt_set_gate(13, (unsigned long)isr13, 0x08, 0x8E);
    idt_set_gate(14, (unsigned long)isr14, 0x08, 0x8E);
    idt_set_gate(15, (unsigned long)isr15, 0x08, 0x8E);
    idt_set_gate(16, (unsigned long)isr16, 0x08, 0x8E);
    idt_set_gate(17, (unsigned long)isr17, 0x08, 0x8E);
    idt_set_gate(18, (unsigned long)isr18, 0x08, 0x8E);
    idt_set_gate(19, (unsigned long)isr19, 0x08, 0x8E);
    idt_set_gate(20, (unsigned long)isr20, 0x08, 0x8E);
    idt_set_gate(21, (unsigned long)isr21, 0x08, 0x8E);
    idt_set_gate(22, (unsigned long)isr22, 0x08, 0x8E);
    idt_set_gate(23, (unsigned long)isr23, 0x08, 0x8E);
    idt_set_gate(24, (unsigned long)isr24, 0x08, 0x8E);
    idt_set_gate(25, (unsigned long)isr25, 0x08, 0x8E);
    idt_set_gate(26, (unsigned long)isr26, 0x08, 0x8E);
    idt_set_gate(27, (unsigned long)isr27, 0x08, 0x8E);
    idt_set_gate(28, (unsigned long)isr28, 0x08, 0x8E);
    idt_set_gate(29, (unsigned long)isr29, 0x08, 0x8E);
    idt_set_gate(30, (unsigned long)isr30, 0x08, 0x8E);
    idt_set_gate(31, (unsigned long)isr31, 0x08, 0x8E);

    /* Points the processor's internal register to the new IDT */
    idt_load();
}



unsigned char *exception_messages[] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};


void fault_handler(struct regs *r)
{
    if (r->int_no < 32)
    {
        puts(exception_messages[r->int_no]);
        unsigned char* exceptmsg="Exception. System halted! \n";
        puts(exceptmsg);
        for (;;);
    }
}
