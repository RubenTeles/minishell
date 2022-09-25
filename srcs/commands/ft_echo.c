/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:18:57 by rteles            #+#    #+#             */
/*   Updated: 2022/09/23 17:54:18 by rteles           ###   ########.fr       */
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
	execute(c, in, 0);
	if ((string())->compare_n(c->command[1], "-n",
			(string())->len(c->command[1])))
		i++;
	while (c->command[++i])
	{
		write(STDOUT_FILENO, c->command[i], string()->len(c->command[i]) + 1);
		if (i < c->count_cmd - 1)
			write(STDOUT_FILENO, " ", 1);
	}
	if (!(string())->compare_n(c->command[1], "-n",
			(string())->len(c->command[1])))
		write(STDOUT_FILENO, "\n", 1);
	execute(c, in, 1);
}

t_command	*ft_echo(t_command *c)
{	
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = echo_execute;
	return (c);
}
