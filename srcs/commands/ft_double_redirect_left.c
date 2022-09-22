/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_redirect_left.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:34:08 by rteles            #+#    #+#             */
/*   Updated: 2022/09/22 17:47:31 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int double_left_redirect(t_command *c)
{
	c->fd[1] = dup(STDIN_FILENO);
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

static void	double_redirect_left_execute(t_command *c, int in)
{
	/*char	*str;

	if (!c->command[1])
	{
		printf("syntax error near unexpected token `newline'\n");
		return ;
	}
	str = ft_str_file(in);
	if (in != STDIN_FILENO)
		close(in);
	c->fd[1] = open(c->command[1], O_RDWR|O_CREAT|O_APPEND, 0777);
	write(c->fd[1], str, (string())->len(str));
	close(c->fd[1]);
	free(str);
	if (c->next != NULL)
		c->next->execute(c->next, c->fd[0]);*/
}

void	*ft_double_redirect_left(t_command *c)
{
	/*if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = double_redirect_left_execute;*/
}
