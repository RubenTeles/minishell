/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:06:27 by rteles            #+#    #+#             */
/*   Updated: 2022/09/29 23:57:30 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	cd_execute_2(t_command *c, int in)
{
	char	buffer[1001];
	char	*home;

	if (!c->command[1])
		home = (terminal())->variable_env("HOME");
	else
		home = c->command[1];
	if (access(home, F_OK))
	{
		printf("cd: %s: No such file or directory\n", home);
		c->exit_status = 1;
		if (!c->command[1])
			free(home);
		return (-1);
	}
	execute(c, in, 2);
	(terminal())->update_var("OLDPWD", getcwd(buffer, 1001));
	chdir(home);
	(terminal())->update_var("PWD", getcwd(buffer, 1001));
	if (!c->command[1])
		free(home);
	execute(c, in, 1);
	return (0);
}

static void	cd_execute(t_command *c, int in)
{
	if (c->next && is_redirect_left(c->next->command[0]) > 0)
		in = management_input_execute(c->next);
	if (in == -1)
		return ;
	if (c->count_cmd > 2)
	{
		printf("cd: too many arguments\n");
		c->exit_status = 1;
		return ;
	}
	if (cd_execute_2(c, in) == -1)
		return ;
}

t_command	*ft_cd(t_command *c)
{
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = cd_execute;
	c->choice = 1;
	return (c);
}
