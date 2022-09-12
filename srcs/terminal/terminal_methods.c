/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_methods.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:02:33 by rteles            #+#    #+#             */
/*   Updated: 2022/09/12 18:15:48 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void __count_env(void)
{
	int		i;
	t_env	*aux;

	aux = terminal()->env_l;
	i = 0;
	while (aux)
	{
		aux = aux->next;
		i++;
	}
	terminal()->env_count = i;
}

/* DAR FREE*/
int	index_var(char *str)
{
	int		i;
	int		len;
	char	*var;
	char	*aux;

	i = -1;
	aux = 0;
	var = string()->join(str, "=");
	len = string()->len(var);
	while (!aux && terminal()->env_m[++i])
		aux = string()->n_str(terminal()->env_m[i], var, len);
	free(var);
	if (!aux)
		return (-1);
	return (i);
}

