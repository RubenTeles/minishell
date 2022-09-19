/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_choise.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:25:52 by rteles            #+#    #+#             */
/*   Updated: 2022/09/19 23:30:49 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute(t_command *c, int in, int option)
{
	int	fd;

	if (option == 0)
	{
		dup2(in, STDIN_FILENO);
		if (c->next && !string()->compare_n(c->next->command[0], "<", string()->len(c->next->command[0])))
			dup2(c->fd[1], STDOUT_FILENO);
		if (in != STDIN_FILENO)
			close(in);
		close(c->fd[1]);
	}
	else if (option == 1)
	{
		if (in != STDIN_FILENO)
			close(in);
		close(c->fd[1]);
		fd = c->fd[0];
		if (c->next && is_redirect_left(c->next->command[0]) > 0)
			c = last_command_left_redirect(c->next);
		if (c->next)
			c->next->execute(c->next, fd);
	}
}

static t_command *new_command(char **command)
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

t_command	*ft_choise(char **command)
{
	t_command	*c;

	c = new_command(command);
	if (string()->compare_n(command[0], "cd", string()->len(command[0])))
		return (ft_cd(c));
	if (string()->compare_n(command[0], "echo", string()->len(command[0])))
		return (ft_echo(c));
	if (string()->compare_n(command[0], "env", string()->len(command[0])))
		return (ft_env(c));
	if (string()->compare_n(command[0], "exit", string()->len(command[0])))
		return (ft_exit(c));
	if (string()->compare_n(command[0], "export", string()->len(command[0])))
		return (ft_export(c));
	if (string()->compare_n(command[0], "pwd", string()->len(command[0])))
		return (ft_pwd(c));
	if (string()->compare_n(command[0], "unset", string()->len(command[0])))
		return (ft_unset(c));
	if (string()->compare_n(command[0], ">>", string()->len(command[0])))
		return (ft_double_redirect_right(c));
	if (string()->compare_n(command[0], ">", string()->len(command[0])))
		return (ft_redirect_right(c));
	if (string()->compare_n(command[0], "<", string()->len(command[0])))
		return (ft_redirect_left(c));
	/*if (string()->compare_n(command[0], "<<", string()->len(command[0])))
		return (ft_double_redirect_left(c));*/
	return (ft_pipe(c));
}

void ft_command_execute(char ***commands)
{
	int			i;
	int			max_i;
	t_command 	*command;
	t_command 	*aux;
	commands = malloc(sizeof(char **) * 4);
	char	*comands_1[3] = {"cd", "..", NULL};
	char	*comands_2[3] = {"cd", "includes", NULL};
	//char	*comands_3[2] = {"cd", NULL};
	//char	*comands_4[3] = {"cd", "asdasdasdasdas/", "asdasd", NULL};
	/*******/
	//char	*comands_5[5] = {"echo", "-n", "\"ahahaha $USER \"", "hamburguer", NULL};
	//char	*comands_6[4] = {"echo", "ahahaha ", "hamburguer", NULL};
	/*******/
	//char	*comands_7[2] = {"env", NULL};
	//char	*comands_8[3] = {"env", "asdas", NULL};
	/*******/
	//char	*comands_9[2] = {"exit", NULL};
	/*******/
	//char	*comands_10[3] = {"export", NULL};
	//char	*comands_11[3] = {"export", "Ola=", NULL};
	//char	*comands_12[3] = {"export", "Ola", NULL};
	//char	*comands_13[3] = {"export", "Ola=hehe", NULL};
	/*******/
	char	*comands_14[3] = {"ls", "-la", NULL};
	//char	*comands_14[2] = {"ls", NULL};
	//char	*comands_15[3] = {"grep", "1", NULL};
	char	*comands_16[3] = {"grep", "minishell", NULL};
	//char	*comands_17[3] = {"wc", "-l", NULL};
	/*******/
	//char	*comands_18[2] = {"pwd", NULL};
	/*******/
	//char	*comands_19[2] = {"unset", NULL};
	//char	*comands_20[3] = {"unset", "Ola", NULL};
	//char	*comands_21[4] = {"unset", "Ola", "Adeus", NULL};
	/*******/
	char	*comands_22[3] = {">", "texto", NULL};
	char	*comands_23[3] = {">", "Adeus", NULL};
	//char	*comands_24[3] = {">", "BYE", NULL};
	//char	*comands_23[4] = {">", "texto", "Adeus", NULL};
	/*******/
	char	*comands_24[3] = {">>", "BYE", NULL};
	//char	*comands_25[4] = {">>", "texto", "Adeus", NULL};
	/*******/
	char	*comands_26[3] = {"wc", "-l", NULL};
	char	*comands_27[3] = {"<", "Adeus", NULL};
	char	*comands_28[3] = {"<", "BYE", NULL};

	//commands[0] = comands_14;
	//commands[1] = comands_22;
	//commands[2] = comands_23;
	//commands[3] = comands_24;

	commands[0] = comands_26;
	commands[1] = comands_27;
	commands[2] = comands_28;
	//commands[3] = comands_24;
	//max_i = 4;
	max_i = 3;
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
