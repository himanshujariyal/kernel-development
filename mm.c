/*
 * =====================================================================================
 *
 *       Filename:  mm.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Tuesday 28 October 2014 08:56:34  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include<system.h>

void *memcpy(void *dest, const void *src, size_t count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

void *memset(void *dest, char val, size_t count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

int number_of_blocks = (MEM_HIGH-MEM_LOW)/PAGE_SIZE;



int used_blocks = 0;

int max_free_blocks = 0;

char bit_map[1535];

int first_free_block(){
    int i;
    for(i=0;i<number_of_blocks;i++){
        if(bit_map[i]=='0') return i;
    }
    return -1;
}

void mm_init(){
    int i;
    for(i=0;i<number_of_blocks;i++) bit_map[i]='0';
       
    putint(number_of_blocks);
}

int* mm_alloc_block(){

    int frame = first_free_block();
    
    if(frame==-1) return -1;

    bit_map[frame] = '1';
    
    int* physical_address = (int*) (frame*PAGE_SIZE+MEM_LOW);

    used_blocks++;

    return physical_address;
}


void mm_free_block(int* p){
    int frame = (int)p/PAGE_SIZE;
    
    bit_map[frame] = '0';

   used_blocks--;
}


void print_mm_things(){
    puts("Just Memory things \n");
    puts("Number of blocks : ");
    putint(number_of_blocks);
    putch('\n');
    int i;
    for(i=0;i<number_of_blocks;i++){
        putch(bit_map[i]);
    }
    putch('\n');
    int free_block = first_free_block();
    int free_address = mm_alloc_block();
    putint(free_block);
    putch('\n');
    putint(free_address); 
    putch('\n');
    for(i=0;i<number_of_blocks;i++){
        putch(bit_map[i]);
    }
     
}


