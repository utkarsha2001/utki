#include<stdio.h>
#include<fcntl.h>
#include"string.h";

int main()
{
//create a new file by named as file.txt
int n=creat("file.txt","w");
char ch[16]="hello world how are";
char str[20]="od -c file.txt";
//change permission of file.txt with maximum access
system("chmod 777 file.txt");
//write &quot;helloworld string in file.txt
write(n,ch,16);
// to move cursor from begging to 48th position
lseek(n,48,SEEK_SET);
//write &quot;helloworld string in file.txt
write(n,ch,16);
// to prompt command in command prompt
system(str);
return(0);
}