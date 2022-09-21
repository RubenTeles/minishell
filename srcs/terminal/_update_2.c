/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _update_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:17:52 by rteles            #+#    #+#             */
/*   Updated: 2022/09/21 22:29:43 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*path_title(void)
{
	char	*pwd;
	char	*home;
	char	*aux;
	int		c;

	aux = NULL;
	home = (terminal())->variable_env("HOME");
	pwd = (terminal())->variable_env("PWD");
	c = (string())->len(pwd) - (string())->len(home);
	if (c >= 0)
	{
		aux = (string())->sub_str(pwd, (string())->len(home),
				(string())->len(pwd));
		if ((string())->len(home) > 0)
		{
			free(pwd);
			pwd = (string())->join("~", aux);
		}
	}
	free(home);
	if (aux != NULL)
		free(aux);
	return (pwd);
}

void	__update_title(void)
{
	char	*title;
	char	*user;
	char	*pwd;
	char	*aux;

	(terminal())->destroy->title();
	user = (terminal())->variable_env("USER");
	aux = (string())->join("\033[1;36m", user);
	free(user);
	user = (string())->join(aux, "\033[0;37m:\033[1;35m");
	free(aux);
	pwd = path_title();
	aux = (string())->join(user, pwd);
	free(user);
	free(pwd);
	title = (string())->join(aux, "\033[0;37m$ ");
	free(aux);
	(terminal())->title = title;
}
