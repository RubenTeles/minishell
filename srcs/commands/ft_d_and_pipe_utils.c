/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_and_pipe_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:53:36 by rteles            #+#    #+#             */
/*   Updated: 2022/10/03 22:05:23 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_d_pipe_or_and(t_command *c)
{
	int	len;

	if (!c)
		return (0);
	len = (string())->len(c->command[0]);
	if (len == 2 && (string())->compare_n(c->command[0], "&&", len))
		return (1);
	if (len == 2 && (string())->compare_n(c->command[0], "||", len))
		return (2);
	return (0);
}

int is_parethenses(t_command *c)
{
	int	len;

	if (!c)
		return (0);
	len = (string())->len(c->command[0]);
	if (len == 1 && (string())->compare_n(c->command[0], "(", len))
		return (1);
	if (len == 1 && (string())->compare_n(c->command[0], ")", len))
		return (2);
	return (0);
}

int	is_ppa(t_command *c)
{
	if ((is_parethenses(c) > 0) || (is_d_pipe_or_and(c) > 0))
		return (1);
	return (0);
}
