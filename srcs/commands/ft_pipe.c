/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:06:35 by rteles            #+#    #+#             */
/*   Updated: 2022/09/19 23:27:00 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define READ 0
#define WRITE 1

static void	pipe_execute(t_command *c, int in)
{
	if (c->next && is_redirect_left(c->next->command[0]) > 0)
		in = management_left_redirect(c->next);
	if (in < 0)
		return ;
	c->pid = fork();
	if(c->pid == 0)
	{
		execute(c, in, 0);
		execve(c->path, c->command, (terminal())->env_m);
	}
	execute(c, in, 1);
}

t_command	*ft_pipe(t_command *c)
{	
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->path = path_command(c->command[0]);
	c->execute = pipe_execute;
	return (c);
}
