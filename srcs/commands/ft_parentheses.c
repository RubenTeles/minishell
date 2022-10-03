/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parentheses.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:50:27 by rteles            #+#    #+#             */
/*   Updated: 2022/10/03 23:36:30 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_command *open_paretheses(t_command *c, t_command *aux)
{
	int	count;

	count = 1;
	c->count_cmd = 0;
	aux = aux->next;
	while (aux)
	{
		c->count_cmd++;
		if ((string())->compare_n(aux->command[0], "(", 1))
			count++;
		else if ((string())->compare_n(aux->command[0], ")", 1))
			count--;
		if (count == 0)
			break ;
		aux = aux->next;
	}
	if (!aux)
	{
		printf("ERRO NAO HA FIM\n");
		return (NULL);
	}
	aux->count_cmd = c->count_cmd;
	return (aux);
}

static void	parentheses_open_execute(t_command *c, int in)
{
	t_command	*last;

	if ((c->prev && (!(is_d_pipe_or_and(c->prev) > 0)
		&& !(is_parethenses(c->prev) == 1)))
		|| (!c->next || (is_d_pipe_or_and(c->next) > 0)
		|| (is_parethenses(c->next) == 2)))
	{
		printf("syntax error near unexpected token `%s'\n", c->command[0]);
		c->exit_status = 2;
		return ;
	}
	last = open_paretheses(c, c);
	if (!c->prev || ((c->prev && (is_d_pipe_or_and(c->prev) == 1)))
			|| (c->prev && (is_d_pipe_or_and(c->prev) == 2)
			&& c->prev->exit_status != 0) || is_parethenses(c->prev) == 1)
		c->next->execute(c->next, in);
	else if ((c->prev && (is_d_pipe_or_and(c->prev) == 2)
			&& c->prev->exit_status == 0) && last->next)
		last->next->execute(last->next, in);
}

static void	parentheses_close_execute(t_command *c, int in)
{
	if ((c->next && (!(is_d_pipe_or_and(c->next) > 0)
		&& !(is_parethenses(c->next) == 2)))
		|| (!c->prev || ((is_d_pipe_or_and(c->prev) > 0)
		|| (is_parethenses(c->prev) == 1))))
	{
		printf("syntax error near unexpected token `%s'\n", c->command[0]);
		c->exit_status = 2;
		return ;
	}
	if (c->next && c->count_cmd > 0)
		c->next->execute(c->next, in);
}


t_command	*ft_parentheses(t_command *c)
{
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	if ((string())->compare_n(c->command[0], "(", 1))
		c->execute = parentheses_open_execute;
	else if ((string())->compare_n(c->command[0], ")", 1))
		c->execute = parentheses_close_execute;
	c->choice = 14;
	return (c);
}
