/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 22:41:55 by rteles            #+#    #+#             */
/*   Updated: 2022/09/16 15:57:08 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	unset_execute(t_command *c, int in)
{
	int	i;
	
	i = 0;
	execute(c, in, 0);
	if (c->count_cmd > 1)
		while (c->command[++i])
			(terminal())->delete_var(c->command[i]);
	execute(c, in, 1);
}

t_command	*ft_unset(t_command *c)
{
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = unset_execute;
	return (c);
}
