/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:18:57 by rteles            #+#    #+#             */
/*   Updated: 2022/09/01 23:12:29 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	echo_execute(t_command *c, int in)
{
	int		i;

	i = 0;
	if (c->command[1] == "-n")
		i++;
	dup2(in, STDIN_FILENO);
	if (c->next != NULL)
		dup2(c->fd[1], STDOUT_FILENO);
	close(in);
	close(c->fd[1]);
	while (c->command[++i])
		write(STDOUT_FILENO, c->command[i], string()->len(c->command[i]) + 1);
	if (c->command[1] != "-n")
		write(STDOUT_FILENO, "\n", 1);
	close(in);
	close(c->fd[1]);
	if (c->next != NULL)
		c->next->execute(c->next, c->fd[0]);
}

static t_command *new_command(char	**command)
{
	t_command	*c;

	c = malloc(sizeof(t_command));
	if (!c)
		return (NULL);
	c->command = command;
	c->path = 0;
	c->next = NULL;
	c->execute = echo_execute;
	return (c);
}

void    ft_echo(char **input)
{
	(void)input;
	char	*input_1[5] = {"echo", "-n", "ahahaha ", "hamburguer", NULL};
	char	*input_2[4] = {"echo", "ahahaha ", "hamburguer", NULL};
	t_command *command;

	command = new_command(input_2);
	command->execute(command, 0);
}
