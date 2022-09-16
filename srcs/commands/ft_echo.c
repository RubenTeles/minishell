/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:18:57 by rteles            #+#    #+#             */
/*   Updated: 2022/09/16 14:15:17 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	echo_execute(t_command *c, int in)
{
	int		i;

	i = 0;
	if ((string())->compare_n(c->command[1], "-n",
			(string())->len(c->command[1])))
		i++;
	dup2(in, STDIN_FILENO);
	if (c->next != NULL)
		dup2(c->fd[1], STDOUT_FILENO);
	if (in != STDIN_FILENO)
		close(in);
	close(c->fd[1]);
	while (c->command[++i])
		write(STDOUT_FILENO, c->command[i], string()->len(c->command[i]) + 1);
	if (!(string())->compare_n(c->command[1], "-n",
			(string())->len(c->command[1])))
		write(STDOUT_FILENO, "\n", 1);
	if (in != STDIN_FILENO)
		close(in);
	close(c->fd[1]);
	if (c->next != NULL)
		c->next->execute(c->next, c->fd[0]);
}

void	*ft_echo(t_command *c)
{	
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = echo_execute;
}
