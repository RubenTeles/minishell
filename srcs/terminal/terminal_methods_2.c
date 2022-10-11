/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_methods_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:06:35 by rteles            #+#    #+#             */
/*   Updated: 2022/10/11 21:17:33 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	add_var(char *var)
{
	t_env	*aux;
	t_env	*var_env;

	aux = (terminal())->env_l;
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

	if (!var)
		return ;
	aux_var = (string())->sub_split_option(var, '=', 0);
	aux_val = (string())->sub_split_option(var, '=', 1);
	if ((terminal())->var_exist(aux_var) > 0)
	{
		if (aux_val != NULL)
			(terminal())->update_var(aux_var, aux_val);
	}
	else
		add_var(var);
	free(aux_var);
	free(aux_val);
	(terminal())->update->all();
}

void	update_var(char *var, char *str)
{
	t_env	*aux;

	aux = (terminal())->env_l;
	while (aux)
	{
		if ((string())->compare(var, aux->var))
		{
			if (str)
				aux->val = (string())->replace(aux->val, str);
			else
			{
				free(aux->val);
				aux->val = NULL;
			}
			return ;
		}
		aux = aux->next;
	}
	(terminal())->update->all();
}

void	delete_var_2(char *var_env)
{
	t_env	*aux;
	t_env	*previus;

	previus = NULL;
	aux = (terminal())->env_l;
	while (aux)
	{
		if ((string())->len(aux->var) == (string())->len(var_env))
			if ((string())->compare_n(aux->var, var_env,
					(string())->len(aux->var)))
				break ;
		previus = aux;
		aux = aux->next;
	}
	if ((string())->compare_n(aux->var, var_env, (string())->len(aux->var)))
		previus->next = aux->next;
	else
		(terminal())->env_l->next = aux->next;
	free(aux->var);
	free(aux->val);
	free(aux);
}

void	delete_var(char	*var)
{
	char	*var_env;

	if (!var)
		return ;
	var_env = (string())->sub_split_option(var, '=', 0);
	if ((terminal())->var_exist(var_env) == 0)
	{
		free(var_env);
		return ;
	}
	delete_var_2(var_env);
	free(var_env);
	(terminal())->update->all();
}
