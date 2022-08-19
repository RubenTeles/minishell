/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_terminal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:37:10 by rteles            #+#    #+#             */
/*   Updated: 2022/08/19 18:53:40 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	create_env(char **env)
{
	int		i;
	char	*path;
	
	i = -1;
	while (env[++i])
	{
		if (path = ft_strnstr(env[i], "PATH=", 6))
			terminal()->path = ft_split(path, ':');
	}
	terminal()->env_n = i;
	printf("%s\n", terminal()->path[5]);
	//terminal()->env_m = malloc(sizeof(char *) * i);
	//terminal()->export = malloc(sizeof(char *) * i);
}

static void	__destroy(void)
{
	int	i;

	i = -1;
}

void    new_terminal(char *title, char **env)
{
    terminal()->title = title;
	terminal()->destroy = __destroy;
	create_env(env);
}

t_terminal *terminal()
{
	static t_terminal t;

	return (&t);
}
