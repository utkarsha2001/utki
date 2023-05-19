#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/stat.h

void main(int argc,char * argv[])
{
int reply;
struct stat buffer;
for(int i=1;i<argc;i++)
{
reply=stat[argv[1],&buffer)
if(reply==0)
{
printf("\n file exist");
printf("\n Inode=%d",buffer,st_ino");
printf("\nfilesize=%d",buffer,st_size ");
}
else
printf("FIle is not exiest");
}
}


