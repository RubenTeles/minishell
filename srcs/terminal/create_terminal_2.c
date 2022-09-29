/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_terminal_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 22:57:46 by rteles            #+#    #+#             */
/*   Updated: 2022/09/29 23:46:08 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	change_shlvl(void)
{
	char	*content;
	int		level;
	int		i;

	content = (terminal())->variable_env("SHLVL");
	level = (string())->str_in_int(content);
	free(content);
	level += 1;
	i = 2;
	if (level < 10)
		i = 3;
	content = malloc(sizeof(char) * i);
	if (!content)
		return ;
	content[i - 1] = '\0';
	if (level < 10)
		content[0] = level + '0';
	else
	{
		content[0] = (level / 10) + '0';
		content[1] = (level % 10) + '0';
	}
	(terminal())->update_var("SHLVL", content);
	free(content);
}

t_env	*create_var_env(char *env)
{
	t_env	*var;

	var = malloc(sizeof(t_env));
	if (!var)
		ft_exit(0);
	var->var = (string())->sub_split_option(env, '=', 0);
	var->val = (string())->sub_split_option(env, '=', 1);
	var->next = 0;
	return (var);
}

void	create_env_l(char **env)
{
	int		i;
	t_env	*aux_env;
	t_env	*var_env;

	i = -1;
	while (env[++i])
	{
		aux_env = create_var_env(env[i]);
		if (!(terminal())->env_l)
			(terminal())->env_l = aux_env;
		else
			var_env->next = aux_env;
		var_env = aux_env;
	}
	(terminal())->env_count = i;
	change_shlvl();
}
