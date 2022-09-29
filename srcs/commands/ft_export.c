/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 22:41:55 by rteles            #+#    #+#             */
/*   Updated: 2022/09/28 22:27:14 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	show_export(t_command *c, int in)
{
	t_env	*aux;

	(void)c;
	(void)in;
	aux = terminal()->env_l;
	while (aux)
	{
		write(c->fd[1], "declare -x ", 11);
		write(c->fd[1], aux->var, string()->len(aux->var));
		if (aux->val)
		{
			write(c->fd[1], "=\"", 2);
			write(c->fd[1], aux->val, string()->len(aux->val));
			write(c->fd[1], "\"", 1);
		}
		write(c->fd[1], "\n", 1);
		aux = aux->next;
	}
}

static void	export_execute(t_command *c, int in)
{
	int	i;

	i = 0;
	in = management_input_execute(c->next);
	if (in == -1)
		return ;
	execute(c, in, 2);
	if (c->count_cmd < 2)
		show_export(c, in);
	else
		while (c->command[++i])
			terminal()->add_var(c->command[i]);
	execute(c, in, 1);
}

t_command	*ft_export(t_command *c)
{
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = export_execute;
	return (c);
}
