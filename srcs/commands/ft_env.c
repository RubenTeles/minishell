/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:49:00 by rteles            #+#    #+#             */
/*   Updated: 2022/09/07 00:10:45 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	env_execute(t_command *c, int in)
{
	printf("env\n");
	char	**env_ter;
	int		i;

	env_ter = terminal()->env_m;
	i = -1;
	if (c->command[1] != NULL)
	{
		printf("env: '%s': No such file or directory\n", c->command[1]);
		return ;
    }
	dup2(in, STDIN_FILENO);
	if (c->next != NULL)
		dup2(c->fd[1], STDOUT_FILENO);
	close(in);
	close(c->fd[1]);
	while (env_ter[++i])
	{
		if (string()->index_char(env_ter[i], '=') == -1)
			continue;
		write(STDOUT_FILENO, env_ter[i], string()->len(env_ter[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
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
	c->count_cmd = 0;
	while (command[c->count_cmd])
		c->count_cmd++;
	c->path = NULL;
	c->next = NULL;
	c->execute = env_execute;
	return (c);
}

t_command	*ft_env(char **input)
{
	/*(void)input;
	char	*input_1[2] = {"env", NULL};
	t_command *command;

	command = new_command(input_1);
	command->execute(command, 0);*/
	return (new_command(input));
}
