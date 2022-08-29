/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:18:57 by rteles            #+#    #+#             */
/*   Updated: 2022/08/29 22:48:01 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	echo_execute(t_command *c, int i)
{
	if (c->command[1] == "-n")
		i++;
	while (c->command[++i])
		printf("%s", c->command[i]);
	if (c->command[1] != "-n")
		printf("\n");
	rl_on_new_line();
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
/*
	command = new_command(input_1);
	command->execute(command, 0);*/
}
