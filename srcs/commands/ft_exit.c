/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:49:00 by rteles            #+#    #+#             */
/*   Updated: 2022/09/02 01:09:51 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	exit_execute(t_command *c, int in)
{
	dup2(in, STDIN_FILENO);
	if (c->next != NULL)
		dup2(c->fd[1], STDOUT_FILENO);
	close(in);
	close(c->fd[1]);
	write(STDOUT_FILENO, "exit\n", 5);
	if (c->next != NULL)
		c->next->execute(c->next, c->fd[0]);
    else
		exit(0);
}

static  t_command *new_command(char	**command)
{
	t_command	*c;

	c = malloc(sizeof(t_command));
	if (!c)
		return (NULL);
	c->command = command;
	c->path = NULL;
	c->next = NULL;
	c->execute = exit_execute;
	return (c);
}

void    ft_exit(char **input)
{
	(void)input;
	char	*input_1[2] = {"exit", NULL};
	t_command *command;

	command = new_command(input_1);
	command->execute(command, 0);
}