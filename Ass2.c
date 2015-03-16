#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <wait.h>
#include<fcntl.h>


int j=0;
struct rec{
	int flag;
	pid_t pid;
	char pro[100];
	};
typedef struct rec proc;
proc struc[100];


void sig_handler(int signum){
	if(signum == 2 || signum == 20){
//	printf("\nEnter \"quit\" to terminate the program\n");
		return;
	}
	signal(SIGINT, sig_handler);
	signal(SIGTSTP, sig_handler);
	return;
}


void child_handler(int signum){
	int l=0;
	pid_t pid;
	pid = waitpid(WAIT_ANY, NULL, WNOHANG);
	for(l=0;l<j;l++)
	{
		if(struc[l].pid==pid)
			struc[l].flag=1;
	}



/*	if(pid != -1){
		printf("child is Dead\n");
	}*/
	signal(SIGCHLD, child_handler);
	return;
}



void fung(char *a1[],char *a2[])
{

///			printf("in greater than : a1[0]= %s a1[1] = %s a2[0]= %s a2[1]=%s\n",a1[0],a1[1],a2[0],a2[1]);
			int fd,tmp_fd;
			pid_t pid;
			fd=open(*a2,O_TRUNC|O_CREAT|O_WRONLY,00644);
			tmp_fd=dup(1);
			dup2(fd,1);
			struc[j].pid=fork();                                             // calling fork
			if(struc[j].pid==0)
				execvp(*a1,a1);
			else
			{
				int statusnew1;
				wait(&statusnew1);
				close(fd);
				struc[j].flag=1;
				j=j+1;
				dup2(tmp_fd,1);
				return;
			}



}

void funl(char *a1[],char *a2[])
{
//			printf("in lesser than :a1[0]= %s a1[1] = %s a2[0]= %s a2[1]=%s\n",a1[0],a1[1],a2[0],a2[1]);
			int fd1,tmp_fd1;
			pid_t pid1;
			fd1=open(*a2,O_RDONLY,0);
			tmp_fd1=dup(0);
			dup2(fd1,0);
			struc[j].pid=fork();                                             // calling fork
			if(struc[j].pid==0)
				execvp(*a1,a1);
			else
			{
				int statusnew2;
				wait(&statusnew2);
				struc[j].flag=1;
				j=j+1;
				close(fd1);
				dup2(tmp_fd1,0);
			}
				return;
}

void fungl(char *a1[],char *a2[],char *a3[])
{
//			printf("in both : a1[0]= %s a1[1] = %s a2[0]= %s a2[1]=%s a3[0]=%s a3[1]=%s\n",a1[0],a1[1],a2[0],a2[1],a3[0],a3[1]);

			int fd,fd1,tmp_fd,tmp_fd1;
		
			fd=open(*a3,O_TRUNC|O_CREAT|O_WRONLY,00644);
			fd1=open(*a2,O_RDONLY,0);
			tmp_fd=dup(1);
			dup2(fd,1);
			tmp_fd1=dup(0);
			dup2(fd1,0);
			pid_t pid2;
					
			struc[j].pid=fork();	
			if(pid2==0)
				execvp(*a1,a1);
			else
			{
				int statusnew3;
				wait(&statusnew3);
				close(fd1);
				close(fd);
				struc[j].flag=1;
				j=j+1;
				dup2(tmp_fd,1);
				dup2(tmp_fd1,0);
			}
				return;
}



