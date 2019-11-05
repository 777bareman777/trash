/* myShell.c shell program */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

#define BUFSIZE 4098

void cmd_help();
bool internal_command(char *tokens[],int t_cnt);
int tokenize(char *buf,const char *delimiter,char *tokens[],int maxTokens);
bool run(char *line);
int redirection(char *tokens[],int *index);

int main(int argc, char *argv[])
{
	char *cwd;
	char line[BUFSIZE];

	system("clear");
	while(1)
	{
		memset(line,0,BUFSIZE);
		cwd=getcwd(NULL,BUFSIZE);
		printf("[%s] $ ",cwd);
		fgets(line,sizeof(line)-1,stdin);
		if(run(line)==false)
			break;
	}

	exit(0);
}

// 도움말
void help()
{
	printf("/**************Simple Shell*****************\\\n");
	printf("Some examples of the built-in commands\n");
	printf("cd\t\t: change directroy\n");
	printf("exit\t\t: exit this shell\n");
	printf("quit\t\t: quit this shell\n");
	printf("help\t\t: show this help\n");
	printf("/*******************************************\\\n");
}

// 내부 명령어
bool internal_command(char *tokens[], int t_cnt)
{
	if(t_cnt==0) return true;
	if(strcmp(tokens[0],"help")==0 || strcmp(tokens[0],"?")==0)
	{	
		help();
	}
	else if(strcmp(tokens[0],"quit")==0 || strcmp(tokens[0],"exit")==0)
	{
		return false;
	}
	else if(strcmp(tokens[0],"cd")==0)
	{
		if(chdir(tokens[1])<0)
		{
			printf("디렉토리 이동하기 실패\n");
		}
	}
	return true;
}

// 토큰 분리
int tokenize(char *buf,const char *delimiter,char *tokens[],int maxTokens)
{
	int t_cnt=0;
	char *token;

	token=strtok(buf,delimiter);
	while(token != NULL && t_cnt < maxTokens)
	{
		tokens[t_cnt++]=token;
		token=strtok(NULL,delimiter);
	}
	tokens[t_cnt]=(char*)0;

	return t_cnt;
}

// 리다이렉션
int redirection(char *tokens[],int *index)
{
	int i;
	for(i=0;tokens[i]!=NULL;i++){
		if( (strcmp(tokens[i],">")) == 0)
		{	*index=i;
			return true; // true -> ">"
		}
		if( (strcmp(tokens[i],"<")) == 0)
		{	
			*index=i;
			return false; // false -> "<"
		}
	}
	return -1; // 리다이렉션이 아님
}

// 실행
bool run(char *line)
{
	pid_t pid;
	int i;

	int background=0;

	int t_cnt;
	char *tokens[BUFSIZE];
	const char *delimiter=" \t\n";

	t_cnt=tokenize(line,delimiter,tokens,sizeof(tokens)/sizeof(char*));

	/*
	printf("line : %s\n",line);
	for(i=0;i<t_cnt;i++)
		printf("token : %s\n",tokens[i]);
	*/

	// 내부 명령어 체크
	if(!internal_command(tokens,t_cnt))
		return false;

	// 백그라운드 체크
	for(i=0;i<t_cnt;i++)
	{
		if(strcmp(tokens[i],"&")==0)
		{
			background=i;
			break;
		}
	}

	pid=fork();
	if(pid<0)
	{
		perror("포크 실패\n");
		return true;
	}
	else if(pid==0)
	{
		int fd,index;

		// 백그라운드 구현
		if(background != 0)
			tokens[background]=(char*)0;

		// 리다이렉션 구현
		fd=redirection(tokens,&index);
		// 표준 출력 리다이렉션 ">"
		if( fd == true)
		{
			fd=open(tokens[index+1],O_WRONLY|O_CREAT|O_TRUNC,0644);
			if(fd<0)
			{
				perror("파일 열기 실패\n");
				return false;
			}
			close(STDOUT_FILENO);
			dup2(fd,STDOUT_FILENO);
			tokens[index]=(char *)0;
		}
		// 표준 입력 리다이렉션 "<"
		else if( fd == false)
		{
			fd=open(tokens[index+1],O_RDONLY|O_NONBLOCK);
			if(fd<0)
			{
				perror("파일 열기 실패\n");
				return false;
			}
			close(STDIN_FILENO);
			dup2(fd,STDIN_FILENO);
			tokens[index]=(char*)0;
		}

		
		// 명령어 실행	
		execvp(tokens[0],tokens);
		return false;
	}
	else
	{
		if(background==0)
			wait(NULL);
	}

	return true;
}

