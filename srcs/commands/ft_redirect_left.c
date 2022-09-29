/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_left.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:33:27 by rteles            #+#    #+#             */
/*   Updated: 2022/09/29 00:47:30 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	management_left_redirect(t_command *c)
{
	if (is_redirect_left(c->command[0]) == 1)
		return (left_redirect(c));
	else
		return (double_left_redirect(c, 0, 0, 0));
}

int	left_redirect(t_command *c)
{
	c->fd[1] = open(c->command[1], O_RDWR, 0777);
	if (c->fd[1] < 0)
	{
		printf("%s: No such file or directory or ", c->command[1]);
		printf("Permission denied\n");
		(terminal())->last_exit = 1;
		close(c->fd[1]);
		return (-1);
	}
	c->fd[0] = c->fd[1];
	if (c->next && is_redirect_left(c->next->command[0]))
		c->fd[0] = management_left_redirect(c->next);
	return (c->fd[0]);
}

static void	redirect_left_execute(t_command *c, int in)
{
	if (!c->command[1])
	{
		printf("syntax error near unexpected token\n");
		(terminal())->last_exit = 2;
		return ;
	}
	in = management_input_execute(c);
	if (in == -1)
		return ;
	if (c->next != NULL)
		c->next->execute(c->next, in);
}

t_command	*ft_redirect_left(t_command *c)
{
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = redirect_left_execute;
	return (c);
}
