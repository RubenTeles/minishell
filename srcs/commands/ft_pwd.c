/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:49:00 by rteles            #+#    #+#             */
/*   Updated: 2022/10/05 18:13:17 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	pwd_execute(t_command *c, int in)
{
	char	*pwd;
	char	buffer[1001];

	if (c->next != NULL && is_redirect_left(c->next->command[0]) > 0)
		in = management_input_execute(c->next);
	if (in == -1)
		return ;
	execute(c, 2);
	pwd = getcwd(buffer, 1001);
	write(c->fd[1], pwd, string()->len(pwd));
	write(c->fd[1], "\n", 1);
	execute(c, 1);
}

t_command	*ft_pwd(t_command *c)
{
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = pwd_execute;
	c->choice = 6;
	return (c);
}
