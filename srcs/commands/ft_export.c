/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 22:41:55 by rteles            #+#    #+#             */
/*   Updated: 2022/09/16 14:04:05 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	show_export(t_command *c, int in)
{
	t_env	*aux;
	char	**env_ter;

	dup2(in, STDIN_FILENO);
	if (c->next != NULL)
		dup2(c->fd[1], STDOUT_FILENO);
	if (in != STDIN_FILENO)
		close(in);
	close(c->fd[1]);
	aux = terminal()->env_l;
	while (aux)
	{
		write(STDOUT_FILENO, "declare -x ", 11);
		write(STDOUT_FILENO, aux->var, string()->len(aux->var));
		if (aux->val)
		{
			write(STDOUT_FILENO, "=\"", 2);
			write(STDOUT_FILENO, aux->val, string()->len(aux->val));
			write(STDOUT_FILENO, "\"", 1);
		}
		write(STDOUT_FILENO, "\n", 1);
		aux = aux->next;
	}
}

static void	export_execute(t_command *c, int in)
{
	int	i;
	
	i = 0;
	if (c->count_cmd < 2)
		show_export(c, in);
	else
	{
		while (c->command[++i])
			terminal()->add_var(c->command[i]);
	}
	if (c->next != NULL)
		c->next->execute(c->next, c->fd[0]);
}

void	*ft_export(t_command *c)
{
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = export_execute;
}
