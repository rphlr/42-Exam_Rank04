#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
void p(char*s,char*a){while(*s)write(2,s++,1);if(a)while(*a)write(2,a++,1);write(2,"\n",1);}void e(char*v[],int i,int t,char*n[]){v[i]=NULL;dup2(t,0);close(t);execve(v[0],v,n);p("error: cannot execute ",v[0]);}int main(int c,char*v[],char*n[]){(void)c;int i=0,f[2],t=dup(0);while(v[i]&&v[i+1]){v=&v[i+1];i=0;while(v[i]&&strcmp(v[i],";")&&strcmp(v[i],"|"))i++;if(!strcmp(v[0],"cd")){if(i!=2)p("error: cd: bad arguments",NULL);else if(chdir(v[1]))p("error: cd: cannot change directory to ",v[1]);}else if(i&&(!v[i]||!strcmp(v[i],";"))){if(!fork())e(v,i,t,n);else{close(t);while(waitpid(-1,NULL,2)!=-1)
;t=dup(0);}}else if(i&&!strcmp(v[i],"|")){pipe(f);if(!fork()){dup2(f[1],1);close(f[0]);close(f[1]);e(v,i,t,n);}else{close(f[1]);close(t);t=f[0];}}}close(t); return 0;}
