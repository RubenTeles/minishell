/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:18:57 by rteles            #+#    #+#             */
/*   Updated: 2022/09/01 22:49:39 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char *echo_string(t_command *c, char *temp, char *str, int i)
{
	int		len;
	
	temp = malloc(sizeof(char) * 1);
	temp[0] = '\0';
	while (c->command[++i])
	{
		str = string()->join(temp, c->command[i]);
		free(temp);
		if (!c->command[i + 1])
			break;
		len = string()->len(str) + 1;
		temp = malloc(sizeof(char) * len);
		string()->copy_n(temp, str, len);
		free(str);
	}
	return (str);
}

static void	echo_execute(t_command *c, int in)
{
	int		i;
	char	*str;

	i = 0;
	if (c->command[1] == "-n")
		i++;
	str = echo_string(c, 0, 0, i);
	dup2(in, STDIN_FILENO);
	if (c->next != NULL)
		dup2(c->fd[1], STDOUT_FILENO);
	close(in);
	close(c->fd[1]);
	write(STDOUT_FILENO, str, string()->len(str));
	if (c->command[1] != "-n")
		write(STDOUT_FILENO, "\n", 1);
	free(str);
	close(in);
	close(c->fd[1]);
	if (c->next != NULL)
		c->next->execute(c->next, c->fd[0]);
}

static t_command *new_command(char	**command)
{
	t_command	*c;

	c = malloc(sizeof(t_command));
	if (!c)
		return (NULL);
	c->command = command;
	c->path = 0;
	c->next = NULL;
	c->execute = echo_execute;
	return (c);
}

void    ft_echo(char **input)
{
	(void)input;
	char	*input_1[5] = {"echo", "-n", "ahahaha ", "hamburguer", NULL};
	char	*input_2[4] = {"echo", "ahahaha ", "hamburguer", NULL};
	t_command *command;

	command = new_command(input_2);
	command->execute(command, 0);
}
