/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_methods_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:53:23 by rteles            #+#    #+#             */
/*   Updated: 2022/09/12 18:23:20 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	__destroy_env_m(void)
{
	int	i;

	i = -1;
	if (!terminal()->env_m)
		return ;
	while (terminal()->env_m[++i])
		free(terminal()->env_m[i]);
	free(terminal()->env_m);
}

static void	__destroy_env_l(void)
{
	t_env	*aux;
	t_env	*aux_2;

	if (!terminal()->env_l)
		return ;
	aux = terminal()->env_l;
	while (aux)
	{
		aux_2 = aux;
		if (aux->next)
			aux = aux->next;
		free(aux_2);
	}
}

static void	__destroy_path(void)
{
	int	i;

	i = -1;
	if (!terminal()->path)
		return ;
	while (terminal()->path[++i])
		free(terminal()->path[i]);
	free(terminal()->path);
}

static void	__destroy_commands(void)
{
	/*int i;

    i = -1;
    if (!terminal()->path)
        return ;
    while (terminal()->path[++i])
		free(terminal()->path[i]);
	free(terminal()->path);*/
}

void	__destroy(void)
{
	terminal()->destroy = malloc(sizeof(t_destroy));
	terminal()->destroy->env_l = __destroy_env_l;
	terminal()->destroy->env_m = __destroy_env_m;
	terminal()->destroy->path = __destroy_path;
	terminal()->destroy->commands = __destroy_commands;
	terminal()->destroy->all = __destroy_all;
}