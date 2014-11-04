#include <system.h>


/************************************************** file system ******************************************/


void create_file(char file_name[], int n)            // using mf command -> "mf file1"
{
  int i=0;
  while(i<n)
  {
    all_files[total_files].name[i] = file_name[i];
    i++;
  }
  all_files[total_files].size = n;
  all_files[total_files].chunks[0] = "New file!";
  all_files[total_files].max_chunk = 1;
  all_files[total_files].last_modified = "<Current Date>";
  current_dir.files[current_dir.max_files]=total_files;
  current_dir.max_files += 1;
  total_files++;
  i=0;
  while(i<n)
  {
    putch(all_files[total_files-1].name[i]);
    i++;
  }
  puts(" file added to ");
  i=0;
  while(i<current_dir.size)
  {
    putch(current_dir.name[i]);
    i++;
  }
  puts(" directory\n");
}


void create_dir(char dir_name[], int n)             // using md command -> "md dir1"
{
  int i=0;
  while(i<n)
  {
    all_dirs[total_dirs].name[i] = dir_name[i];
    i++;
  }
  all_dirs[total_dirs].size = n;
  all_dirs[total_dirs].max_files = 0;
  all_dirs[total_dirs].max_dirs = 0;
  all_dirs[total_dirs].last_modified = "<Current Date>";
  current_dir.sub_dirs[current_dir.max_dirs] = total_dirs++;
  current_dir.max_dirs += 1;
  i=0;
  while(i<n)
  {
    putch(all_dirs[total_dirs-1].name[i]);
    i++;
  }
  puts(" directory added to ");
  i=0;
  while(i<current_dir.size)
  {
    putch(current_dir.name[i]);
    i++;
  }
  puts(" directory\n");
}

void show_contents()                         // using ls command -> "ls"
{
  int i=0,j;
  puts("This directory's contents:\nFiles: ");
  putint(current_dir.max_files);
  putch('\n');
  while(i<(current_dir.max_files))
  {
    j=0;
    while(j<all_files[current_dir.files[i]].size)
    {
      putch(all_files[(current_dir.files[i])].name[j]);
      j++;
    }
    putch('\t');
    i++;
  }
  putch('\n');
  puts("Sub Directories: ");
  i=0;
  putint(current_dir.max_dirs);
  putch('\n');
  while(i<(current_dir.max_dirs))
  {
    j=0;
    while(j<all_dirs[current_dir.sub_dirs[i]].size)
    {
      putch(all_dirs[(current_dir.sub_dirs[i])].name[j]);
      j++;
    }
    putch('\t');
    i++;
  }
  putch('\n');
}






