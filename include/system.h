/*
 * =====================================================================================
 *
 *       Filename:  system.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Wednesday 15 October 2014 02:12:41  IST
 *       :wRevision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __BING_H
#define __BING_H

typedef int size_t;

struct regs
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;    
};



/* bingmain.c */
extern void *memcpy(void *dest, const void *src, size_t count);
extern void *memset(void *dest, char val, size_t count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);
extern size_t strlen(const char *str);
extern unsigned char inportb (unsigned short _port);
extern void outportb (unsigned short _port, unsigned char _data);

/* screen.c */
extern void init_video(void);
extern void puts(unsigned char *text);
extern void putch(unsigned char c);
extern void cls();
extern void putint(int n);
extern void line_collector(unsigned char scancode);
extern void line_parser();
extern void keyboard_handler(struct regs *r);


/* file system */
typedef struct file_node
{
  char name[128];          // The name of file should come under this limit
  int size;                // For now the size of the name of the file
  char* chunks[10];        // Gonna be the contents of the file for now -> Every line is a chunk
  int max_chunk;           // Limit for the chunk array
  char* last_modified;
} fnode;                   // file node can be created using "fnode new_file"


typedef struct dir_node
{
  char name[128];
  int size;
  int files[10];           // list of files -> int because it includes index of the file from all_files array
  int max_files;
  int sub_dirs[10];        // list of sub_dirs -> int as it contains index of the directory from all_dirs array
  int max_dirs;
  char* last_modified;
} dnode;

dnode current_dir;         // The current directory in which the user is
dnode all_dirs[100];       // The array of all dirs
int total_dirs;
fnode all_files[100];      // all files
int total_files;


extern void create_file(char file_name[], int n);
extern void create_dir(char dir_name[], int n);
extern void delete_file(char* file_name);
extern void delete_dir(char* dir_name);
extern void rename_file(char* file_name);
extern void rename_dir(char* dir_name);
extern void copy_file(char* file_name, char* dir_name);
extern void move_file(char* file_name, char* dir_name);

extern void show_contents();

/* gdt.c */

extern void gdt_install();
extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);


/* interrupts.c */

extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
extern void idt_install();
  
/* int_req.c */
extern void irq_install_handler(int irq, void (*handler)(struct regs *r));
extern void irq_uninstall_handler(int irq);
extern void irq_install();
extern void fault_handler(struct regs *r);

extern void keyboard_install();


#endif
