/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_choise.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:25:52 by rteles            #+#    #+#             */
/*   Updated: 2022/09/02 06:28:31 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_choise(char *line)
{
	if (string()->compare_n(line, "echo", string()->len(line)))
		ft_echo(0);
	else if (string()->compare_n(line, "pwd", string()->len(line)))
		ft_pwd(0);
	else if (string()->compare_n(line, "env", string()->len(line)))
		ft_env(0);
	else if (string()->compare_n(line, "exit", string()->len(line)) ||
		!line)
		ft_exit(0);
	/*else if (command[0] == "export")
		ft_export(command);
	else if (command[0] == "unset")
		ft_unset(command);
	else if (command[0] == "cd")
		ft_cd(command);
	else
		ft_pipe(command);*/
}

void ft_execute(void)
{
	int			i;
	int			max_i;
	t_command 	*command;
	t_command 	*aux;
	char	***comands = malloc(sizeof(char **) * 4);
	char	*comands_1[3] = {"ls", "-la", NULL};
	char	*comands_2[3] = {"grep", "5", NULL};
	char	*comands_3[3] = {"grep", "a.out", NULL};
	char	*comands_4[3] = {"wc", "-l", NULL};

	comands[0] = comands_1;
	comands[1] = comands_2;
	comands[2] = comands_3;
	comands[3] = comands_4;
	max_i = 4;
	i = -1;
	while (++i < max_i)
	{
		aux = new_command(comands[i]);
		if (terminal()->start == NULL)
			terminal()->start = aux;
		else
			command->next = aux;
		command = aux;
	}
	terminal()->start->execute(terminal()->start, STDIN_FILENO);
	aux = terminal()->start;
	while (aux)
	{
		wait(&aux->pid);
		aux = aux->next;
	}
	//destroy commands
}
