/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:10:53 by rteles            #+#    #+#             */
/*   Updated: 2022/10/03 23:37:16 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	double_pipe_execute(t_command *c, int in)
{
	t_command	*aux;
	int			status;

	status = 0;
	(void)in;
	aux = (terminal())->start;
	while (aux != c)
	{
		waitpid(aux->pid, &status, 0);
		if (WIFEXITED(status) && aux->choice == 12 && aux->exit_status == 0)
			aux->exit_status = WEXITSTATUS(status);
		(terminal())->last_exit = aux->exit_status;
		if (aux->next == c)
			break ;
		aux = aux->next;
	}
	if ((terminal())->last_exit == 0)
	{
		c->exit_status = (terminal())->last_exit;
		if (c->next && (is_parethenses(c->next) > 0))
			c->next->execute(c->next, STDIN_FILENO);
		else if (c->next->next)
			c->next->next->execute(c->next->next, STDIN_FILENO);
		return ;
	}
	if (c->next)
		c->next->execute(c->next, STDIN_FILENO);
}

t_command	*ft_double_pipe(t_command *c)
{
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = double_pipe_execute;
	c->choice = 13;
	return (c);
}
