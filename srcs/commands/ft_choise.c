/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_choise.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:25:52 by rteles            #+#    #+#             */
/*   Updated: 2022/09/16 15:34:58 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute(t_command *c, int in)
{
	dup2(in, STDIN_FILENO);
	if (c->next != NULL)
		dup2(c->fd[1], STDOUT_FILENO);
	if (in != STDIN_FILENO)
		close(in);
	close(c->fd[1]);
	//c->execute(c, STDIN_FILENO);
	//if (c->next != NULL)
	//	execute(c->next, c->fd[0]);
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
	if (command[0] == "unset")
		return (ft_unset(c));
	return (ft_pipe(c));
}

void ft_command_execute(char ***commands)
{
	int			i;
	int			max_i;
	t_command 	*command;
	t_command 	*aux;
	commands = malloc(sizeof(char **) * 1);
	char	*comands_1[3] = {"cd", "..", NULL};
	char	*comands_2[3] = {"cd", "includes", NULL};
	char	*comands_3[2] = {"cd", NULL};
	//char	*comands_4[3] = {"cd", "asdasdasdasdas/", "asdasd", NULL};
	/*******/
	char	*comands_5[5] = {"echo", "-n", "\"ahahaha $USER \"", " hamburguer", NULL};
	char	*comands_6[4] = {"echo", "ahahaha ", "hamburguer", NULL};
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
	char	*comands_14[3] = {"pwd", NULL};
	//******/
	//char	*comands_15[3] = {"ls", "-la", NULL};
	//char	*comands_16[3] = {"grep", "1", NULL};
	//char	*comands_17[3] = {"grep", "minishell", NULL};
	//char	*comands_18[3] = {"wc", "-l", NULL};
	/*******/
	//char	*comands_19[2] = {"pwd", NULL};
	/*******/
	//char	*comands_20[3] = {"unset", NULL};
	//char	*comands_21[3] = {"unset", "Ola", NULL};
	//char	*comands_22[4] = {"unset", "Ola", "Adeus", NULL};
	/*******/



	commands[0] = comands_3;
	//commands[1] = comands_16;
	//commands[2] = comands_17;
	//commands[3] = comands_18;
	//max_i = 4;
	max_i = 1;
	i = -1;
	while (++i < max_i)
	{
		aux = ft_choise(commands[i]);
		if ((terminal())->start == NULL)
			(terminal())->start = aux;
		else
			command->next = aux;
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
