/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_choise.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:25:52 by rteles            #+#    #+#             */
/*   Updated: 2022/09/12 19:41:00 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_command	*ft_choise(char **command)
{
	if (string()->compare_n(command[0], "cd", string()->len(command[0])))
		return (ft_cd(command));
	if (string()->compare_n(command[0], "echo", string()->len(command[0])))
		return (ft_echo(command));
	if (string()->compare_n(command[0], "env", string()->len(command[0])))
		return (ft_env(command));
	if (string()->compare_n(command[0], "exit", string()->len(command[0])))
		return (ft_exit(command));
	if (string()->compare_n(command[0], "export", string()->len(command[0])))
		return (ft_export(command));
	if (string()->compare_n(command[0], "pwd", string()->len(command[0])))
		return (ft_pwd(command));
	/*
	if (command[0] == "unset")
		return (ft_unset(command));
	*/
	return (ft_pipe(command));
}

void ft_command_execute(char ***commands)
{
	int			i;
	int			max_i;
	t_command 	*command;
	t_command 	*aux;
	commands = malloc(sizeof(char **) * 4);
	char	*comands_1[3] = {"ls", "-la", NULL};
	char	*comands_2[3] = {"grep", "1", NULL};
	char	*comands_3[3] = {"grep", "minishell", NULL};
	char	*comands_4[3] = {"wc", "-l", NULL};

	commands[0] = comands_1;
	commands[1] = comands_2;
	commands[2] = comands_3;
	commands[3] = comands_4;
	max_i = 4;
	i = -1;
	while (++i < max_i)
	{
		aux = ft_choise(commands[i]);
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
		command = aux;
		aux = aux->next;
		free(command);
	}
	//rl_on_new_line();
	/*while (--i >= 0)
		free(commands[i]);*/
	free(commands);
	//destroy commands
}
