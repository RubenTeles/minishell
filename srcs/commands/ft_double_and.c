/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_and.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:10:42 by rteles            #+#    #+#             */
/*   Updated: 2022/10/03 00:28:10 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	double_and_execute(t_command *c, int in)
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
	if (c->next)
		c->next->execute(c->next, STDIN_FILENO);
	else
		printf("ERRO\n");
}

t_command	*ft_double_and(t_command *c)
{
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = double_and_execute;
	c->choice = 12;
	return (c);
}
