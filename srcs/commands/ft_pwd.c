/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:49:00 by rteles            #+#    #+#             */
/*   Updated: 2022/09/02 07:16:56 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


static void	pwd_execute(t_command *c, int in)
{
	printf("pwd\n");
	char	*pwd;

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

t_command	*ft_pwd(char **input)
{
	/*(void)input;
	char	*input_1[2] = {"pwd", NULL};
	t_command *command;

	command = new_command(input_1);
	command->execute(command, 0);*/
	return (new_command(input));
}
