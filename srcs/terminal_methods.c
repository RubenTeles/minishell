/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_methods.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:02:33 by rteles            #+#    #+#             */
/*   Updated: 2022/08/20 20:26:51 by rteles           ###   ########.fr       */
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

int	is_variable_env(char *var)
{
	int		i;
	char	*aux;

	i = -1;
	aux = 0;
	printf("%s \n", var);
	/*aux = string()->duplicate(string()->pos_char(var, '$'));

	string()->split(var, '.');
	while (terminal()->env_m[++i])
	{
		path = ft_strnstr(env_m[i], "PATH=", 6);
	}

*/
	return (0);
}
