#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#define MAX_CMD_ARG 10
#define MAX_CMD_GRP 10

const char* prompt = "Command> ";
int type = 0;
int grpcount = 0;
char* cmdgrps[MAX_CMD_GRP];
char* cmdvector[MAX_CMD_ARG];
char cmdline[BUFSIZ];
char* parseArr[50]={NULL,};
char* procgrps[50][50]={NULL,};
void makeparse(char* s, char* de);
void redirection(int index);
int splitGroup(void);
void fatal(char* str);
void execute_cmdline(char* cmd);
void execute_cmdgrp(char* cmdgrp);
void execute_pipe(int n);
int makelist(char* s, const char* delimiters, char** list, int MAX_LIST);
int changeDir(char* pathname);
int main(int argc, char** argv)
{
	while(1) {
		grpcount = 0;
		fputs(prompt, stdout);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		fgets(cmdline, BUFSIZ, stdin);
		if(strcmp(cmdline, "exit")==0)
			exit(0);
		cmdline[strlen(cmdline)-1] = '\0';
		execute_cmdline(cmdline);
		printf("\n");
	}
	return 0;
}
int splitGroup(void)
{
	int i=0, j=0, k=0, count = 1;
	while(parseArr[i] != NULL)
	{
		if(strcmp(parseArr[i], "|")==0)
		{
			count++;
			j++;
			k=0;
		}
		else
			procgrps[j][k++] = parseArr[i];
		i++;
	}
	return count;
}
void execute_pipe(int n)
{
	int p[2], status;
	pid_t  pid;
	int in = 0;
	int i = 0;
	while(i!=n)
	{
		pipe(p);
		if((pid=fork())==-1)
		{
			exit(EXIT_FAILURE);
		}
		else if(pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGSTOP, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			dup2(in, 0);
			if(i+1 != n)
				dup2(p[1], 1);
		redirection(i);
			char* ar[20] = {NULL, };
			int k = 0;
			while(1)
			{
				if(procgrps[i][k]==NULL||strcmp(procgrps[i][k],"<")==0||
						strcmp(procgrps[i][k],">")==0)
					break;
				ar[k] = procgrps[i][k];
				k++;
			}
				execvp(ar[0], ar);
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
			close(p[1]);
			in = p[0];
			i++;
		}
	}
	exit(0);
}
void makeparse(char* s, char* de)
{
	int i = 0;
	char* tmp = malloc(sizeof(char)*100);
	strcpy(tmp, s);
	char* snew = strtok(tmp, de);
	while(snew != NULL)
	{
		parseArr[i] = snew;
		snew = strtok(NULL, de);
		i++;
	}
	parseArr[i] = NULL;
}
void redirection(int index)
{
	char* redi = malloc(sizeof(char)*10);
	int fd, fd2;
	int pf = 0;
	
	for(int i = 1; i<10; i++)
	{
		if(procgrps[index][i]==NULL)
			break;
		if(strcmp(procgrps[index][i], ">") == 0 || strcmp(procgrps[index][i], "<") == 0)
		{strcpy(redi, procgrps[index][i]);
			pf = 1;
		}
		else
		{
			if(pf == 1)
			{			if(strcmp(redi, ">") == 0)
				{
					fd = open(procgrps[index][i], O_RDWR|O_CREAT, 0644);
					dup2(fd, 1);
					close(fd);
				}
				else 
				{
					if(strcmp(redi, "<")==0)
					{	fd2 = open(procgrps[index][i], O_RDWR|O_CREAT, 0644);
						dup2(fd2, 0);
						close(fd2);}
				}
				pf = 0;}
		}
	}
}
int changeDir(char* pathname)
{
	char* c = pathname + 2;
	if(*c=='\0')
	{
		const char* home = getenv("HOME");
		chdir(home);
		return 0;
	}
	c = pathname+3;
	int Result = chdir(c);
	if(Result == -1)
		printf("fail cd");
	return 0;

}
void fatal(char* str)
{
	perror(str);
	exit(1);
}

