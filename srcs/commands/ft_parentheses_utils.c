/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parentheses_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:53:23 by rteles            #+#    #+#             */
/*   Updated: 2022/10/10 19:21:36 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_command	*ft_close(t_command *aux, t_command *close, int on, int values)
{
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
	return (close);
}

int	is_in_p_pipe(t_command *c)
{
	t_command	*aux;
	t_command	*close;

	aux = c;
	close = ft_close(aux, 0, 0, 0);
	while (close && close->next && is_parethenses(close->next) == 2)
		close = close->next;
	if (close && close->next && !is_ppa(close->next))
		return (1);
	return (0);
}
