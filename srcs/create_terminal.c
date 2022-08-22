/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_terminal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:37:10 by rteles            #+#    #+#             */
/*   Updated: 2022/08/23 00:17:18 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* Dá valores ao env_m, export, e ao env_count usando o env do main*/
static void	create_env(char **env)
{
	int		i;
	int		aux;
	char	*path;
	
	path = 0;
	i = -1;
	while (env[++i])
	{
		if (!terminal()->path)
			path = string()->n_str(env[i], "PATH=", 6);
		if (path && !terminal()->path)
			terminal()->path = string()->split(path, ':');
	}
	terminal()->env_count = i;
	terminal()->env_m = malloc(sizeof(char *) * i + 1);
	terminal()->export = malloc(sizeof(char *) * i + 1);
	i = -1;
	while (++i < terminal()->env_count)
	{
		aux = ft_strlen(env[i]);
		terminal()->env_m[i] = malloc(sizeof(char) * aux + 1);
		ft_strlcpy(terminal()->env_m[i], env[i], aux + 1);
		terminal()->export[i] = string()->join("export ", env[i]);
	}
}

static void	__destroy(void)
{
	int	i;

	i = -1;
	while (++i < terminal()->env_count)
	{
		free(terminal()->env_m[i]);
		free(terminal()->export[i]);
	}
	free(terminal()->export);
	free(terminal()->env_m);
}

void new_terminal(char *title, char **env)
{
	terminal()->title = title;
	terminal()->env_count = 0;
	terminal()->env_m = 0;
	terminal()->export = 0;
	terminal()->path = 0;
	terminal()->count_env = __count_env;
	terminal()->variable_env = variable_env;
	terminal()->execute = ft_execute;
	terminal()->destroy = __destroy;
	create_env(env);
}

t_terminal *terminal()
{
	static t_terminal t;

	return (&t);
}
