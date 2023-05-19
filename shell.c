#include &lt;stdio.h&gt;
#include &lt;string.h&gt;
#include &lt;sys/types.h&gt;
#include &lt;sys/wait.h&gt;
#include &lt;sys/stat.h&gt;
#include &lt;fcntl.h&gt;
#include &lt;dirent.h&gt;
//#include &lt;bfd.h&gt;
char comm[100],*ptr;
char *args[10];
int tot_arg;
int search(char option, char *pattern, char *fname);
int count( char option, char *fname);
int typeline( char *option, char *fname);
int list( char option, char dirname[]);
main()
{
do
{
printf(&quot;myshell $ &quot;);
getcomm();
sep_arg();
take_action();
}while(1);
} // main
sep_arg()
{
int i,j;
i = j = tot_arg = 0;
args[tot_arg] = (char*)malloc(sizeof(char) * 20);
for(i=0; comm[i] !=&#39;\0&#39; ; i++)
{
if( comm[i] == &#39; &#39;)
{
args[tot_arg][j] = &#39;\0&#39;;
tot_arg++;
args[tot_arg] = (char*)malloc(sizeof(char) * 20);
j=0;
}
else
{
args[tot_arg][j] =comm[i];
j++;
}
} // while
args[tot_arg][j] = &#39;\0&#39;; // complete last word
return;
}

getcomm()
{
int len;
ptr = fgets(comm,80,stdin);
len = strlen(comm);
comm[len-1] = &#39;\0&#39;;

return;
} // getcomm
take_action()
{
char str[100];
pid_t pid;
int status;
if(strcmp(args[0],&quot;search&quot;) == 0 )
search(*args[1],args[2],args[3]);
else
if(strcmp(args[0],&quot;count&quot;) == 0 )
count(*args[1],args[2]);
else
if(strcmp(args[0],&quot;typeline&quot;) == 0 )
typeline(args[1],args[2]);
else
if(strcmp(args[0],&quot;list&quot;) == 0 )
list(*args[1],args[2]);
else
{
if( ptr == NULL )
exit(0);
if ( strlen(comm) &lt;= 1 )
return;
if( ( pid = fork() ) &lt; 0 )
{
printf(&quot;\nUnable to create process&quot;);
}
else
if( pid == 0 ) // child
{ sscanf(comm,&quot;%s&quot;,comm);
execvp(comm,args);
strcpy(str,&quot;./&quot;);
strcat(str,args[0]);
execvp(str,args);
printf(&quot;\n%s : command not found&quot;,comm);
exit(0);
}
else //parent
waitpid(pid,&amp;status,0);
} // else
}// take action
int search(char option, char *pattern, char *fname)
{
char buff[100],*ptr;
int cnt;
FILE *fp;
int i;
fp= fopen(fname,&quot;r&quot;);
if( fp == NULL )
{
printf(&quot;\nUnable to open file&quot;);
exit(0);
}
switch(option)
{
case &#39;a&#39; : // print all occ
while ( !feof (fp))
{

buff[0] = &#39;\0&#39;;
fgets(buff,80,fp);
ptr = strstr(buff,pattern);
if( ptr != NULL )
printf(&quot;%s&quot;,buff);

}
fclose(fp);
break;
case &#39;c&#39; : // count occ
cnt=0;
while ( !feof (fp))
{
buff[0] = &#39;\0&#39;;
fgets(buff,80,fp);
ptr = strstr(buff,pattern);
while(ptr != NULL )
{
cnt++;
ptr = ptr + strlen(pattern);
ptr = strstr(ptr,pattern);
} // while
}
fclose(fp);
printf(&quot;\nThe serach string %s occurs %d

times&quot;,pattern,cnt);

break;
case &#39;f&#39; : //print first occ
while ( !feof (fp))
{
buff[0] = &#39;\0&#39;;
fgets(buff,80,fp);
ptr = strstr(buff,pattern);
if( ptr != NULL )
{
printf(&quot;%s&quot;,buff);
break;
}
}
fclose(fp);
break;
} // switch
return;
}//search
int count( char option, char *fname)// count c/w/l &lt;filename&gt;
{
int ccnt,wcnt,lcnt,wflag;
int ch;
FILE *fp;
int i;
fp= fopen(fname,&quot;r&quot;);
if( fp == NULL )
{
printf(&quot;\nUnable to open file&quot;);
exit(0);
}
ccnt =wcnt = lcnt = 0;
wflag=1;
ch = fgetc(fp);
while ( ch != EOF)
{
ccnt++;
if( ch ==&#39; &#39; || ch== &#39;\t&#39;)

{
if( wflag == 0 )
{
wcnt++;
wflag = 1;
}
}
else
if( ch == &#39;\n&#39;)
{
lcnt++;
if( wflag == 0 )
{
wcnt++;
wflag = 1;
}
}
else
{
wflag = 0;
}
ch = fgetc(fp);
}//while
if( wflag == 0 )
{
wcnt++;
lcnt++;
}
fclose(fp);
switch(option)
{
case &#39;c&#39; : // print all chars

printf(&quot;\nTot chars = %d\n&quot;,ccnt);
break;
case &#39;w&#39; : // print all words

printf(&quot;\nTot words = %d\n&quot;,wcnt);
break;
case &#39;l&#39; : // print all lines

printf(&quot;\nTot lines = %d\n&quot;,lcnt);
break;

} // switch
return;
}// count
int typeline( char *option, char *fname)
{
FILE *fp;
int tot_lines,ch,n,cnt;
//---- count the lines
fp= fopen(fname,&quot;r&quot;);
if( fp == NULL )
{
printf(&quot;\nUnable to open file&quot;);
exit(0);
}
tot_lines = 0;//count total lines
ch = fgetc(fp);
while ( ch != EOF )
{
if( ch == 10 ) //new line char
tot_lines++;
ch = fgetc(fp);
}
fclose(fp);

//---- take action
if( strcmp(option,&quot;a&quot;)== 0 ) // print all lines
{
fp= fopen(fname,&quot;r&quot;);
ch = fgetc(fp);
while ( ch != EOF )
{
printf(&quot;%c&quot;,ch);
ch = fgetc(fp);
}
fclose(fp);
}
else
if( option[0] ==&#39;+&#39;) //print first n lines)
{
n = atoi(option+1);
if( n &gt; tot_lines)
{
printf(&quot;\nInvalid option&quot;);
exit(0);
}
fp= fopen(fname,&quot;r&quot;);
cnt = 0;
while( cnt &lt; n )
{
ch = fgetc(fp);
printf(&quot;%c&quot;,ch);
if( ch == 10)
cnt++;

}
fclose(fp);
}
else
if( option[0] ==&#39;-&#39;) //print last n lines)
{
n = atoi(option+1);
if( n &gt; tot_lines)
{
printf(&quot;\nInvalid option&quot;);
exit(0);
}
fp= fopen(fname,&quot;r&quot;);
cnt = 0;
while( cnt &lt; tot_lines -n )
{
ch = fgetc(fp);
if( ch == 10)
cnt++;

}
while( (ch=fgetc(fp)) != EOF )
printf(&quot;%c&quot;,ch);
fclose(fp);
}
else
{
printf(&quot;\nInvalid option&quot;);
exit(0);
}
return(0);
} //typeline
int list( char option, char dirname[])
{

DIR *dp;
struct dirent *dent;
struct stat buff;
char orgdir[100];
int cnt,reply;
getcwd(orgdir,90);
chdir(dirname);
switch(option)
{
case &#39;f&#39; : // list all dir entries
dp= opendir(&quot;.&quot;);
if( dp == NULL )
{
printf(&quot;\nUnable to open dir&quot;);
exit(0);
}
dent = readdir(dp);
while( dent != NULL )
{
printf(&quot;\n%s&quot;,dent-&gt;d_name);
dent= readdir(dp);
}
printf(&quot;\n&quot;);
break;

case &#39;n&#39; : // list number all dir entries

cnt =0;
dp= opendir(&quot;.&quot;);
if( dp == NULL )
{
printf(&quot;\nUnable to open dir&quot;);
exit(0);
}
dent = readdir(dp);
while( dent != NULL )
{
cnt++;
dent= readdir(dp);
}
printf(&quot;\ntot dir entries = %d\n&quot;,cnt);
closedir(dp);
break;

case &#39;i&#39; : // list all dir entries with inode

dp= opendir(&quot;.&quot;);
if( dp == NULL )
{
printf(&quot;\nUnable to open dir&quot;);
exit(0);
}
dent = readdir(dp);
while( dent != NULL )
{
reply = stat(dent-&gt;d_name,&amp;buff);
if( reply &lt; 0 )
printf(&quot;\nError&quot;);
else
printf(&quot;\n%s %ld&quot;,dent-&gt;d_name,buff.st_ino);
dent= readdir(dp);
}
closedir(dp);
break;

default : printf(&quot;\nInvalid option&quot;);

exit(0);

} // switch
chdir(orgdir);

return(0);