/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:06:35 by rteles            #+#    #+#             */
/*   Updated: 2022/09/12 19:33:36 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define READ 0
#define WRITE 1

static void	execute(t_command *c, int in)
{
	//printf("pipe\n");
	c->pid = fork();
	if(c->pid == 0)
	{
		dup2(in, STDIN_FILENO);
		if (c->next != NULL)
			dup2(c->fd[1], STDOUT_FILENO);
		close(in);
		close(c->fd[1]);
		execve(c->path, c->command, terminal()->env_m);
	}
	if (in != STDIN_FILENO)
		close(in);
	close(c->fd[1]);
	if (c->next != NULL)
		c->next->execute(c->next, c->fd[0]);
}

t_command *new_command(char	**command)
{
	t_command	*c;

	c = malloc(sizeof(t_command));
	if (!c)
		return (NULL);
	c->command = command;
	c->path = path_command(command[0]);
	c->next = NULL;
	c->execute = execute;
	pipe(c->fd);
	return (c);
}

t_command	*ft_pipe(char **input)
{
	return (new_command(input));
}

void	ft_pipex(char ***comands)
{
	(void)comands;
	int			i;
	int			max_i;
	t_command 	*command;
	t_command 	*aux;
	char	***input = malloc(sizeof(char **) * 4);
	char	*input_1[3] = {"ls", "-la", NULL};
	char	*input_2[3] = {"grep", "1", NULL};
	char	*input_3[3] = {"grep", "a.out", NULL};
	char	*input_4[3] = {"wc", "-l", NULL};

	input[0] = input_1;
	input[1] = input_2;
	input[2] = input_3;
	input[3] = input_4;
	max_i = 4;
	i = -1;
	while (++i < max_i)
	{
		aux = new_command(input[i]);
		if (terminal()->start == NULL)
			terminal()->start = aux;
		else
			command->next = aux;
		command = aux;
	}
	terminal()->start->execute(terminal()->start, STDIN_FILENO);
	aux = terminal()->start;
	while (aux)
	{
		wait(&aux->pid);
		aux = aux->next;
	}
	//destroy commands
}
