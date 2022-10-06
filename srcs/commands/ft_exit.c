/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:49:00 by rteles            #+#    #+#             */
/*   Updated: 2022/10/05 19:25:09 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	exit_execute_2(t_command *c, int *x)
{
	execute(c, 2);
	if (c->count_cmd > 2)
	{
		printf("exit: too many arguments\n");
		c->exit_status = 1;
	}
	if (c->count_cmd == 2)
	{
		if ((string())->only_this_chars(c->command[1], "-+0123456789"))
		{
			*x = (string())->str_in_int(c->command[1]);
			if (*x >= 256 || *x < 0)
				*x %= 256;
			c->exit_status = *x;
		}
		else
		{
			printf("exit: %s: numeric argument required\n", c->command[1]);
			c->exit_status = 2;
		}
	}
}

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
		exit_execute_2(c, &x);
	}
	if (c && c->next && !is_ppa(c->next))
		execute(c, 1);
	else if (!c || !c->prev || (c->prev && is_ppa(c->prev)))
	{
		write(STDOUT_FILENO, "exit\n", 6);
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
	c->execute = exit_execute;
	c->choice = 4;
	return (c);
}
