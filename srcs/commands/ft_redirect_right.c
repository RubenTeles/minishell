/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_right.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:33:17 by rteles            #+#    #+#             */
/*   Updated: 2022/09/17 21:59:11 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	redirect_right_execute(t_command *c, int in)
{
	char	*str;

	if (!c->command[1])
	{
		printf("syntax error near unexpected token `newline'\n");
		return ;
	}
	if (c->next && is_redirect(c->next->command[0]) > 0)
	{
		c->fd[1] = open(c->command[1], O_RDWR|O_CREAT, 0777);
		close(c->fd[1]);
		c->next->execute(c->next, in);
		return ;
	}
	str = ft_str_file(in);
	if (in != STDIN_FILENO)
		close(in);
	c->fd[1] = open(c->command[1], O_RDWR|O_CREAT, 0777);
	write(c->fd[1], str, (string())->len(str));
	close(c->fd[1]);
	free(str);
	if (c->next != NULL)
		c->next->execute(c->next, c->fd[0]);
}

void	*ft_redirect_right(t_command *c)
{
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = redirect_right_execute;
}
