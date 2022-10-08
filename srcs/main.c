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

void	formate_tokens_main(t_data *data)
{
	int	i;
	int	j;

	j = -1;
	while (data->comando[++j])
	{
		i = -1;
		//printf("O comando   ->  ");
		while (data->comando[j][++i])
		{
			//printf("%s\n", data->comando[j][i]);
			data->comando[j][i] = ft_formattoken(data->comando[j][i]);
		}
	}
}

int	ft_readline_while_2(t_data *data)
{
	(terminal())->line = ft_check_cotes((terminal())->line);
	data->input = ft_split_line((terminal())->line, 0, NULL, NULL);
	if (!ft_multipipe(data->input) && !ft_check_parents(data->input)
		&& get_comando((terminal())->line, data))
	{
		formate_tokens_main(data);
		(terminal())->execute(data->comando, STDIN_FILENO);
		if ((terminal())->line
			&& !(string())->compare_n((terminal())->line, "", 1))
			add_history((terminal())->line);
		ft_free_data(data, (terminal())->line);
		return (0);
	}
	add_history((terminal())->line);
	free((terminal())->line);
	return (1);
}

static void	ft_readline_while(void)
{
	t_data	data;

	while (1)
	{
		(terminal())->line = readline((terminal())->title);
		if (!(terminal())->line
			|| (string())->compare_n((terminal())->line, "exit", 5))
		{
			if ((terminal())->line)
				free((terminal())->line);
			ft_exit(0);
		}
		if ((string())->compare_n((terminal())->line, "", 1)
			|| ft_str_is((terminal())->line, ' ', ' '))
		{
			free((terminal())->line);
			continue ;
		}
		if (ft_readline_while_2(&data))
			continue ;
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	signal(SIGINT, action);
	signal(SIGQUIT, action);
	//ft_call();
	new_terminal(env);
	ft_readline_while();
	return (0);
}

/* ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’. space, tab, newline 
Ctrl + 'D' - é quando a line for nula
Ctrl + '\' - não faz nada
Ctrl + 'C' - nova quebra de linha
*/