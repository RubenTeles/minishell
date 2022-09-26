/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_choise.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:25:52 by rteles            #+#    #+#             */
/*   Updated: 2022/09/26 04:52:45 by rteles           ###   ########.fr       */
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
		wait(&aux->pid);
		aux = aux->next;
	}
	(terminal())->destroy->commands();
	(terminal())->update->title();
}
/*
void	ft_command_finish(void)
{
	t_command	*aux;

	aux = (terminal())->start;
	while (aux)
	{
		wait(&aux->pid);
		aux = aux->next;
	}
	(terminal())->destroy->commands();
	(terminal())->update->title();
}

void	ft_command_execute(t_data *data)
{
	t_command	*command;
	t_command	*aux;

	while (data->start)
	{
		aux = ft_choise(data->start->commands);
		if ((terminal())->start == NULL)
			(terminal())->start = aux;
		else
		{
			aux->prev = command;
			command->next = aux;
		}
		command = aux;
		data->start = data->start->next;
	}
	(terminal())->start->execute((terminal())->start, STDIN_FILENO);
	ft_command_finish();
}
*/
//void	ft_command_execute(char ***commands)
//{
//	int			i;
//	int			max_i;
//	t_command 	*command;
//	t_command 	*aux;
//
//	commands = malloc(sizeof(char **) * 4);
//	//char	*comands_1[3] = {"cd", "..", NULL};
//	//char	*comands_2[3] = {"cd", "includes", NULL};
//	//char	*comands_3[2] = {"cd", NULL};
//	//char	*comands_4[3] = {"cd", "asdasdasdasdas/", "asdasd", NULL};
//	/*******/
//	char	*comands_5[5] = {"echo", "-n", "ahahaha", "hamburguer", NULL};
//	char	*comands_6[4] = {"echo", "ahahaha", "hamburguer", NULL};
//	/*******/
//	//char	*comands_7[2] = {"env", NULL};
//	//char	*comands_8[3] = {"env", "asdas", NULL};
//	/*******/
//	//char	*comands_9[2] = {"exit", NULL};
//	/*******/
//	char	*comands_10[3] = {"export", NULL};
//	//char	*comands_11[3] = {"export", "Ola=", NULL};
//	//char	*comands_12[3] = {"export", "Ola", NULL};
//	char	*comands_13[3] = {"export", "USER=STRONG", NULL};
//	/*******/
//	//char	*comands_14[3] = {"ls", "-l", NULL};
//	//char	*comands_14[2] = {"ls", NULL};
//	//char	*comands_15[3] = {"grep", "srcs", NULL};
//	//char	*comands_16[3] = {"grep", "minishell", NULL};
//	//char	*comands_17[3] = {"wc", "-l", NULL};
//	/*******/
//	//char	*comands_18[2] = {"pwd", NULL};
//	/*******/
//	//char	*comands_19[2] = {"unset", NULL};
//	//char	*comands_20[3] = {"unset", "Ola", NULL};
//	//char	*comands_21[4] = {"unset", "Ola", "Adeus", NULL};
//	/*******/
//	//char	*comands_22[3] = {">", "texto", NULL};
//	//char	*comands_23[3] = {">", "Adeus", NULL};
//	//char	*comands_24[3] = {">", "BYE", NULL};
//	//char	*comands_23[4] = {">", "texto", "Adeus", NULL};
//	/*******/
//	//char	*comands_24[3] = {">>", "BYE", NULL};
//	//char	*comands_25[4] = {">>", "texto", "Adeus", NULL};
//	/*******/
//	//char	*comands_26[3] = {"wc", "-l", NULL};
//	//char	*comands_27[3] = {"<", "Adeus", NULL};
//	//char	*comands_28[3] = {"<", "BYE", NULL};
//	/*******/
//	//char	*comands_29[3] = {"<<", "Adeus", NULL};
//	//char	*comands_30[3] = {"<", "minishel.txt", NULL};
//	/****ERROS****/
//	//char	*comands_31[2] = {">", NULL};
//	//char	*comands_32[2] = {"<", NULL};
//	//char	*comands_33[2] = {".", NULL};
//	//char	*comands_34[3] = {">", "asd", NULL};
//	//char	*comands_35[3] = {"<", "ola", NULL};
//	//char	*comands_36[3] = {">", "ola", NULL};
//	//char	*comands_37[3] = {">>", "ola", NULL};
//
//	commands[0] = comands_5;
//	//commands[1] = comands_29;
//	//commands[2] = comands_6;
//	//commands[3] = comands_24;
//	//max_i = 4;
//	max_i = 1;
//	i = -1;
//	while (++i < max_i)
//	{
//		aux = ft_choise(commands[i]);
//		if ((terminal())->start == NULL)
//			(terminal())->start = aux;
//		else
//		{
//			aux->prev = command;
//			command->next = aux;
//		}
//		command = aux;
//	}
//	(terminal())->start->execute((terminal())->start, STDIN_FILENO);
//	aux = (terminal())->start;
//	while (aux)
//	{
//		wait(&aux->pid);
//		command = aux;
//		aux = aux->next;
//	}
//	free(commands);
//	(terminal())->destroy->commands();
//	(terminal())->update->title();
//}

/*
void ft_command_execute_2(char ***commands)
{
	int			i;
	int			max_i;
	t_command 	*command;
	t_command 	*aux;

	commands = malloc(sizeof(char **) * 1);
	//char	*comands_10[2] = {"export", NULL};
	char	*comands_20[3] = {"unset", "USER", NULL};

	commands[0] = comands_20;
	max_i = 1;
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
		wait(&aux->pid);
		command = aux;
		aux = aux->next;
	}
	free(commands);
	(terminal())->destroy->commands();
	(terminal())->update->title();
}

void ft_command_execute_3(char ***commands)
{
	int			i;
	int			max_i;
	t_command 	*command;
	t_command 	*aux;

	commands = malloc(sizeof(char **) * 1);
	char	*comands_20[3] = {"unset", "PWD", NULL};

	commands[0] = comands_20;
	max_i = 1;
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
		wait(&aux->pid);
		command = aux;
		aux = aux->next;
	}
	free(commands);
	(terminal())->destroy->commands();
	(terminal())->update->title();
}
*/