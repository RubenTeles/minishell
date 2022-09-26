/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:49:00 by rteles            #+#    #+#             */
/*   Updated: 2022/09/26 22:17:33 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	pwd_execute(t_command *c, int in) //getcwd(buffer, 100)
{
	char	*pwd;
	char	buffer[1001];

	if (c->next != NULL && is_redirect_left(c->next->command[0]) > 0)
		in = management_input_execute(c->next);
	if (in == -1)
		return ;
	execute(c, in, 0);
	pwd = getcwd(buffer, 1001);
	write(STDOUT_FILENO, pwd, string()->len(pwd));
	write(STDOUT_FILENO, "\n", 1);
	execute(c, in, 1);
}

t_command	*ft_pwd(t_command *c)
{
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = pwd_execute;
	return (c);
}
