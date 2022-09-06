/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_methods.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:02:33 by rteles            #+#    #+#             */
/*   Updated: 2022/09/06 16:07:39 by rteles           ###   ########.fr       */
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

void	replace_var(char *var, char *str)
{
	char	*aux;
	char	*var2;
	int		i;

	i = index_var(var);
	if (i < -1)
		return ;
	printf("%s \n", terminal()->env_m[i]);
	var2 = string()->join(var, "=");
	aux = string()->replace(terminal()->env_m[i], str);
	terminal()->env_m[i] = string()->join(var2, aux);
	free(aux);
	free(var2);
	printf("%s \n", terminal()->env_m[i]);
}