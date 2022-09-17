/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_left.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:33:27 by rteles            #+#    #+#             */
/*   Updated: 2022/09/17 23:27:09 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	redirect_left_execute(t_command *c, int in)
{
	c->fd[1] = open(c->command[1], O_RDWR, 0777);
	if (c->fd[1] < 0)
	{
	    printf("%s: No such file or directory\n", c->command[1]);
		close(c->fd[1]);
		return ;
	}
	close(c->fd[1]);
	dup2(in, c->fd[1]);
	if (c->next != NULL)
		c->next->execute(c->next, c->fd[0]);
}

void	*ft_redirect_left(t_command *c)
{
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = redirect_left_execute;
}
