/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_methods.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:02:33 by rteles            #+#    #+#             */
/*   Updated: 2022/09/30 22:24:15 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	__count_env(void)
{
	int		i;
	t_env	*aux;

	aux = (terminal())->env_l;
	i = 0;
	while (aux)
	{
		aux = aux->next;
		i++;
	}
	(terminal())->env_count = i;
}

int	var_exist(char *str)
{
	int		len;
	t_env	*aux;

	aux = (terminal())->env_l;
	len = (string())->len(str);
	while (aux)
	{
		if ((string())->compare_n(str, aux->var, len))
		{
			if (aux->val)
				return (1);
			return (2);
		}
		aux = aux->next;
	}
	return (0);
}

char	*variable_env(char *str)
{
	int		len;
	t_env	*aux;
	int		aux_len;

	aux = (terminal())->env_l;
	len = (string())->len(str);
	while (aux)
	{
		aux_len = (string())->len(aux->var);
		if (len == aux_len && (string())->compare_n(str, aux->var, len))
		{
			if (aux->val)
				return ((string())->duplicate(aux->val));
			return (0);
		}
		aux = aux->next;
	}
	return ((string())->duplicate(""));
}

/*Retorna o path com o comando certo*/
char	*path_command(char *command)
{
	char	*aux_path;
	int		i;

	i = -1;
	aux_path = 0;
	if (!(terminal())->var_exist("PATH") || !(terminal())->path)
		return (0);
	while ((terminal())->path[++i])
	{
		aux_path = string()->join((terminal())->path[i], command);
		if (!access(aux_path, F_OK))
			return (aux_path);
		free(aux_path);
	}
	aux_path = 0;
	return (aux_path);
}
