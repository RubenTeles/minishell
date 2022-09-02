/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:51:30 by ede-alme          #+#    #+#             */
/*   Updated: 2022/08/23 20:19:38 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <signal.h>

/* Falta tirar o ^\   Para tirar é so meter uma flag no make*/ 
static void	action(int sig)
{
	if (sig == SIGINT)
	{
		//Falta Tirar o ^C
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	if (sig == SIGQUIT) 
		return ;
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	*var;
	char	*var2;
	int		i;

	(void)argc;
	(void)argv;

	signal(SIGINT, action);  //Ctrl + C
	signal(SIGHUP, action); //Ctrl + '\'
	//Ctrl + 'D' - é quando a line for nula
	new_terminal("\033[0;36mThe Best: \033[0;37m", env);
	while (1)
	{
		line = readline(terminal()->title);
		if (line != NULL && !string()->compare_n(line, "", 1))
			add_history(line);
		//printf("%s\n", line);
		ft_choise(line);
		//var = path_command(line);
		//terminal()->execute(var);
		//printf("%s \n", var);
		//free(var);
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
