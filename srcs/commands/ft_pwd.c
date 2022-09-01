/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:49:00 by rteles            #+#    #+#             */
/*   Updated: 2022/09/01 23:32:53 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	pwd_execute(t_command *c, int in)
{
	char	*pwd;
	int		i;

    pwd = terminal()->variable_env("PWD");
	dup2(in, STDIN_FILENO);
	if (c->next != NULL)
		dup2(c->fd[1], STDOUT_FILENO);
	close(in);
	close(c->fd[1]);
    {
		write(STDOUT_FILENO, pwd, string()->len(pwd));
		write(STDOUT_FILENO, "\n", 1);
	}
	close(in);
	close(c->fd[1]);
    free(pwd);
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
	c->path = NULL;
	c->next = NULL;
	c->execute = pwd_execute;
	return (c);
}

void    ft_pwd(char **input)
{
	(void)input;
	char	*input_1[2] = {"pwd", NULL};
	t_command *command;

	command = new_command(input_1);
	command->execute(command, 0);
}
