#include  <fcntl.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <sys/types.h>
#include  <sys/wait.h>
#include  <sys/stat.h>
#include  <termios.h>
#include  <unistd.h>

#define READ 0
#define WRITE 1

int main(int argc, char* argv[], char **env)
{
	pid_t	pid1;
	pid_t	pid2;
	pid_t	pid3;
	int fd[2];
	int fd_2[2];
	char	***comands = malloc(sizeof(char **) * 3);
	char	*comands_1[3] = {"ls", "-la", NULL};
	char	*comands_2[3] = {"grep", "obj", NULL};
	char	*comands_3[3] = {"wc", "-l", NULL};
	comands[0] = comands_1;
	comands[1] = comands_2;
	comands[2] = comands_3;

	pipe(fd); // fd[0] = fd[1]
	pipe(fd_2); //fd_2[0] = fd_2[1]
	// READ | WRITE
	pid1 = fork();
	if(pid1 == 0)
	{
		dup2(fd[WRITE], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		execve("/bin/ls", comands[0], env);
	}

	pid2 = fork();
	if(pid2 == 0)
	{
		dup2(fd[READ], STDIN_FILENO);
		dup2(fd_2[WRITE], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve("/usr/bin/grep", comands[1], env);
	}
	close(fd[1]);
	close(fd[0]);
	wait(&pid1);
	wait(&pid2);

	pid3 = fork();
	if(pid3 == 0)
	{
		dup2(fd_2[READ], STDIN_FILENO);
		wait(&pid1);
		close(fd_2[0]);
		close(fd_2[1]);
		execve("/bin/wc", comands[2], env);
	}
	
	close(fd_2[1]);
	close(fd_2[0]);
	wait(&pid3);
}
