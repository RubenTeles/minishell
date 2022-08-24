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

static void	action(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "CTRL + C!", 9);
		write(STDOUT_FILENO, "\n\0", 2);
		return ;
	}
	if (sig == SIGKILL)
		write(STDOUT_FILENO, "CTRL + D\n", 6);
		exit(0);
	if (sig == SIGQUIT){
		write(STDOUT_FILENO, "CTRL + \\n", 6);
		return ;
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	*var;
	char	*var2;
	int		i;

	(void)argc;
	(void)argv;
	signal(SIGINT, action); //Ctrl + C
	signal(SIGKILL, action); //Ctrl + 'D' - nao tenho a certeza
	signal(SIGQUIT, action); //Ctrl + '\'
	new_terminal("The Best: ", env);
	while (1)
	{
		line = readline(terminal()->title);
		add_history(line);
		printf("%s \n", line);
		var = path_command(line);
		terminal()->execute(var);
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
