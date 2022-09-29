/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:49:00 by rteles            #+#    #+#             */
/*   Updated: 2022/09/29 00:48:28 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	env_execute(t_command *c, int in)
{
	t_env	*aux;

	if (c->next != NULL && is_redirect_left(c->next->command[0]) > 0)
		in = management_input_execute(c->next);
	if (in == -1)
		return ;
	if (c->command[1] != NULL)
	{
		printf("env: '%s': No such file or directory\n", c->command[1]);
		(terminal())->last_exit = 1;
		return ;
	}
	execute(c, in, 2);
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
	execute(c, in, 1);
}

t_command	*ft_env(t_command *c)
{
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = env_execute;
	return (c);
}
