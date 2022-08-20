/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:51:30 by ede-alme          #+#    #+#             */
/*   Updated: 2022/08/20 14:59:21 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*void	create_path_comands(t_terminal *rules, char **env, int i)
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
	rules->comands_path = 0;
}*/
/*
void	execute(t_terminal *rules, char **env)
{
	int		pid_t;
	char	*comands[3] = {"ls", "-la", NULL};

	pid_t = fork();
	if (pid_t == 0)
	{
		execve("/bin/ls", comands, env);
		exit(127);
	}
	else
		exit(1);
}
*/

void	ft_get_comand(char *line, char ***out, int *i, int comands)
{
	char	*comand_line;
	int		temp_i;

	temp_i = *i;
	while (line[temp_i] && line[temp_i] != ' ')
		temp_i++;
	temp_i = temp_i - *i;
	comand_line = malloc(sizeof(char) * temp_i + 1);
	comand_line[temp_i] = '\0';
	while (comand_line[*i] != '\0')
		comand_line[*i] = line[*i++];
	out[comands][0] = comand_line;
}

char	***ft_tri_split(char *line)
{
	char	out[100][100][100];
	int		i;
	int		comands;

	i = 0;
	comands = 0;
	while (line[i])
	{
		ft_get_comand(line, out, &i, comands);
		while (line[i] && line[i] != '|')
		{
			//ft_get_flag(line, out, &i, comands);
		}
		comands++;
	}
	return (out);
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_terminal	t;

	(void)argc;
	(void)argv;
	while (1)
	{
		line = readline("Meu terminal$ ");
		if (line)
			break ;
	}
	t.input = ft_tri_split(line);
	printf("%s\n", line);
	return (0);
}
