/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_redirect_left.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:34:08 by rteles            #+#    #+#             */
/*   Updated: 2022/09/19 19:34:15 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
