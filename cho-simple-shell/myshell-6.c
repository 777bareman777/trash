/* myshell.c shell program 777bareman777@gmail.com */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#define BUFSIZE 4098

void cmd_help()
{
	printf("/**************Simple Shell*****************\\\n");
	printf("You can use is just as the conventional shell\n\n");
	printf("Some examples of the built-in commands\n");
	printf("cd\t\t: change directroy\n");
	printf("exit\t\t: exit this shell\n");
	printf("quit\t\t: quit this shell\n");
	printf("help\t\t: show this help\n");
	printf("?\t\t: show this help\n");
	printf("/*******************************************\\\n");
}

int tokenize(char *buf,const char *delims, char *tokens[],int maxTokens)
{
	int token_count=0;
	char *token;

	token=strtok(buf,delims);
	while(token!=NULL && token_count < maxTokens)
	{
		tokens[token_count++]=token;
		token=strtok(NULL,delims);
	}
	tokens[token_count]=(char *)0;

	return token_count;
}

bool run (char *line)
{
	pid_t pid;

	int token_count;
	char *tokens[BUFSIZE];
	const char *delims=" \t\n";

	bool check_background=false;
	bool check_redirection_stdout=false;
	bool check_redirection_stdin=false;
	bool check_pipe=false;

	int check_background_index;
	int check_redirection_stdout_index;
	int check_redirection_stdin_index;
	int check_pipe_index;
	int i;

	token_count=tokenize(line,delims,tokens,sizeof(tokens)/sizeof(char *));
	
	// handling internal command such as cd, stty and exit
	if(strcmp(tokens[0],"help")==0 || strcmp(tokens[0],"?")==0)
	{	
		cmd_help();
		return true;
	}
	else if(strcmp(tokens[0],"quit")==0 || strcmp(tokens[0],"exit")==0)
	{
		return false;
	}
	else if(strcmp(tokens[0],"cd")==0)
	{
		if(chdir(tokens[1])<0)
		{
			printf("change directory error");
			return true;
		}
	}
	

	// handling redirection, pipe and background processing


	// check background processing
	for(i=0;i<token_count;i++)
	{
		if(strcmp(tokens[i],"&")==0)
		{
			check_background_index=i;
			check_background=true;
			break;
		}

	}

	// check redirection processing
	for(i=0;i<token_count;i++)
	{
		if(strcmp(tokens[i],">")==0)
		{
			check_redirection_stdout_index=i;
			check_redirection_stdout=true;
			break;
		}
	}

	for(i=0;i<token_count;i++)
	{
		if(strcmp(tokens[i],"<")==0)
		{
			check_redirection_stdin_index=i;
			check_redirection_stdin=true;
			break;
		}
	}

	// check pipe processing
	for(i=0;i<token_count;i++)
	{
		if(strcmp(tokens[i],"|")==0)
		{
			check_pipe_index=i;
			check_pipe=true;
			break;
		}
	}


	// normal and pipe and redirection and background processing
	pid=fork();
	if(pid<0)
	{
		printf("fork error\n");
		return true;
	}
	else if(pid == 0 )
	{
		if(check_background)
			tokens[check_background_index]=(char *)0;
		
		// pipe "|" + redirection ">"  processing
		if(check_redirection_stdout==true && check_pipe==true)
		{
			int pipefd1[2];
			int fd;
			pipe(pipefd1);

			pid=fork();
			if(pid<0)
			{
				printf("fork error\n");
				return false;
			}
			if(pid==0)
			{
				close(pipefd1[0]);
				close(STDOUT_FILENO);
				dup2(pipefd1[1],STDOUT_FILENO);
				tokens[check_pipe_index]=(char *)0;
				execvp(tokens[0],tokens);
				return false;
			}
			else
			{
				int fd;

				wait();
				close(pipefd1[1]);
				close(STDIN_FILENO);
				dup2(pipefd1[0],STDIN_FILENO);
				
				fd=open(tokens[check_redirection_stdout_index+1],O_WRONLY|O_CREAT|O_TRUNC,0644);
				if(fd<0)
				{
					printf("open error\n");
					return false;
				}
				tokens[check_redirection_stdout_index]=(char *)0;
				tokens[check_redirection_stdout_index+1]=(char *)0;
				close(STDOUT_FILENO);
				dup2(fd,STDOUT_FILENO);

				execvp(tokens[check_pipe_index+1],&tokens[check_pipe_index+1]);
				return false;
			}
		}	

		// redirection "<" + redirecton ">" processing

		if(check_redirection_stdin==true && check_redirection_stdout==true)
		{
			int fd1, fd2;
			close(STDIN_FILENO);
			fd1=open(tokens[check_redirection_stdin_index+1],O_RDONLY|O_NONBLOCK);
			if(fd1<0)
			{
				printf("open error\n");
				return false;
			}
			dup2(fd1,STDIN_FILENO);
			tokens[check_redirection_stdin_index]=(char *)0;

			close(STDOUT_FILENO);
			fd2=open(tokens[check_redirection_stdout_index+1],O_WRONLY|O_CREAT|O_TRUNC,0644);
			if(fd2<0)
			{
				printf("open error\n");
				return false;
			}
			dup2(fd2,STDOUT_FILENO);
			tokens[check_redirection_stdout_index]=(char *)0;
			tokens[check_redirection_stdout_index+1]=(char *)0;

			execvp(tokens[0],tokens);
			return false;
		}

		// redirection ">" processing
		if(check_redirection_stdout==true)
		{
			int fd;
			
			close(STDOUT_FILENO);
			fd=open(tokens[check_redirection_stdout_index+1],O_WRONLY|O_CREAT|O_TRUNC,0644);
			if(fd<0)
			{
				printf("open error\n");
				return false;
			}
			dup2(fd,STDOUT_FILENO);
			tokens[check_redirection_stdout_index]=(char *)0;

			execvp(tokens[0],tokens);
			return false;
		}
		// redirection "<" processing
		if(check_redirection_stdin==true)
		{
			int fd;

			close(STDIN_FILENO);
			fd=open(tokens[check_redirection_stdin_index+1],O_RDONLY|O_NONBLOCK);
			if(fd<0)
			{
				printf("open error\n");
				return false;
			}
			dup2(fd,STDIN_FILENO);
			tokens[check_redirection_stdin_index]=(char *)0;

			execvp(tokens[0],tokens);
			return false;
		}

		// pipe "|"  processing
		if(check_pipe==true)
		{
			int fd[2];
			pipe(fd);
			pid=fork();
			
			if(pid<0)
			{
				printf("fork error\n");
				return false;
			}
			if(pid==0)
			{
				close(fd[0]);
				close(STDOUT_FILENO);
				dup2(fd[1],STDOUT_FILENO);
				tokens[check_pipe_index]=(char *)0;
				execvp(tokens[0],tokens);
				return false;
			}
			else
			{
				wait();
				close(fd[1]);
				close(STDIN_FILENO);
				dup2(fd[0],STDIN_FILENO);
				execvp(tokens[check_pipe_index+1],&tokens[check_pipe_index+1]);
				return false;
			}
		}

		
		// normal processing
		execvp(tokens[0],tokens);
		return false;
	}
	else if(check_background==false)
	{
		wait();
	}
	
	return true;
}


int main(int argc, char *argv[])
{
	char line[BUFSIZE];

	system("clear");
	while(1)
	{
		memset(line,0,BUFSIZE);
		printf("[%s] $ ",get_current_dir_name());
		fgets(line,sizeof(line)-1,stdin);
		if(run(line)==false)
			break;
	}
	exit(0);
}
