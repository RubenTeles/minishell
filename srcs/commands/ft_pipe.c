/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:06:35 by rteles            #+#    #+#             */
/*   Updated: 2022/09/30 19:30:10 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	pipe_execute(t_command *c, int in)
{
	/*if ((string())->compare_n(c->command[0], ".",
			(string())->len(c->command[0])))
	{
		printf(".: filename argument required\n");
		printf(".: usage: . filename [arguments]\n");
		execute(c, in, 1);
		return ;
	}*/
	if (c->next != NULL && is_redirect_left(c->next->command[0]) > 0)
		in = management_input_execute(c->next);
	if (in == -1)
		return ;
	if (!c->path)
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
		execute(c, in, 0);
		execve(c->path, c->command, (terminal())->env_m);
	}
	if (in != STDIN_FILENO)
		close(in);
	close(c->fd[1]);
	if (c->next && is_redirect_left(c->next->command[0]) > 0)
		c = last_command_left_redirect(c->next);
	if (c->next)
		c->next->execute(c->next, c->fd[0]);
}

t_command	*ft_pipe(t_command *c)
{	
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->path = path_command(c->command[0]);
	c->execute = pipe_execute;
	c->choice = 12;
	return (c);
}
