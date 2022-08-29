/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:49:00 by rteles            #+#    #+#             */
/*   Updated: 2022/08/29 23:03:48 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	env_execute(t_command *c, int i)
{
	if (c->command[1] != NULL)
	{
        printf("env: '%s': No such file or directory\n", c->command[1]);
        rl_on_new_line();
        return ;
    }
	while (terminal()->env_m[++i])
		printf("%s\n", terminal()->env_m[i]);
	rl_on_new_line();
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
	c->execute = env_execute;
	return (c);
}

void    ft_env(char **input)
{
	(void)input;
	char	*input_1[2] = {"env", NULL};
	t_command *command;

	command = new_command(input_1);
	command->execute(command, -1);
}
