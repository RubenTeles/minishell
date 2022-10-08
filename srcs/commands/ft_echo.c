/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:18:57 by rteles            #+#    #+#             */
/*   Updated: 2022/10/08 18:11:25 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	echo_execute(t_command *c, int in)
{
	int		i;

	i = 0;
	if (c->next != NULL && is_redirect_left(c->next->command[0]) > 0)
		in = management_input_execute(c->next);
	if (in == -1)
		return ;
	execute(c, 2);
	if ((string())->compare_n(c->command[1], "-n",
			(string())->len(c->command[1])))
		i++;
	while (c->command[++i])
	{
		write(c->fd[1], c->command[i], string()->len(c->command[i]));
		if (i < c->count_cmd - 1)
			write(c->fd[1], " ", 1);
	}
	if (!(string())->compare_n(c->command[1], "-n",
			(string())->len(c->command[1])))
		write(c->fd[1], "\n", 1);
	execute(c, 1);
}

t_command	*ft_echo(t_command *c)
{	
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = echo_execute;
	c->choice = 2;
	return (c);
}
