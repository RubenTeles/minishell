/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_left.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:33:27 by rteles            #+#    #+#             */
/*   Updated: 2022/09/19 23:30:03 by rteles           ###   ########.fr       */
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

int left_redirect(t_command *c)
{
	c->fd[1] = open(c->command[1], O_RDWR, 0777);
	if (c->fd[1] < 0)
	{
		printf("%s: No such file or directory\n", c->command[1]);
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
	(void)c;
	(void)in;

	return ;
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
