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
#include <parse.h>

static void	action(int sig)
{
	if (sig == SIGINT)
	{
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
	int		i;
	int		u;
	t_data	data;

	(void)argc;
	(void)argv;
	signal(SIGINT, action);
	signal(SIGHUP, action);
	new_terminal(env);
	while (1)
	{
		line = readline((terminal())->title);
		if (!line || (string())->compare_n(line, "exit", 5))
		{
			free(line);
			ft_exit(0);
		}
		if ((string())->compare_n(line, "", 1))
		{
			free(line);
			continue;
		}
		line = ft_check_cotes(line);
		get_comando(line, &data);
		i = -1;
		while (data.comando[++i])
		{
			u = -1;
			while(data.comando[i][++u])
			printf("-%s-\n", data.comando[i][u]);
		}
		if (line != NULL && !(string())->compare_n(line, "", 1))
			add_history(line);
		ft_command_execute(data.comando);
		ft_free_data(&data, line);
	}
	return (0);
}

/* ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’. space, tab, newline 
Ctrl + 'D' - é quando a line for nula
Ctrl + 'D' - é quando a line for nula
Ctrl + 'D' - é quando a line for nula
*/