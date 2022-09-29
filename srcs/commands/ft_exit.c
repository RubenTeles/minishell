/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:49:00 by rteles            #+#    #+#             */
/*   Updated: 2022/09/30 00:06:37 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	exit_execute(t_command *c, int in)
{
	int	x;

	x = 0;
	if (c)
	{
		if (c->next != NULL && is_redirect_left(c->next->command[0]) > 0)
			in = management_input_execute(c->next);
		if (in == -1)
			return ;
		execute(c, in, 2);
		if (c->count_cmd > 2)
		{
			printf("cd: too many arguments\n");
			c->exit_status = 1;
		}
		if (c->count_cmd == 2)
		{
			if ((string())->only_this_chars(c->command[1], "0123456789"))
			{
				x = (string())->str_in_int(c->command[1]);
				c->exit_status = x;
			}
			else
			{
				printf("exit: %s: numeric argument required", c->command[1]);
				c->exit_status = 2;
			}
		}
	}
	write(STDOUT_FILENO, "exit\n", 5);
	if (c && c->next != NULL)
		execute(c, in, 1);
	else
	{
		terminal()->destroy->all();
		exit(x);
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
	c->choice = 4;
	return (c);
}
