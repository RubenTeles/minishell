/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _update.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 20:57:01 by rteles            #+#    #+#             */
/*   Updated: 2022/09/30 22:18:52 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	__update_env_m(void)
{
	int		i;
	t_env	*aux;
	char	*str;

	(terminal())->destroy->env_m();
	aux = (terminal())->env_l;
	(terminal())->count_env();
	(terminal())->env_m = malloc(sizeof(char *)
			* ((terminal())->env_count + 1));
	i = 0;
	while (aux)
	{
		str = (string())->join(aux->var, "=");
		(terminal())->env_m[i] = (string())->join(str, aux->val);
		free(str);
		aux = aux->next;
		i++;
	}
	(terminal())->env_m[i] = NULL;
}

/* Dá valores ao env_m, export, e ao env_count usando o env do main*/
static void	__update_path(void)
{
	char	*path;

	(terminal())->destroy->path();
	if ((terminal())->var_exist("PATH"))
	{
		path = (terminal())->variable_env("PATH");
		if ((string())->index_char(path, ':') > -1)
			(terminal())->path = (string())->split(path, ':');
		free(path);
	}
}

static void	__update_all(void)
{
	(terminal())->update->env_m();
	(terminal())->update->path();
	(terminal())->update->title();
}

void	__update(void)
{
	(terminal())->update = malloc(sizeof(t_update));
	(terminal())->update->env_m = __update_env_m;
	(terminal())->update->path = __update_path;
	(terminal())->update->title = __update_title;
	(terminal())->update->all = __update_all;
}
