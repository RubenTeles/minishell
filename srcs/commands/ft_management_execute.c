/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_management_execute.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:41:40 by rteles            #+#    #+#             */
/*   Updated: 2022/09/23 21:37:24 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	management_input_execute(t_command *c)
{
	int	in;

	if (c && is_redirect_left(c->command[0]) > 0)
		in = management_left_redirect(c);
	if (in < 0)
		return (-1);
	return (in);
}

void	execute_in(t_command *c, int in)
{
	int	fd;

	if (in != STDIN_FILENO)
		close(in);
	close(c->fd[1]);
	fd = c->fd[0];
	if (c->next && is_redirect_left(c->next->command[0]) > 0)
		c = last_command_left_redirect(c->next);
	if (c->next)
		c->next->execute(c->next, c->fd[0]);
}

void	execute(t_command *c, int in, int option)
{
	t_command	*nextx;

	nextx = NULL;
	if (option == 0)
	{
		dup2(in, STDIN_FILENO);
		if (c->next && is_redirect_left(c->next->command[0]) > 0)
			nextx = last_command_left_redirect(c->next);
		else
			nextx = c;
		if (nextx->next)
			dup2(c->fd[1], STDOUT_FILENO);
		if (in != STDIN_FILENO)
			close(in);
		close(c->fd[1]);
	}
	else if (option == 1)
		execute_in(c, in);
	/*{
		if (in != STDIN_FILENO)
			close(in);
		close(c->fd[1]);
		fd = c->fd[0];
		if (c->next && is_redirect_left(c->next->command[0]) > 0)
			c = last_command_left_redirect(c->next);
		if (c->next)
			c->next->execute(c->next, c->fd[0]);
	}*/
}
