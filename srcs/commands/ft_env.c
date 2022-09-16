/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:49:00 by rteles            #+#    #+#             */
/*   Updated: 2022/09/16 15:49:21 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	env_execute(t_command *c, int in)
{
	t_env	*aux;
	char	**env_ter;

	if (c->command[1] != NULL)
	{
		printf("env: '%s': No such file or directory\n", c->command[1]);
		return ;
	}
	execute(c, in,  0);
	aux = terminal()->env_l;
	while (aux)
	{
		if (aux->val)
		{
			write(STDOUT_FILENO, aux->var, string()->len(aux->var));
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, aux->val, string()->len(aux->val));
			write(STDOUT_FILENO, "\n", 1);
		}
		aux = aux->next;
	}
	execute(c, in, 1);
}

void	*ft_env(t_command *c)
{
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = env_execute;
}
