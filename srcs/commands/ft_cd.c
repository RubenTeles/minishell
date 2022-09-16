/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:06:27 by rteles            #+#    #+#             */
/*   Updated: 2022/09/16 15:39:38 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	cd_execute(t_command *c, int in)
{
	char	buffer[100];
	int		i;

	execute(c, in);
	if (c->count_cmd > 2)
	{
		printf("cd: too many arguments\n");
		return ;
	}
	if (c->command[1] == NULL && (terminal())->var_exist("HOME"))
		c->command[1] = (terminal())->variable_env("HOME");
	if (access(c->command[1], F_OK))
	{
		printf("cd: %s: No such file or directory\n", c->command[1]);
		return ;
	}
	(terminal())->update_var("OLDPWD", getcwd(buffer, 100));
	chdir(c->command[1]);
	(terminal())->update_var("PWD", getcwd(buffer, 100));
	if (in != STDIN_FILENO)
		close(in);
	close(c->fd[1]);
	if (c->next != NULL)
		c->next->execute(c->next, c->fd[0]);
}

void	*ft_cd(t_command *c)
{
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = cd_execute;
}
