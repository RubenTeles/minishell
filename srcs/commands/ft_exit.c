/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:49:00 by rteles            #+#    #+#             */
/*   Updated: 2022/09/23 18:06:16 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	exit_execute(t_command *c, int in)
{
	if (c)
	{
		if (c->next != NULL && is_redirect_left(c->next->command[0]) > 0)
			in = management_input_execute(c->next);
		if (in == -1)
			return ;
		execute(c, in, 0);
	}
	write(STDOUT_FILENO, "exit\n", 5);
	if (c && c->next != NULL)
		execute(c, in, 1);
	else
	{
		terminal()->destroy->all();
		exit(0);
	}
}

t_command	*ft_exit(t_command *c)
{
	if (!c)
		exit_execute(c, STDIN_FILENO);
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = exit_execute;
	return (c);
}
