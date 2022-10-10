/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_redirect_right.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:33:46 by rteles            #+#    #+#             */
/*   Updated: 2022/10/10 22:13:12 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_permission_denied(t_command *c, int in)
{
	t_command	*pipe_or_and;

	(void)in;
	printf("%s: Permission denied\n", c->command[1]);
	c->exit_status = 1;
	pipe_or_and = next_d_pipe_or_and(c);
	if (pipe_or_and)
		pipe_or_and->execute(pipe_or_and, STDIN_FILENO);
}

static void	double_redirect_right_execute_2(t_command *c, int in)
{
	char	*str;

	str = NULL;
	str = ft_str_file(in);
	if (in != STDIN_FILENO)
		close(in);
	c->fd[1] = open(c->command[1], O_RDWR | O_CREAT | O_APPEND, 0777);
	if (c->fd[1] == -1)
	{
		ft_permission_denied(c, in);
		if (str)
			free(str);
		return ;
	}
	else
	{
		write(c->fd[1], str, (string())->len(str));
		write(c->fd[1], "", 1);
		close(c->fd[1]);
	}
	if (str)
		free(str);
	execute(c, 1);
}

static void	double_redirect_right_execute(t_command *c, int in)
{
	if (!c->command[1])
	{
		printf("syntax error near unexpected token >>\n");
		c->exit_status = 2;
		return ;
	}
	if (c->next != NULL && is_redirect_left(c->next->command[0]) > 0)
		in = management_input_execute(c->next);
	if (in == -1)
		return ;
	if (c->next && is_redirect_right(c->next->command[0]) > 0)
	{
		c->fd[1] = open(c->command[1], O_RDWR | O_CREAT, 0777);
		close(c->fd[1]);
		if (c->fd[1] == -1)
		{
			ft_permission_denied(c, in);
			return ;
		}
		c->next->execute(c->next, in);
		return ;
	}
	double_redirect_right_execute_2(c, in);
}

t_command	*ft_double_redirect_right(t_command *c)
{
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = double_redirect_right_execute;
	c->choice = 8;
	return (c);
}
