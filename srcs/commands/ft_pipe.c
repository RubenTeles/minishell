/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:06:35 by rteles            #+#    #+#             */
/*   Updated: 2022/09/15 22:52:10 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define READ 0
#define WRITE 1

static void	pipe_execute(t_command *c, int in)
{
	c->pid = fork();
	if(c->pid == 0)
	{
		dup2(in, STDIN_FILENO);
		if (c->next != NULL)
			dup2(c->fd[1], STDOUT_FILENO);
		close(in);
		close(c->fd[1]);
		execve(c->path, c->command, (terminal())->env_m);
	}
	if (in != STDIN_FILENO)
		close(in);
	close(c->fd[1]);
	if (c->next != NULL)
		c->next->execute(c->next, c->fd[0]);
}

void	*ft_pipe(t_command *c)
{	
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->path = path_command(c->command[0]);
	c->execute = pipe_execute;
}
