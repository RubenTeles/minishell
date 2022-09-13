/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 22:41:55 by rteles            #+#    #+#             */
/*   Updated: 2022/09/14 00:03:24 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	unset_execute(t_command *c, int in)
{
	printf("unset\n");
	int	i;
	
	i = 0;
	if (c->count_cmd > 1)
	{
		while (c->command[++i])
			terminal()->delete_var(c->command[i]);
	}
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
	c->count_cmd = 0;
	if (command)
		while (command[c->count_cmd])
			c->count_cmd++;
	c->path = 0;
	c->next = NULL;
	c->execute = unset_execute;
	return (c);
}

t_command	*ft_unset(char **input)
{
	(void)input;
	char	*input_1[3] = {"unset", NULL};
	char	*input_2[3] = {"unset", "Ola", NULL};
	char	*input_3[4] = {"unset", "Ola", "Adeus", NULL};
	t_command *command;

	command = new_command(input_2);
	command->execute(command, 0);
/*
	command = new_command(input_1);
	command->execute(command, 0);*/
	return (command);
}
