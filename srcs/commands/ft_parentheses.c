/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parentheses.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:50:27 by rteles            #+#    #+#             */
/*   Updated: 2022/10/04 23:06:10 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_command	*open_paretheses(t_command *c, t_command *aux)
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
		printf("syntax error near expected token `)'\n");
		c->exit_status = 2;
		return (NULL);
	}
	aux->count_cmd = c->count_cmd;
	return (aux);
}

static void	parentheses_open_execute(t_command *c, int in)
{
	t_command	*last;
	t_command	*next_p_a;

	last = open_paretheses(c, c);
	if (!last)
		return ;
	if ((c->prev && (!(is_token(c->prev))
				&& !(is_parethenses(c->prev) == 1)))
		|| (!c->next || (is_token(c->next))
			|| (is_parethenses(c->next) == 2))
		|| ((is_parethenses(c->prev) == 1)
			&& (is_parethenses(last->next) == 2)))
	{
		printf("syntax error near unexpected token `('\n");
		c->exit_status = 2;
		return ;
	}
	if ((c->prev && c->prev && (is_d_pipe_or_and(c->prev) == 2)
			&& c->prev->exit_status == 0))
	{
		next_p_a = next_d_pipe_or_and(last);
		if (next_p_a)
		{
			next_p_a->execute(next_p_a, in);
			return;
		}
		return ;
	}
	if (!c->prev)
		c->next->execute(c->next, in);
	/*if (!c->prev || ((c->prev && (is_d_pipe_or_and(c->prev) == 1)))
		|| (c->prev && (is_d_pipe_or_and(c->prev) == 2)
			&& c->prev->exit_status != 0) || is_parethenses(c->prev) == 1)
		c->next->execute(c->next, in);
	else if ((c->prev && (is_d_pipe_or_and(c->prev) == 2)
			&& c->prev->exit_status == 0) && last->next)
		last->next->execute(last->next, in);*/
}

static void	parentheses_close_execute(t_command *c, int in)
{
	if ((c->next && (!(is_token(c->next)) && !(is_parethenses(c->next) == 2)))
		|| (!c->prev || ((is_token(c->prev))
				|| (is_parethenses(c->prev) == 1))))
	{
		printf("syntax error near unexpected token `)'\n");
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
