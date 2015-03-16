#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <wait.h>

/*
void child_handler(int signum){
	int pid;
	pid = waitpid(WAIT_ANY, NULL, WNOHANG);
	if(pid != -1){
		printf("child Dead\n");
	}
	signal(SIGCHLD, child_handler);
	return;
}
*/




int main( int argc, char *argv[] )
{
	
	char  *user, hostname[256],pwd[1000],d[100];
	char *cmd1[100],*cmd2=NULL;
	//memset(hostname, 0x00, sizeof(hostname));//initialising the hostname string
	gethostname(hostname, sizeof(hostname));//gets the host name
	user = (char *)getenv("USER");//gets the user

	char pwd1[1000];
	getcwd(pwd1,1000);
	
	getcwd(pwd,1000);
//	printf("pwd1 = %s\n",pwd1);
//	printf("pwd = %s\n",pwd1);
	if( user == NULL )
	{
		strcpy(user, "unknown");
	}
	int j=0;
	struct rec{
		int flag;
		pid_t pid;
		char pro[100];
	};
	typedef struct rec proc;

	proc struc[100];
	int s = 5;
	
	while(1)
	{
	/*	char a;
		scanf("%c",&a);*/
		int i=0;
		printf("[%s@%s %s]", user, hostname,pwd);
		char cmdStr[256];
		char cmdstr[256];
		char hist1[100];
		char hist2[100];
		gets(cmdStr);
//		struc[j].pidp=getpid();
		strcpy(struc[j].pro,cmdStr);
		strcpy(cmdstr,cmdStr);
		strcpy(hist1,cmdStr);
		strcpy(hist2,cmdStr);
		cmd1[0]=strtok(cmdstr," ");

		while((cmd1[++i]=strtok(NULL," "))!=NULL);
		int p=0;
		int t=0;
//		printf("1st :%s",cmd1[0]);
//		printf("2nd :%s",cmd1[1]);
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
//						printf("for loop of entered pid current\n");
						printf("%s",struc[t].pro);
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
//			strcpy(cmd1,struc[y1].pro);
//			goto lol;	
//			printf("%s\n",struc[y1-1].pro);
				
					struc[j].pid=fork();
					if(struc[j].pid>0)
					{
						int st8;
						wait(&st8);
						struc[j].flag=1;
						j=j+1;	
						continue;
					}
					if(struc[j].pid==0)
					{
						 execlp(struc[y1-1].pro,struc[y1-1].pro,NULL);		
					 	 _exit(0);
					}
			
			
		}

		else
		{
			struc[j].pid=fork();
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
		/*	if(cmd1[1]=='&')
			{
				if(struc[j].pid>0)
				{
						int status;
						struc[j].flag=1;
						j=j+1;	
						continue;				
				}
			}
			else
			{
						int status;
						wait(&status);
						struc[j].flag=1;
						j=j+1;	
						continue;				

			}
			if(struc[j].pid==0)
			{
				execvp(*cmd1,cmd1);
				_exit(0);
			}
			else
			{
				printf("error\n");	
			}*/

		}

		


	}
}
