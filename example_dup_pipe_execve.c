#include  <fcntl.h>                              //
#include  <stdio.h>                              //
#include  <stdlib.h>                             //
#include  <string.h>                             //
#include  <sys/types.h>                          //
#include  <sys/wait.h>                           //
#include  <sys/stat.h>                           //
#include  <termios.h>                            //
#include  <unistd.h>                             //
                                                 //
#define INPUT_END 1                              // INPUT_END means where the pipe takes input
#define OUTPUT_END 0                             // OUTPUT_END means where the pipe produces output
                                                 //
int main(int argc, char* argv[], char **env)                 //
{                                                //
    pid_t pid1;                                  // [STDIN -> terminal_input, STDOUT -> terminal_output]                       (of the parent process)
    pid_t pid2;                                  //
    int fd[2];
	char	***comands = malloc(sizeof(char **) * 3);
	char	*comands_2[3] = {"wc", "-l", NULL};
	char	*comands_1[3] = {"ls", "-la", NULL};
	comands[0] = comands_1;
	comands[1] = comands_2;
	comands[2] = NULL;

	                                             //
    pipe(fd);                                    // [STDIN -> terminal_input, STDOUT -> terminal_output, fd[0] -> pipe_input, fd[1] -> pipe_output]
    pid1 = fork();                               //
                                                 //
    if(pid1==0)                                  //
    {                                            // I am going to be the wc process (i.e. taking input from the pipe)
        close(fd[1]);                    // [STDIN -> terminal_input, STDOUT -> terminal_output, fd[1] -> pipe_output] (of the WC process)
        dup2(fd[0], STDIN_FILENO);      // [STDIN -> pipe_output, STDOUT -> terminal_output, fd[1] -> pipe_output]    (of the WC process)
        close(fd[0]);      	         // [STDIN -> pipe_output, STDOUT -> terminal_output]                          (of the WC process)
        execve("/bin/wc", comands[1], env);      //
    }
                                                 //
    pid2=fork();                             //
                                             //
    if(pid2==0)                              //
    {                                        // I am going to be the ls process (i.e. producing output to the pipe)
        close(fd[0]);               // [STDIN -> terminal_input, STDOUT -> terminal_output, fd[0] -> pipe_input] (of the ls process)
        dup2(fd[1], STDOUT_FILENO);  // [STDIN -> terminal_input, STDOUT -> pipe_input, fd[0] -> pipe_input]      (of the ls process)
        close(fd[1]);                // [STDIN -> terminal_input, STDOUT -> pipe_input]                           (of the ls process)
    	execve("/bin/ls", comands[0], env);  //
    }                                        //
                                             //
    close(fd[0]);                   // [STDIN -> terminal_input, STDOUT -> terminal_output, fd[0] -> pipe_input] (of the parent process)
    close(fd[1]);                    // [STDIN -> terminal_input, STDOUT -> terminal_output]                      (of the parent process)
    wait(&pid1);                    // As the parent process - we wait for a process to die (-1) means I don't care which one - it could be either ls or wc
    wait(&pid2);                    // As the parent process - we wait for the another process to die.
                                                 // At this point we can safely assume both process are completed
                                             //
}
