/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 22:41:55 by rteles            #+#    #+#             */
/*   Updated: 2022/09/29 23:59:17 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	unset_execute(t_command *c, int in)
{
	int	i;

	i = 0;
	if (c->next != NULL && is_redirect_left(c->next->command[0]) > 0)
		in = management_input_execute(c->next);
	if (in == -1)
		return ;
	execute(c, 2);
	if (c->count_cmd > 1)
	{
		while (c->command[++i])
		{
			if (string()->is_alfanumeric(c->command[i]) == 0)
			{
				printf("unset: '%s': not a valid identifier\n", c->command[i]);
				c->exit_status = 1;
			}
			else
				(terminal())->delete_var(c->command[i]);
		}
	}
	execute(c, 1);
}

t_command	*ft_unset(t_command *c)
{
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = unset_execute;
	c->choice = 7;
	return (c);
}
