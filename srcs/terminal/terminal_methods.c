/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_methods.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:02:33 by rteles            #+#    #+#             */
/*   Updated: 2022/09/01 23:32:43 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int __count_env(void)
{
	int	i;

	i = -1;
	while (terminal()->env_m[++i])
		i++;
	return (i);
}

/* DAR FREE*/
char	*variable_env(char *str)
{
	int		i;
	int		len;
	char	*var;
	char	*aux;

	i = -1;
	aux = 0;
	var = string()->join(str, "=");
	len = string()->len(var);
	//printf("%s \n", var);
	while (terminal()->env_m[++i] && !aux)
		aux = string()->n_str(terminal()->env_m[i], var, len);
	free(var);
	if (!aux)
		return ("");
	return (string()->duplicate(aux));
}
