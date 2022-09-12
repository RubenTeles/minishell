/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_terminal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:37:10 by rteles            #+#    #+#             */
/*   Updated: 2022/09/12 18:27:59 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* Dá valores ao env_m, export, e ao env_count usando o env do main*/
static void	create_path(void)
{
	int		i;
	char	*path;

	terminal()->destroy->path();
	path = terminal()->variable_env("PATH");
	if (string()->index_char(path, ':') > -1)
		terminal()->path = string()->split(path, ':');
}

void	__destroy_all(void)
{
	terminal()->destroy->env_l();
	terminal()->destroy->env_m();
	terminal()->destroy->path();
	free(terminal()->destroy);
}

void new_terminal(char *title, char **env)
{
	terminal()->title = title;
	terminal()->env_count = 0;
	terminal()->env_m = 0;
	terminal()->env_l = NULL;
	terminal()->path = 0;
	terminal()->create_path = create_path;
	terminal()->start = NULL;
	terminal()->count_env = __count_env;
	terminal()->variable_env = variable_env;
	terminal()->update_var = update_var;
	terminal()->execute = ft_command_execute;
	terminal()->index_var = index_var;
	__destroy();
	create_env_l(env);
	create_path();
}

t_terminal *terminal(void)
{
	static t_terminal	t;

	return (&t);
}
