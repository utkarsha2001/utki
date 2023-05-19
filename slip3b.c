// Print the type of file where file name accepted through Command Line
#include <stdio.h>
#include <sys/types>
#include <dirent>
#include <sys/stat>
int main(int argc,char *argv[])
{ 
    int i;
struct stat st; 
for(i=0;i<argc;i++)
{
 stat(argv[i], &st);
if(S_ISDIR(st.st_mode))
printf("\n type of file %s is directory",argv[i]);
else if(S_ISREG(st.st_mode))
printf("\n type of file %s is Regular file",argv[i]);
else
printf("\n other than directory or regular file...");

}
return 0;
}