/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:06:27 by rteles            #+#    #+#             */
/*   Updated: 2022/09/23 21:26:22 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	cd_execute(t_command *c, int in)
{
	char	buffer[100];
	char	*home;

	if (c->next && is_redirect_left(c->next->command[0]) > 0)
		in = management_input_execute(c->next);
	if (in == -1)
		return ;
	if (c->count_cmd > 2)
	{
		printf("cd: too many arguments\n");
		return ;
	}
	if (!c->command[1] && (terminal())->var_exist("HOME"))
		home = (terminal())->variable_env("HOME");
	if (access(c->command[1], F_OK) || access(home, F_OK))
	{
		printf("cd: %s: No such file or directory\n", c->command[1]);
		if (home)
			free(home);
		return ;
	}
	execute(c, in, 0);
	(terminal())->update_var("OLDPWD", getcwd(buffer, 100));
	if (!c->command[1])
		chdir(home);
	else
		chdir(c->command[1]);
	(terminal())->update_var("PWD", getcwd(buffer, 100));
	execute(c, in, 1);
}

t_command	*ft_cd(t_command *c)
{
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = cd_execute;
	return (c);
}
