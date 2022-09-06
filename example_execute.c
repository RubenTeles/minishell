#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <termios.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

void ft_pipex(char **env, int in) 
{
	pid_t	pid1;
	pid_t	pid2;
	pid_t	pid3;
	int fd[2];
	int fd_2[2];
	char	***comands = malloc(sizeof(char **) * 3);
	char	*comands_1[3] = {"ls", "-la", NULL};
	char	*comands_2[3] = {"grep", "a.out", NULL};
	char	*comands_3[3] = {"wc", "-l", NULL};
	char	*token[3] = {"|", "|", NULL};
	comands[0] = comands_1;
	comands[1] = comands_2;
	comands[2] = comands_3;

	printf("aqui\n");

	pipe(fd); // fd[0] = fd[1]
	pipe(fd_2); //fd_2[0] = fd_2[1]
	// READ | WRITE
	pid1 = fork();
	if(pid1 == 0)
	{
		dup2(in, STDIN_FILENO);
		dup2(fd[WRITE], STDOUT_FILENO);
		close(in);
		close(fd[1]);
		execve("/bin/ls", comands[0], env);
	}
	close(in);
	close(fd[1]);

	pid2 = fork();
	if(pid2 == 0)
	{
		dup2(fd[READ], STDIN_FILENO);
		dup2(fd_2[WRITE], STDOUT_FILENO);
		close(fd[READ]);
		close(fd_2[WRITE]);
		execve("/usr/bin/grep", comands[1], env);
	}
	close(fd[0]);
	close(fd_2[1]);

	pid3 = fork();
	if(pid3 == 0)
	{
		dup2(fd_2[READ], STDIN_FILENO);
		close(fd_2[0]);
		execve("/bin/wc", comands[2], env);
	}
	close(fd_2[0]);
	wait(&pid1);
	wait(&pid2);
	wait(&pid3);
}

int main(int argc, char* argv[], char **env)
{
	char	*line;
	int		command;

	command = 0;
	while(1)
	{
		if (command)
		{
			command = 0;
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		line = readline("ola: ");
		printf("%s line\n", line);
		if (line != NULL)
			add_history(line);
		if (!line && !command)
		{
			printf("line passou aqui\n");
			exit(0);
		}
		////printf("%s\n", line);
		if (line)
		{
			ft_pipex(env, 0);
			command = 1;
			free(line);
		}
	}
}
