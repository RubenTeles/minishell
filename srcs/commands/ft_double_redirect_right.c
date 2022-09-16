/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_redirect_right.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:33:46 by rteles            #+#    #+#             */
/*   Updated: 2022/09/16 18:40:47 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	double_redirect_right_execute(t_command *c, int in)
{
	char	buffer[__INT_MAX__];
	char	*str;

	execute(c, in, 0);
	if (!c->command[1])
	{
		printf("syntax error near unexpected token `newline'\n");
		return ;
	}
	str = str_file(in);
	c->fd[1] = open(c->command[1], O_WRONLY | O_APPEND | O_CREAT );
	write(c->fd[1], str, (string())->len(str));
	execute(c, in, 1);
}

void	*ft_double_redirect_right(t_command *c)
{
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = double_redirect_right_execute;
}
