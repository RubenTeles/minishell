/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_choise.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:25:52 by rteles            #+#    #+#             */
/*   Updated: 2022/09/29 01:08:30 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parse.h>

static t_command	*new_command(char **command)
{
	t_command	*c;

	c = malloc(sizeof(t_command));
	if (!c)
		return (NULL);
	c->command = command;
	c->count_cmd = 0;
	c->path = NULL;
	c->prev = NULL;
	c->next = NULL;
	pipe(c->fd);
	return (c);
}

t_command	*ft_choise_2(t_command *c, char **command, int i)
{
	if (i == 2 && (string())->compare_n(command[0], ">>", i))
		return (ft_double_redirect_right(c));
	if (i == 1 && (string())->compare_n(command[0], ">", i))
		return (ft_redirect_right(c));
	if (i == 2 && (string())->compare_n(command[0], "<<", i))
		return (ft_double_redirect_left(c));
	if (i == 1 && (string())->compare_n(command[0], "<", i))
		return (ft_redirect_left(c));
	return (ft_pipe(c));
}

t_command	*ft_choise(char **command)
{
	t_command	*c;
	int			i;

	c = new_command(command);
	i = (string())->len(command[0]);
	if (i == 2 && (string())->compare_n(command[0], "cd", i))
		return (ft_cd(c));
	if (i == 4 && (string())->compare_n(command[0], "echo", i))
		return (ft_echo(c));
	if (i == 3 && (string())->compare_n(command[0], "env", i))
		return (ft_env(c));
	if (i == 4 && (string())->compare_n(command[0], "exit", i))
		return (ft_exit(c));
	if (i == 6 && (string())->compare_n(command[0], "export", i))
		return (ft_export(c));
	if (i == 3 && (string())->compare_n(command[0], "pwd", i))
		return (ft_pwd(c));
	if (i == 5 && (string())->compare_n(command[0], "unset", i))
		return (ft_unset(c));
	return (ft_choise_2(c, command, i));
}

void ft_command_execute(char ***commands)
{
	int			i;
	int			max_i;
	t_command 	*command;
	t_command 	*aux;
	int			i_erro;

	i_erro = STDERR_FILENO;
	(void)i_erro;
	max_i = 0;
	while (commands[max_i])
		max_i++;
	i = -1;
	while (++i < max_i)
	{
		aux = ft_choise(commands[i]);
		if ((terminal())->start == NULL)
			(terminal())->start = aux;
		else
		{
			aux->prev = command;
			command->next = aux;
		}
		command = aux;
	}
	(terminal())->start->execute((terminal())->start, STDIN_FILENO);
	aux = (terminal())->start;
	while (aux)
	{
		wait(&aux->pid);//preciso do status do filho.
		/*https://www.geeksforgeeks.org/exit-status-child-process-linux/?ref=lbp
		https://www.geeksforgeeks.org/exit-status-variable-in-linux/?ref=gcse*/
		aux = aux->next;
	}
	(terminal())->destroy->commands();
	(terminal())->update->title();
}
