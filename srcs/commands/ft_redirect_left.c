/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_left.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:33:27 by rteles            #+#    #+#             */
/*   Updated: 2022/09/19 23:30:03 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int left_redirect(t_command *c)
{
	c->fd[1] = open(c->command[1], O_RDWR, 0777);
	if (c->fd[1] < 0)
	{
		printf("%s: No such file or directory\n", c->command[1]);
		close(c->fd[1]);
		return (-1);
	}
	c->fd[0] = c->fd[1];
	if (c->next && is_redirect_left(c->next->command[0]))
		c->fd[0] = left_redirect(c->next);
	return (c->fd[0]);
}

static void	redirect_left_execute(t_command *c, int in)
{
//	char	*str;
//	int		i;
//
//	
//	//dup2(in, c->fd[1]);
//	dup2(c->fd[1], in);
//	c->fd[1] = open(c->command[1], O_RDWR, 0777);
//	if (c->fd[1] < 0)
//	{
//	    printf("%s: No such file or directory\n", c->command[1]);
//		close(c->fd[1]);
//		return ;
//	}
//	str = ft_str_file(c->fd[1]);
//	i = -1;
//	
//	/*while (str[++i])
//		write(in, &str[i], 1);*/
//	
//	/*dup2(in, c->fd[1]);*/
//	close(c->fd[1]);
//	/*if (c->next != NULL)
//		c->next->execute(c->prev, c->fd[0]);*/
}

void	*ft_redirect_left(t_command *c)
{
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = redirect_left_execute;
}
