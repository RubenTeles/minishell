/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_methods_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:06:35 by rteles            #+#    #+#             */
/*   Updated: 2022/09/13 03:54:32 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	add_var(char *var)
{
	t_env	*aux;
	t_env	*var_env;

	aux = terminal()->env_l;
	while (aux)
	{
		var_env = aux;
		aux = aux->next;
	}
	var_env->next = create_var_env(var);
}

void	add_var_if_exist(char *var)
{
	char	*aux_var;
	char	*aux_val;

	if (!aux_var)
		return ;
	aux_var = string()->sub_split_option(var, '=', 0);
	aux_val = string()->sub_split_option(var, '=', 1);
	if (terminal()->var_exist(aux_var) > 0)
	{
		if (aux_val != NULL)
			terminal()->update_var(aux_var, aux_val);
	}
	else
		add_var(var);
	free(aux_var);
	free(aux_val);
	terminal()->update->all();
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
	terminal()->update->all();
}

void	delete_var(char	*var)
{
	t_env	*aux;
	t_env	*previus;
	char	*aux_var;
	char	*aux_val;

	if (!aux_var)
		return ;
	aux_var = string()->sub_split_option(var, '=', 0);
	aux_val = string()->sub_split_option(var, '=', 1);
	if (terminal()->var_exist(aux_var) == 0)
		return ;
	aux = terminal()->env_l;
	previus = NULL;
	while (aux)
	{
		if (string()->compare_n(aux_var, aux->var, string()->len(aux->var)));
			break;
		previus = aux;
		aux = aux->next;
	}
	if (string()->compare_n(aux_var, aux->var, string()->len(aux->var)) && previus)
		previus->next = aux->next;
	else
		terminal()->env_l->next = aux->next;
	free(aux->val);
	free(aux->var);
	free(aux);
	free(aux_var);
	free(aux_val);
	terminal()->update->all();
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
		{
			if (aux->val)
				return (string()->duplicate(aux->val));
			return (0);
		}
		aux = aux->next;
	}
	return (string()->duplicate(""));
}
