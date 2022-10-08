/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parentheses_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:53:23 by rteles            #+#    #+#             */
/*   Updated: 2022/10/08 17:54:01 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_in_p_pipe(t_command *c)
{
	t_command	*aux;
	t_command	*close;
	int			values;
	int			on;

	aux = c;
	values = 0;
	on = 0;
	close = NULL;
	while (aux)
	{
		if (is_parethenses(aux) == 1)
		{
			values += 1;
			on = 1;
		}
		if (is_parethenses(aux) == 2)
		{
			values -= 1;
			if (on == 1)
				on = 0;
			else
				if (values == -1)
					close = aux;
		}
		aux = aux->next;
	}
	while (close && close->next && is_parethenses(close->next) == 2)
		close = close->next;
	if (close && close->next && !is_ppa(close->next))
		return (1);
	return (0);
}
