/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:51:30 by ede-alme          #+#    #+#             */
/*   Updated: 2022/08/19 00:15:10 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_path_comands(t_rules *rules, char **env, int i)
{
	char	*path;
	
	while (env[++i])
	{
		if (path = ft_strnstr(env[i], "PATH=", 6))
		{
			rules->comands_path = ft_split(path, ':');
			return ;
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_rules rules;
	int		i;

	(void)argc;
	(void)argv;
	create_path_comands(&rules, env, -1);
	i = -1;
	while (rules.comands_path[++i])
		printf("%s \n", rules.comands_path[i]);
	return (0);
}
