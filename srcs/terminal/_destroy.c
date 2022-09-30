/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _destroy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:53:23 by rteles            #+#    #+#             */
/*   Updated: 2022/09/30 22:19:40 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	__destroy_env_m(void)
{
	int	i;

	i = -1;
	if (!(terminal())->env_m)
		return ;
	while ((terminal())->env_m[++i])
		free((terminal())->env_m[i]);
	free((terminal())->env_m[i]);
	free((terminal())->env_m);
}

static void	__destroy_env_l(void)
{
	t_env	*aux;
	t_env	*aux_2;

	if (!(terminal())->env_l)
		return ;
	aux = (terminal())->env_l;
	while (aux)
	{
		aux_2 = aux;
		aux = aux->next;
		free(aux_2->var);
		free(aux_2->val);
		free(aux_2);
	}
}

static void	__destroy_path(void)
{
	int	i;

	i = -1;
	if (!(terminal())->path)
		return ;
	while ((terminal())->path[++i])
		free((terminal())->path[i]);
	free((terminal())->path);
	(terminal())->path = NULL;
}

static void	__destroy_commands(void)
{
	t_command	*aux;
	t_command	*aux_2;

	if (!(terminal())->start)
		return ;
	aux = (terminal())->start;
	while (aux)
	{
		aux_2 = aux;
		aux = aux->next;
		if (aux_2->path)
			free(aux_2->path);
		free(aux_2);
	}
	(terminal())->start = NULL;
}

void	__destroy(void)
{
	(terminal())->destroy = malloc(sizeof(t_destroy));
	(terminal())->destroy->env_l = __destroy_env_l;
	(terminal())->destroy->env_m = __destroy_env_m;
	(terminal())->destroy->path = __destroy_path;
	(terminal())->destroy->title = __destroy_title;
	(terminal())->destroy->commands = __destroy_commands;
	(terminal())->destroy->all = __destroy_all;
}
