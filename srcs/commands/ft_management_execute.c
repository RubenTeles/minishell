/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_management_execute.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:41:40 by rteles            #+#    #+#             */
/*   Updated: 2022/10/03 01:00:02 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	error_line(char	*str)
{
	printf("\033[1;33mwarning\033[0;37m: here-document at line ");
	printf("%zu delimited by end-of-file\n", (string())->len(str));
	return (1);
}

int	management_input_execute(t_command *c)
{
	int	in;

	if (c && is_redirect_left(c->command[0]) > 0)
		in = management_left_redirect(c);
	if (in < 0)
		return (-1);
	return (in);
}

void	execute_out(t_command *c)
{
	int	fd;

	if (c->fd[1] != STDOUT_FILENO)
		close(c->fd[1]);
	fd = c->fd[0];
	if (c->next && is_redirect_left(c->next->command[0]) > 0)
		c = last_command_left_redirect(c->next);
	if (c->next)
		c->next->execute(c->next, fd);
}

void	execute(t_command *c, int option)
{
	t_command	*nextx;

	nextx = NULL;
	if (option == 0)
	{
		if (c->next && is_redirect_left(c->next->command[0]) > 0)
			nextx = last_command_left_redirect(c->next);
		else
			nextx = c;
		if (nextx->next && !is_d_pipe_or_and(nextx->next))
			dup2(c->fd[1], STDOUT_FILENO);
		close(c->fd[1]);
	}
	else if (option == 1)
		execute_out(c);
	else if (option == 2)
	{
		if (c->next && is_redirect_left(c->next->command[0]) > 0)
			nextx = last_command_left_redirect(c->next);
		else
			nextx = c;
		if (!nextx->next || (nextx->next && (is_d_pipe_or_and(nextx->next))))
			c->fd[1] = STDOUT_FILENO;
	}
}
