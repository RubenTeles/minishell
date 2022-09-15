/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:49:00 by rteles            #+#    #+#             */
/*   Updated: 2022/09/15 22:52:22 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	pwd_execute(t_command *c, int in)
{
	char	*pwd;

    pwd = (terminal())->variable_env("PWD");
	dup2(in, STDIN_FILENO);
	if (c->next != NULL)
		dup2(c->fd[1], STDOUT_FILENO);
	if (in != STDIN_FILENO)
		close(in);
	close(c->fd[1]);
	write(STDOUT_FILENO, pwd, string()->len(pwd));
	write(STDOUT_FILENO, "\n", 1);
    free(pwd);
	if (c->next != NULL)
		c->next->execute(c->next, c->fd[0]);
}

void	*ft_pwd(t_command *c)
{
	/*	char		*input_1[2] = {"pwd", NULL};

	c->command = input_1;*/
	
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = pwd_execute;
}
