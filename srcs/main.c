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
#include <ft_input.h>
#include <signal.h>

/* Falta tirar o ^\   Para tirar é so meter uma flag no make*/ 
static void	action(int sig)
{
	if (sig == SIGINT)
	{
		//Falta Tirar o ^C
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
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
	char	***command;
	//t_data	data;
	(void)argc;
	(void)argv;

	signal(SIGINT, action);  //Ctrl + C
	signal(SIGHUP, action); //Ctrl + '\'
	new_terminal("\033[0;36mThe Best: \033[0;37m", env);
	while (1)
	{
		line = readline((terminal())->title);
		//get_comando(line, &data);
		if (line != NULL && !(string())->compare_n(line, "", 1))
			add_history(line);
		if (!line || (string())->compare_n(line, "exit", 5))
		{
			free(line);
			ft_exit(0);
		}
		ft_command_execute(0);
		free(line);
	}
	return (0);
}

/* ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’. space, tab, newline 
//Ctrl + 'D' - é quando a line for nula

*/