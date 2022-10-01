/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:06:35 by rteles            #+#    #+#             */
/*   Updated: 2022/09/30 20:48:53 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	pipe_execute_2(t_command *c, int in)
{
	if (!c->path && access(c->command[0], F_OK))
	{
		printf("Command '%s' not found\n", c->command[0]);
		c->exit_status = 127;
	}
	if (c->path)
		c->pid = fork();
	if (c->path && c->pid == 0)
	{
		dup2(in, STDIN_FILENO);
		if (in != STDIN_FILENO)
			close(in);
		execute(c, 0);
		execve(c->path, c->command, (terminal())->env_m);
	}
}

static void	pipe_execute(t_command *c, int in)
{
	int	fd;

	if ((string())->compare_n(c->command[0], ".",
			(string())->len(c->command[0])))
	{
		printf(".: filename argument required\n");
		printf(".: usage: . filename [arguments]\n");
		execute(c, 1);
		return ;
	}
	if (c->next != NULL && is_redirect_left(c->next->command[0]) > 0)
		in = management_input_execute(c->next);
	if (in == -1)
		return ;
	pipe_execute_2(c, in);
	if (in != STDIN_FILENO)
		close(in);
	close(c->fd[1]);
	fd = c->fd[0];
	if (c->next && is_redirect_left(c->next->command[0]) > 0)
		c = last_command_left_redirect(c->next);
	if (c->next)
		c->next->execute(c->next, fd);
}

t_command	*ft_pipe(t_command *c)
{	
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->path = path_command(c->command[0]);
	if (!c->path && !access(c->command[0], F_OK))
		c->path = (string())->duplicate(c->command[0]);
	c->execute = pipe_execute;
	c->choice = 12;
	return (c);
}