void execute_cmdline(char* cmdline)
{
	int count = 0;
	int i = 0;
	count = makelist(cmdline, ";", cmdgrps, MAX_CMD_GRP);

	if(count==-1)
		exit(0);
	for(i = 0; i < count; i++)
	{
		char* find = strstr(cmdgrps[i], "cd");
		if(find!=NULL)
		{changeDir(cmdgrps[i]);
			break;
		}
		switch(fork())
		{
			case -1: fatal("fork error");
			case 0:
						  execute_cmdgrp(cmdgrps[i]);
			default:
					  {	
						  wait(NULL);
						  if(type)
							  tcsetpgrp(STDIN_FILENO, getpgid(0));
						  fflush(stdout);		  
					  }
		}
	}
}
void execute_cmdgrp(char* cmdgrp)
{
	int i = 0;
	int count = 0;
	char ch = '&';
	char* find = strchr(cmdgrp, ch);
	if(find != NULL)
	{
		type = 0;
		char ad[100];
		memset(ad, '\0', 100);
		for(int i =0; cmdgrp[i] != '&'; i++)
			ad[i] = cmdgrp[i];
		pid_t pid;
		pid= fork();
		if(pid == -1)
			fatal("exec error");
		if(pid != 0)
			exit(0);
		if(strchr(ad, '|')!=NULL||strchr(ad, '>')!=NULL||strchr(ad, '<')!=NULL)
		{
			makeparse(ad, " ");
			int count = splitGroup();
			if(strchr(ad, '|')!=NULL)
			{
				execute_pipe(count);

			}
			else{
					char* ar[20] = {NULL, };
			int k = 0;
			while(1)
			{
				if(procgrps[0][k]==NULL||strcmp(procgrps[0][k],"<")==0||
						strcmp(procgrps[0][k],">")==0)
					break;
				ar[k] = procgrps[0][k];
				k++;
			}redirection(0);
			execvp(ar[0], ar);
			}
		}
		else		count = makelist(ad, " \t", cmdvector, MAX_CMD_ARG);	
	}
	if(strchr(cmdgrp, '|')!=NULL||strchr(cmdgrp, '>')!=NULL||strchr(cmdgrp, '<')!=NULL)
	{
		makeparse(cmdgrp, " ");
		int count = splitGroup();
		if(strchr(cmdgrp, '|')!=NULL)
		{
			execute_pipe(count);

		}
		else{
			redirection(0);
			char* ar[20] = {NULL, };
			int k = 0;
			while(1)
			{
				if(procgrps[0][k]==NULL||strcmp(procgrps[0][k],"<")==0||
						strcmp(procgrps[0][k],">")==0)
					break;
				ar[k] = procgrps[0][k];
				k++;
			}redirection(0);
			execvp(ar[0], ar);
		}

	}
	else 
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		type = 1;
		count = makelist(cmdgrp, " \t", cmdvector, MAX_CMD_ARG);
		tcsetpgrp(STDIN_FILENO, getpgid(0));


		if(count==-1)
			exit(0);
		execvp(cmdvector[0], cmdvector);
		fatal("exec error");
	}
}

int makelist(char* s, const char* delimiters, char** list, int MAX_LIST){

	int i = 0;
	int numtokens = 0;
	char* snew = NULL;
	char* Exit = "exit";
	if((s==NULL) || (delimiters == NULL)) return -1;

	snew = s + strspn(s, delimiters);
	if((*snew)==(*Exit))
		return -1;
	if((list[numtokens] = strtok(snew, delimiters))==NULL)
	{

		return numtokens;
	}
	numtokens = 1;

	while(1){
		if((list[numtokens] = strtok(NULL, delimiters))== NULL)
			break;
		if(numtokens == (MAX_LIST-1)) return -1;
		numtokens++;	
	}
	return numtokens;
}
