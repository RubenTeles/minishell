/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:51:30 by ede-alme          #+#    #+#             */
/*   Updated: 2022/08/20 20:52:27 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ft_string.h>

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

void	execute(t_terminal *rules, char **env)
{
	int		pid_t;
	char	*comands[3] = {	"ls", "-la", NULL };

	pid_t = fork();
	if (pid_t == 0)
	{
		execve("/bin/ls", comands, env);
		exit(127);
	}
	else
		exit(1);
}

int	main(int argc, char **argv, char **env)
{
	t_terminal rules;
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
		var = string()->sub_str_chars(line, 'o', '$');
		printf("%s \n", var);
		var2 = string()->sub_str_chars(line, '$', '$');
		printf("%s \n", var2);
		free(var);
		free(var2);
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
/*
/bin/ls

ls
dssf
^Cfsd
sdfsfdsfdsdsf

*/
