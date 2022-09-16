/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:49:00 by rteles            #+#    #+#             */
/*   Updated: 2022/09/16 14:03:34 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	exit_execute(t_command *c, int in)
{
	if (c)
	{
		dup2(in, STDIN_FILENO);
		if (c->next != NULL)
			dup2(c->fd[1], STDOUT_FILENO);
		close(in);
		close(c->fd[1]);
	}
	write(STDOUT_FILENO, "exit\n", 5);
	if (c && c->next != NULL)
		c->next->execute(c->next, c->fd[0]);
	else
	{
		terminal()->destroy->all();
		exit(0);
	}
}

void	*ft_exit(t_command *c)
{
	if (!c)
		exit_execute(c, STDIN_FILENO);
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = exit_execute;
}
