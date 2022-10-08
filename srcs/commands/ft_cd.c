/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:06:27 by rteles            #+#    #+#             */
/*   Updated: 2022/10/08 18:10:43 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	cd_erro(t_command *c, char *home, int v)
{
	if (access(home, ENOTDIR) && v == -1)
	{
		printf("cd: %s: No such directory\n", home);
		c->exit_status = 1;
	}
}

static int	cd_execute_3(t_command *c, char	*home)
{
	t_command	*aux;

	if (c->next)
	{
		aux = c->next;
		while ((is_redirect_left(aux->command[0]) > 0)
			|| (is_redirect_right(aux->command[0]) > 0))
		{
			if (aux->next)
				aux = aux->next;
			else
				break ;
		}
	}
	if (c->prev || (!(is_redirect_left(aux->command[0]) > 0)
			&& !(is_redirect_right(aux->command[0]) > 0)))
	{
		execute(c, 1);
		if (!c->command[1])
			free(home);
		return (1);
	}
	return (0);
}

static void	cd_execute_2(t_command *c)
{
	char		buffer[1001];
	char		*home;

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
	}
	if ((c->next && !is_ppa(c->next))
		|| (c->prev && !is_ppa(c->prev)))
		if (cd_execute_3(c, home) == 1)
			return ;
	execute(c, 2);
	(terminal())->update_var("OLDPWD", getcwd(buffer, 1001));
	cd_erro(c, home, chdir(home));
	(terminal())->update_var("PWD", getcwd(buffer, 1001));
	if (!c->command[1])
		free(home);
	execute(c, 1);
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
	}
	cd_execute_2(c);
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
