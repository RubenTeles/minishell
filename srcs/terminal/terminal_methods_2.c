/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_methods_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:06:35 by rteles            #+#    #+#             */
/*   Updated: 2022/09/12 18:25:11 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	add_var_env(char *var)
{
	int		i;
	char	*aux_var;
	char	*aux_val;

	aux_var = string()->sub_split_option(var, '=', 0);
	aux_val = string()->sub_split_option(var, '=', 1);
	if (!aux_var)
		return ;
	i = -1;
	while (terminal()->env_m[++i])
	{
		if (string()->compare_n(aux_var, terminal()->env_m[i],\
			string()->len(aux_var)))
		{
            printf("por fazer");
		}
	}
	i = terminal()->env_count;


	printf("%s\n",aux_var);
	free(aux_var);
}

void	update_var(char *var, char *str)
{
	int		len;
	int		len_var;
	t_env	*aux;
	char	*var_aux;

	aux = terminal()->env_l;
	len = string()->len(var);
	while (aux)
	{
		len_var = string()->len(aux->var);
		if (len_var == len)
			if (string()->compare_n(var, aux->var, len))
			{
				aux->val = string()->replace(aux->val, str);
				return ;
			}
		aux = aux->next;
	}
}

char	*variable_env(char *str)
{
	int		len;
	t_env	*aux;
	char	*var;

	aux = terminal()->env_l;
	len = string()->len(str);
	while (aux)
	{
		if (string()->compare_n(str, aux->var, len))
			return (string()->duplicate(aux->val));
		aux = aux->next;
	}
	return (string()->duplicate(""));
}
