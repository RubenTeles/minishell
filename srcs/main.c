/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:51:30 by ede-alme          #+#    #+#             */
/*   Updated: 2022/08/19 19:58:06 by ede-alme         ###   ########.fr       */
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
*/
int	main(int argc, char **argv, char **env)
{
	//t_terminal rules;
	char	*line;
	//int		i;

	(void)argc;
	(void)argv;
	line = NULL;
	//new_terminal("The Best: ", env);
	while (1)
	{
		line = readline("Teste_prompt$ ");
		if (line)
			break;
	}
	printf("%s\n", line);
	/*while(terminal()->path[++i])
		printf("%s \n", terminal()->path[i]);*/


	//create_path_comands(&rules, env, -1);
	//execute(&rules, env);
	/*while (rules.comands_path[++i])
		printf("%s \n", rules.comands_path[i]);*/
	return (0);
}
/*
/bin/ls

ls
dssf
^Cfsd
sdfsfdsfdsdsf

*/
