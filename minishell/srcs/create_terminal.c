/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_terminal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:37:10 by rteles            #+#    #+#             */
/*   Updated: 2022/08/19 21:09:24 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	create_env(char **env)
{
	int		i;
	int		aux;
	char	*path;
	
	path = 0;
	i = -1;
	while (env[++i])
	{
		if (!terminal()->path)
			path = ft_strnstr(env[i], "PATH=", 6);
		if (path && !terminal()->path)
			terminal()->path = ft_split(path, ':');
	}
	terminal()->env_n = i;
	terminal()->env_m = malloc(sizeof(char *) * i + 1);
	terminal()->export = malloc(sizeof(char *) * i + 1);
	i = -1;
	while (++i < terminal()->env_n)
	{
		aux = ft_strlen(env[i]);
		terminal()->env_m[i] = malloc(sizeof(char) * aux + 1);
		terminal()->export[i] = malloc(sizeof(char) * aux + 1);
		ft_strlcpy(terminal()->env_m[i], env[i], aux + 1);
		ft_strlcpy(terminal()->export[i], env[i], aux + 1);
	}
}

static void	__destroy(void)
{
	int	i;

	i = -1;
	while (++i < terminal()->env_n)
	{
		printf("%s \n", terminal()->env_m[i]);
		free(terminal()->env_m[i]);
		free(terminal()->export[i]);
	}
	free(terminal()->export);
	free(terminal()->env_m);
}

void    new_terminal(char *title, char **env)
{
    terminal()->title = title;
	terminal()->env_n = 0;
	terminal()->path = 0;
	terminal()->destroy = __destroy;
	create_env(env);
}

t_terminal *terminal()
{
	static t_terminal t;

	return (&t);
}
