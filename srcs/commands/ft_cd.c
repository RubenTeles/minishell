/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:06:27 by rteles            #+#    #+#             */
/*   Updated: 2022/09/15 22:50:42 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	cd_execute(t_command *c, int in)
{
	char	buffer[100];
	char	*str;
	int		i;

	if (c->count_cmd > 2)
	{
		printf("cd: too many arguments\n");
		return ;
	}
	if (c->command[1] == NULL)
		c->command[1] = string()->replace(c->command[1], "/\0");
	if (access(c->command[1], F_OK))
	{
		printf("cd: %s: No such file or directory\n", c->command[1]);
		return ;
	}
	(terminal())->update_var("OLDPWD", getcwd(buffer, 100));
	chdir(c->command[1]);
	(terminal())->update_var("PWD", getcwd(buffer, 100));
	if (c->next != NULL)
		c->next->execute(c->next, c->fd[0]);
}

void	*ft_cd(t_command *c)
{
	/*char	*input_1[3] = {"cd", "..", NULL};
	char	*input_2[3] = {"cd", "includes", NULL};
	char	*input_3[2] = {"cd", NULL};
	char	*input_4[3] = {"cd", "asdasdasdasdas/", NULL};

	c->command = input_1;*/
	
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = cd_execute;
}
