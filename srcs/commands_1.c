/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:02:33 by rteles            #+#    #+#             */
/*   Updated: 2022/08/23 00:15:46 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*Retorna o path com o comando certo*/
char	*path_command(char *command)
{
	//char	*aux_command;
	char	*aux_path;
	int		i;

	i = -1;
	aux_path = 0;
	printf("comand: %s \n", command);
	//aux_command = string()->join("/", command);
	while (terminal()->path[++i])
	{
		aux_path = string()->join(terminal()->path[i], command);
		if (!access(aux_path, F_OK))
			break ;
		free(aux_path);
	}
	//free(aux_command);
	return (aux_path);
}

void	ft_execute(char *path_command)
{
	int		pid_t;
	char	*comands[3] = {	"ls", "-la", NULL };

	if (!path_command)
		return ;
	pid_t = fork();
	if (pid_t == 0)
	{
		execve(path_command, comands, terminal()->env_m);
		free(path_command);
		exit(127);
	}
	else
		exit(1);
}
