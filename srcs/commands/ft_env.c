/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:49:00 by rteles            #+#    #+#             */
/*   Updated: 2022/10/08 18:10:26 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	env_execute_2(t_command *c)
{
	t_env	*aux;

	execute(c, 2);
	aux = terminal()->env_l;
	while (aux)
	{
		if (aux->val)
		{
			write(c->fd[1], aux->var, string()->len(aux->var));
			write(c->fd[1], "=", 1);
			write(c->fd[1], aux->val, string()->len(aux->val));
			write(c->fd[1], "\n", 1);
		}
		aux = aux->next;
	}
	execute(c, 1);
}

static void	env_execute(t_command *c, int in)
{
	if (c->next != NULL && is_redirect_left(c->next->command[0]) > 0)
		in = management_input_execute(c->next);
	if (in == -1)
		return ;
	if (c->command[1] != NULL)
	{
		printf("env: '%s': No such file or directory\n", c->command[1]);
		c->exit_status = 1;
		execute(c, 2);
		return ;
	}
	env_execute_2(c);
}

t_command	*ft_env(t_command *c)
{
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = env_execute;
	c->choice = 3;
	return (c);
}
