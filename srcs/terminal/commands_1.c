/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:02:33 by rteles            #+#    #+#             */
/*   Updated: 2022/08/23 20:59:54 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <sys/types.h>
#include <sys/wait.h>

/*Retorna o path com o comando certo*/
char	*path_command(char *command)
{
	char	*aux_path;
	int		i;

	i = -1;
	aux_path = 0;
	while (terminal()->path[++i])
	{
		aux_path = string()->join(terminal()->path[i], command);
		if (!access(aux_path, F_OK))
			break ;
		free(aux_path);
	}
	return (aux_path);
}

void	ft_execute(char *path)
{
	int		pid_t;
	char	*comands[3] = {	"ls", "-la", NULL };

	if (!path)
		return ;
	pid_t = fork();
	if (pid_t == 0)
	{
		if (execve(path, comands, terminal()->env_m) < 0)
			printf("%s: Command not found\n", comands[0]);
		exit(0);
	}
	else
		wait(&pid_t);
}
