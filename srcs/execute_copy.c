#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <termios.h>
#include <unistd.h>

typedef struct s_command 			t_command;

struct s_command {
	int		fd[2];
	char	***commands;
	char	**path;
	char	**env_m;
	int		c;
	int		max_c;
};

#define READ 0
#define WRITE 1

t_command *command(void)
{
	static t_command	c;

	return (&c);
}

int	create_3cmd(int *fd)
{
	int	i;
	int pid3;
	//int	fd_2[2];
	
	i = command()->c;
	//pipe(fd_2);
	pid3 = fork();
	if(pid3 == 0)
	{
		//if (i > 0)
		dup2(fd[READ], STDIN_FILENO);
		/*if (i )
		dup2(fd_2[WRITE], STDOUT_FILENO);*/
		close(fd[0]);
		close(fd[1]);
		execve(command()->path[i], command()->commands[i], command()->env_m);
		command()->c += 1;
	}
	
	close(fd[1]);
	close(fd[0]);
	wait(&pid3);
	command()->c += 1;
}

void	first_execute(int *fd)
{
	int		i;
	pid_t	pid1;
	pid_t	pid2;
	pid_t	pid3;
	int fd_2[2];

	i = command()->c;
	//printf("AQUI: %s \n", command()->path[i]);

	if (i == 0)
		pipe(fd); // fd[0] = fd[1]
	pipe(fd_2);
	if (i < command()->max_c)
	{
			printf("AQUI: %s \n", command()->path[i]);
		pid1 = fork();
		if(pid1 == 0)
		{
			if (i == 0)
				dup2(fd[WRITE], STDOUT_FILENO);
			else if (i > 0)
				dup2(fd[READ], STDIN_FILENO);
			close(fd[1]);
			close(fd[0]);
			execve(command()->path[i], command()->commands[i], command()->env_m);
		}
	}
	if (i + 1 < command()->max_c)
	{
		printf("AQUI: %s \n", command()->path[i + 1]);
		pid2 = fork();
		if(pid2 == 0)
		{
			dup2(fd[READ], STDIN_FILENO);
			if (i + 2 < command()->max_c)
				dup2(fd_2[WRITE], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			execve(command()->path[i + 1], command()->commands[i + 1], command()->env_m);
		}
	}
	close(fd[1]);
	close(fd[0]);
	wait(&pid1);
	wait(&pid2);
	command()->c += 2;
	if (command()->c < command()->max_c)
		first_execute(fd_2);
}

int main(int argc, char* argv[], char **env)
{
	int 	fd[2];
	char	*path[5] = {"/bin/ls",
	 "/usr/bin/grep",
	   "/bin/wc",
	  "/usr/bin/grep",
	     NULL};
	char	***comands = malloc(sizeof(char **) * 4);
	char	*comands_1[3] = {"ls", "-la", NULL};
	char	*comands_2[3] = {"grep", "5", NULL};
	char	*comands_3[3] = {"grep", "23", NULL};
	char	*comands_4[3] = {"wc", "-l", NULL};
	comands[0] = comands_1;
	comands[1] = comands_2;
	comands[2] = comands_4;
	comands[3] = comands_3;

	command()->commands = comands;
	command()->path = path;
	command()->env_m = env;
	command()->c = 0;
	command()->max_c = 3;
	first_execute(fd);
}

