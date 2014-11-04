#include <system.h>


/************************************************** file system ******************************************/

int cmpstr(char a[], int an, char b[], int bn)
{
  if(an!=bn) return 0;
  int i=0;
  while(i<an)
  {
/*    putch(a[i]);
    putch('\t');
    putch(b[i]);
    putch('\n');*/
    if(a[i]!=b[i]) return 0;
    i++;
  }
  return 1;
}

int find_file(char fname[], int fn)
{
  int i=0;
  while(i<current_dir.max_files)
  {
    if(cmpstr(fname,fn,all_files[current_dir.files[i]].name,all_files[current_dir.files[i]].size)==1) return current_dir.files[i];
    i++;
  }
  return -1;
}

int find_dir(char dname[], int dn)
{
  int i=0;
  while(i<current_dir.max_dirs)
  {
    if(cmpstr(dname,dn,all_dirs[current_dir.sub_dirs[i]].name,all_dirs[current_dir.sub_dirs[i]].size)==1) return current_dir.sub_dirs[i];
    i++;
  }
  return -1;
}

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


void delete_file(char file_name[], int n)
{
  int file = find_file(file_name, n);
  if(file==-1)
  {
    puts("No match found");
  }
  else   // for now only file reference is deleted -> node free entry still missing
  {
    int i=0;
    while(i<current_dir.max_files)
    {
      if(current_dir.files[i]==file) break;
      i++;
    }
    i++;
    while(i<current_dir.max_files)
    {
      current_dir.files[i-1]=current_dir.files[i];
      i++;
    }
    current_dir.max_files -= 1;

    puts("Deleted file\n");
  }
}


void delete_dir(char dir_name[], int n)
{
  int dir = find_dir(dir_name, n);
  if(dir==-1)
  {
    puts("No match found");
  }
  else   // for now only dir reference is deleted -> node free entry still missing
  {
    int i=0;
    while(i<current_dir.max_dirs)
    {
      if(current_dir.sub_dirs[i]==dir) break;
      i++;
    }
    i++;
    while(i<current_dir.max_dirs)
    {
      current_dir.sub_dirs[i-1]=current_dir.sub_dirs[i];
      i++;
    }
    current_dir.max_dirs -= 1;

    puts("Deleted dir\n");
  }
}

void rename_file(char file_name[], int n, char new_name[], int new_n)
{
  int file = find_file(file_name, n);
  if(file==-1)
  {
    puts("No match found");
  }
  else   // for now only file reference is deleted -> node free entry still missing
  {
    int i=0;
    while(i<new_n)
    {
      all_files[file].name[i]=new_name[i];
      i++;
    }
    all_files[file].size = new_n;
    puts("Renamed file\n");
  }
}

void rename_dir(char dir_name[], int n, char new_name[], int new_n)
{
  int dir = find_dir(dir_name, n);
  if(dir==-1)
  {
    puts("No match found");
  }
  else   // for now only dir reference is deleted -> node free entry still missing
  {
    int i=0;
    while(i<new_n)
    {
      all_dirs[dir].name[i]=new_name[i];
      i++;
    }
    all_dirs[dir].size = new_n;
    puts("Renamed dir\n");
  }
}
