/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_left.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:33:27 by rteles            #+#    #+#             */
/*   Updated: 2022/10/07 23:41:42 by rteles           ###   ########.fr       */
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
	t_command	*pipe_or_and;

	c->fd[1] = open(c->command[1], O_RDWR, 0777);
	if (c->fd[1] < 0)
	{
		printf("%s: No such file or directory or ", c->command[1]);
		printf("Permission denied\n");
		c->exit_status = 1;
		close(c->fd[1]);
		pipe_or_and = next_d_pipe_or_and(c);
		if (pipe_or_and)
			pipe_or_and->execute(pipe_or_and, STDIN_FILENO);
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
		printf("syntax error near unexpected token <\n");
		c->exit_status = 2;
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
	c->choice = 11;
	return (c);
}
