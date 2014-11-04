/*
 * =====================================================================================
 *
 *       Filename:  process.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Monday 03 November 2014 06:10:42  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <system.h>
#define MAX_TASKS 100
struct task_struct
{
	int state;   
    int pid;
    int priority;
    int process_table_number;

    int exit_code;

    int runtime;
    int start_time;
    int deadline;
    
    int start_stack;
    int start_code,end_code;
    int start_data,end_data;
    int code_limit;
    int data_limit;

    struct tss_struct task_state_segment;

    struct inode* present;
    struct inode* root;
    struct file* files[];
};

struct process_table
{
    task_struct tasks[MAX_TASKS];
    int scheduling_algo;
    int pt_start;
    int pt_end;
    task_struct* current;
};

task_struct init_task = {
    0,1,1,1,0,5,0,10,
}

process_table PT;

PT->scheduling_algo=0;

PT->current = PT->tasks[1];

pt_start = 0;

pt_end = 1;

void schedule(){
    int next;
    if(PT -> scheduling_algo == 0){
            for(int i=pt_start ;i <= pt_end; i++){
                if((PT-> tasks[i])->state == READY)
                {
                    PT -> state = RUNNING;
                    next = i;
                    break;
                }
            }
            switch_to(next);
         }
   /* else if( PT -> scheduling_algo == 1) ........ */
    }

void kill(nr){
    task_struct* p = PT -> tasks[nr];
    mm_free_block(p-> start_code);
    p = NULL;
   /*  free_space(p);  */

}

/*
void exec(char* path){

    f_inode* inode = get_inode(path);
        
    int* free_block =  first_free_block();

    
*/