/*void pipefunc(char string[]){
	char str[256];
	strcpy(str,string);
	char *cmd1[20];
	char *cmd2[20];
	char *cmd3[20];
	char *cmd4[20];
	int pfd[2];
	int i1=0,i2=0,i3=0;
	cmd1[0]=strtok(string,"|");
	while((cmd1[++i1]=strtok(NULL,"|"))!=NULL);
	cmd2[0]=strtok(cmd1[0]," ");
	while((cmd1[++i1]=strtok(NULL," "))!=NULL);
	cmd3[0]=strtok(cmd1[1]," ");
	while((cmd1[++i1]=strtok(NULL," "))!=NULL);

	pid_t pid;
	pid=fork();
	if(pid==0){
		close(pfd[0]);
		dup2(pfd[1],1);
		execvp(*cmd2,cmd2);
		_exit(0);
	}
	else{
		close(pfd[1]);
		wait(NULL);
	}
	if(fork()==0){
		dup2(pfd[0],0);
		close(pfd[0]);
		execvp(*cmd3,cmd3);
		_exit(0);
	}
	else{
		wait(NULL);
	}
	return;
}*/
int main( int argc, char *argv[] )
{

	signal(SIGINT, sig_handler);
	signal(SIGTSTP, sig_handler);
	signal(SIGCHLD, child_handler);
	
	char  *user, hostname[256],d[100];
	char *cmd1[100] = {NULL};
	char *cmd2[100]={NULL};
	//memset(hostname, 0x00, sizeof(hostname));//initialising the hostname string
	gethostname(hostname, sizeof(hostname));//gets the host name
	user = (char *)getenv("USER");//gets the user

	char pwd1[1000],pwd[1000];
	int l;
	getcwd(pwd1,1000);
	getcwd(pwd,1000);
//	printf("pwd1 = %s\n",pwd1);
//	printf("pwd = %s\n",pwd1);
	if( user == NULL )
	{
		strcpy(user, "unknown");
	}
/*	struct rec{
		int flag;
		pid_t pid;
		char pro[100];
	};
	typedef struct rec proc;

	proc struc[100];
*/
	int s = 5;
	
	while(1)
	{
	/*	char a;
		scanf("%c",&a);*/
		int lk=strlen(pwd1);
		char til[100];
		int kl=0,k;
//		printf("pwd=%s pwd1=%s\n",pwd,pwd1);
		for(k=lk;k<100;k++){
			til[kl]=pwd[k];
			kl++;
		}
///		printf("cmd= %s\n",til);
		int i=0,ii=0;
		if(strstr(pwd,pwd1) == NULL){
		printf("<%s@%s:~%s>", user, hostname,pwd);
		}
		else{
		printf("<%s@%s:~%s>", user, hostname,til);
		}
		char cmdStr[256];
		char cmdstr[256];
		char cmdstr1[256];
		char hist1[100];
		char hist2[100];
		gets(cmdStr);
//		struc[j].pidp=getpid();
//		if(strstr(cmdStr,"|")==NULL){
//			pipefunc(cmdStr);
//			continue;
//		}
		strcpy(struc[j].pro,cmdStr);
		strcpy(cmdstr,cmdStr);
		strcpy(cmdstr1,cmdStr);
		strcpy(hist1,cmdStr);
		strcpy(hist2,cmdStr);
		int chati=0;
lol:		if(chati==1){
			i=0;
			strcpy(hist1,cmdstr);
		}
//		printf("here at lol cmdstr =:%s\n",cmdstr);
		if(strlen(cmdstr)!=0){
		cmd1[0]=strtok(cmdstr," ");
//		printf("cmd1[0] = %s\n",cmd1[0]);
		while((cmd1[++i]=strtok(NULL," "))!=NULL);
		int ss=0,tt=0,pp=0,qq=0,i1=0,i2=0,i3=0;
		char *before1[1000],*before2[1000],*after1[1000],*after2[1000],*c1[1000],*c2[1000],*e[1000],*f[1000];
	
		if(strstr(cmdStr,"<")!=NULL && strstr(cmdStr,">")==NULL)
		{
			cmd2[0]=strtok(cmdstr1,"<");
			while((cmd2[++i1]=strtok(NULL,"<"))!=NULL);
	//		before1[0]=cmd2[0];
	//		after1[0]=cmd2[1];	
//			printf("cmd2[0] = %s\n",cmd2[0]);
//			printf("cmd2[1] = %s\n",cmd2[1]);
			before1[0]=strtok(cmd2[0]," ");
			while((before1[++i2]=strtok(NULL," "))!=NULL);
			after1[0]=strtok(cmd2[1]," ");
			while((after1[++i3]=strtok(NULL," "))!=NULL);
			funl(before1,after1);
			continue;

		}
	
		if(strstr(cmdStr,">")!=NULL && strstr(cmdStr,"<")==NULL)
		{

			cmd2[0]=strtok(cmdstr1,">");
			while((cmd2[++i1]=strtok(NULL,">"))!=NULL);
//			before2[0]=cmd2[0];
//			after2[0]=cmd2[1];
//			ii=0;
//			printf("cmd2[0] = %s\n",cmd2[0]);
//			printf("cmd2[1] = %s\n",cmd2[1]);
			before2[0]=strtok(cmd2[0]," ");
			while((before2[++i2]=strtok(NULL," "))!=NULL);	
			after2[0]=strtok(cmd2[1]," ");
			while((after2[++i3]=strtok(NULL," "))!=NULL);
			fung(before2,after2);
			continue;
		}
		else if(strstr(cmdStr,">")!=NULL && strstr(cmdStr,"<")!=NULL)
		{
			i1=0;	
			cmd2[0]=strtok(cmdstr1,"<");
			while((cmd2[++i1]=strtok(NULL,"<"))!=NULL);
			
			i1=0;
			c1[0]=strtok(cmd2[0]," ");
			while((c1[++i1]=strtok(NULL," "))!=NULL);
			i1=0;
			c2[0]=strtok(cmd2[1],">");
			while((c2[++i1]=strtok(NULL,">"))!=NULL);
//			e[0]=c2[1]
			i1=0;
			f[0]=strtok(c2[0]," ");
			while((f[++i1]=strtok(NULL," "))!=NULL);
			i1=0;
			e[0]=strtok(c2[1]," ");
			while((e[++i1]=strtok(NULL," "))!=NULL);

			fungl(c1,f,e);
			continue;
		}


		
			
			

		int p=0;
		int t=0;
//		printf("1st :%s",cmd1[0]);
//		printf("2nd :%s",cmd1[1]);
		if(strcmp(cmd1[0],"quit")==0)
		{
			_exit(0);
		}
		if(strcmp(cmd1[0],"cd")==0)
		{
			if(strcmp(cmdStr,"cd")==0)
			{
		//		printf("entered to only cd\n");
//				int t=chdir();
				p=chdir(pwd1);
		//		printf("and original directory is %s\n",pwd1);
				getcwd(pwd,256);
		//		printf("current directory is %s\n",pwd);
				struc[j].pid=fork();
				if(struc[j].pid>0)
				{
					int st1;
					wait(&st1);
					struc[j].flag=1;
					j=j+1;	
					continue;
				}
				if(struc[j].pid==0)
				{
					_exit(0);
				}
			}
			else
			{
//				cmd1[0]=strtok(cmdstr," ");
//				cmd1[1]=strtok(NULL," ");
//				printf("%s %s\n",cmd1[0],cmd1[1]);
				p=chdir(cmd1[1]);
				getcwd(pwd,256);			
				struc[j].pid=fork();
				if(struc[j].pid>0)
				{
					int st2;
					wait(&st2);
					struc[j].flag=1;
					j=j+1;	
					continue;
				}
				if(struc[j].pid==0)
				{
					_exit(0);
				}
			}
		}
		
		else if(strcmp(cmd1[0],"pid")==0)
		{
			if (strcmp(cmdStr,"pid")==0)
			{
				printf("command name: ./a.out process id = %d\n",getpid());
				struc[j].pid=fork();
				if(struc[j].pid>0)
				{
					int st3;
					wait(&st3);
					struc[j].flag=1;
					j=j+1;	
					continue;
				}
				if(struc[j].pid==0)
				{
					_exit(0);
				}		
			}

			else if (strcmp(cmd1[1],"all")==0)
			{
//				struc[j].flag=1;
//				printf("entered pid all\n");
				for(t=0;t<j;t++)
				{
					
//					printf("for loop of entered pid all\n");
					printf("command name: %s ",struc[t].pro);
					printf("process id: %d",struc[t].pid);
					printf("\n");
				}
				
				struc[j].pid=fork();
				if(struc[j].pid>0)
				{
					int st4;
					wait(&st4);
					struc[j].flag=1;
					j=j+1;	
					continue;
				}
				if(struc[j].pid==0)
				{
					_exit(0);
				}
			
			}
			else if(strcmp(cmd1[1],"current")==0)
			{
				struc[j].flag=1;
//				j=j+1;
//				printf("entered pid current\n");
				for(t=0;t<j;t++)
				{
//					printf("for loop of entered pid current\n");
					if(struc[t].flag !=1)
					{
//						printf("if inside the for loop of entered pid current\n");
						printf("%s",struc[t].pro);
//						printf("entered till here\n");
						printf("%d",struc[t].pid);
						printf("\n");
					}
				}
				struc[j].pid=fork();
				if(struc[j].pid>0)
				{
					int st5;
					wait(&st5);
					struc[j].flag=1;
					j=j+1;	
					continue;
				}
				if(struc[j].pid==0)
				{
					_exit(0);
				}
//				j=j+1;
	
			}
			else
			{

				struc[j].pid=fork();
				if(struc[j].pid>0)
				{
					int stlat;
					wait(&stlat);
					struc[j].flag=1;
					j=j+1;	
					continue;
				}
				if(struc[j].pid==0)
				{
					_exit(0);
				}
			}
			

		}
		
		else if(strcmp(cmd1[0],"hist")==0)		
		{
			for(t=0;t<j;t++)
			{
				printf("%d. %s\n",t+1,struc[t].pro);
			}
				struc[j].pid=fork();
				if(struc[j].pid>0)
				{
					int st6;
					wait(&st6);
					struc[j].flag=1;
					j=j+1;	
					continue;
				}
				if(struc[j].pid==0)
				{
					_exit(0);
				}
		}
		else if(hist1[0]-'h'==0 && hist1[1]-'i'==0 && hist1[2]-'s'==0 && hist1[3]-'t'==0 && hist1[4]-'\n'!=0)
		{
			char b[10];
			int x=0;
			for(t=4;t<strlen(hist1);t++)
			{
			  b[x++]=hist1[t];
			}
			int y;
			y=atoi(b);
//			printf("number beside hist=%d\n",y);
			if(y<j)
			{
				for(t=j-y;t<j;t++)
				{
					printf("%d. %s\n",t-(j-y)+1,struc[t].pro);
				}
			}
			else
			{
				for(t=0;t<j;t++)
				{
					printf("%s\n",struc[t].pro);
				}
			}
					struc[j].pid=fork();
					if(struc[j].pid>0)
					{
						int st7;
						wait(&st7);
						struc[j].flag=1;
						j=j+1;	
						continue;
					}
					if(struc[j].pid==0)
					{
					_exit(0);
					}

		}



		else if(hist2[0]-'!'==0 && hist2[1]-'h'==0 && hist1[2]-'i'==0 && hist1[3]-'s'==0 && hist1[4]-'t'==0 && hist1[5]-'\n'!=0)
		{
			char c[10];
			int x1=0;
			for(t=5;t<strlen(hist2);t++)
			{
			  c[x1++]=hist2[t];
			}
			int y1;
			y1=atoi(c);
			
			
//			printf("number beside hist=%d\n",y);			
			//printf("%s\n",struc[y1-1].pro);			
			strcpy(cmdstr,struc[y1-1].pro);
//			printf("%s\n",cmdstr);
		//	pole=0;
			chati=1;
			int tp;
//			scanf("%d",&tp);
			goto lol;	
//			printf("%s\n",struc[y1-1].pro);
				
		/*			struc[j].pid=fork();
					if(struc[j].pid>0)
					{
						int st8;
						wait(&st8);
						struc[j].flag=1;
						j=j+1;	
						continue;
					}
			//		if(struc[j].pid==0)
			//		{
			//			 execlp(struc[y1-1].pro,struc[y1-1].pro,NULL);		
			//		 	 _exit(0);
			//		}
			
			*/
		}
		else
		{
			struc[j].pid=fork();			
/*
			if(struc[j].pid==0)
			{
				execvp(*cmd1,cmd1);
				_exit(0);
			}
			else
			{
						int status;
						wait(&status);
						struc[j].flag=1;
						j=j+1;	
						continue;				
				
			}
*/			
			if(struc[j].pid>0)
			{
//				printf("entered cmd1[0]=%s\n",cmd1[0]);
//				printf("entered cmd1[1]=%s\n",cmd1[1]);
//				printf("entered\n");
//				if(cmd1[i-1]==NULL)
//					cmd1[i-1]="aaaaaaaaaabbbbbbbb";
//				if(strcmp(cmd1[i-1],"&") == 0)
				if(strstr(cmdStr,"&")!=NULL)	
				{
						printf("entered here\n");
//						cmd1[i-1]=NULL;
///						printf("entered else in parent with &\n");
						int status55;
						struc[j].flag=0;
			//			struc[j].flag=1;
						j=j+1;	
						continue;				
					
				}
				else
				{
//						printf("entered else in parent\n");
						int status66;
						wait(&status66);
						struc[j].flag=1;
						j=j+1;	
					continue;				
				}
			}
				if(struc[j].pid == 0)
				{
					if(strstr(cmdStr,"&")!=NULL)
					{
						cmd1[i-1]=NULL;	
					}
					execvp(*cmd1,cmd1);
					_exit(0);
				}
				else
				{
					printf("error\n");	
				}
			
		}
		}
	}
}
