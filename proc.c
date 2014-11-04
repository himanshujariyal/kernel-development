/*
 * =====================================================================================
 *
 *       Filename:  proc.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Tuesday 04 November 2014 04:30:23  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <system.h>
extern void execute();

int process_stack;
int process_start;

void loadProcesses(void (*processhandler)()){
    int dest = mm_alloc_block();
    memcpy(dest, processhandler, PAGE_SIZE); 
    process_start = dest;
    process_stack = mm_alloc_block();
    putint(process_start); putch('\n');
    putint(process_stack); putch('\n');
    execute();
}

void process1(){
    puts(" Process 1 executing now");
}

void process_init(){
    void (*prochandler)() = &process1;
    loadProcesses(prochandler);
}

void debug(){
    puts("Its working \n");
}
