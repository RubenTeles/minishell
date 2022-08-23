/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:51:30 by ede-alme          #+#    #+#             */
/*   Updated: 2022/08/23 20:57:46 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ft_string.h>

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	*var;
	char	*var2;
	int		i;

	(void)argc;
	(void)argv;
	new_terminal("The Best: ", env);
	while (1)
	{
		line = readline(terminal()->title);
		var = path_command(line);
		terminal()->execute(var);
		
		
		printf("%s \n", var);
		free(var);
		//printf("%s \n", terminal()->variable_env(line));
	}
	
	/*while(terminal()->path[++i])
		printf("%s \n", terminal()->path[i]);*/


	//create_path_comands(&rules, env, -1);
	//execute(&rules, env);
	/*while (rules.comands_path[++i])
		printf("%s \n", rules.comands_path[i]);*/
	terminal()->destroy();
	return (0);
}
