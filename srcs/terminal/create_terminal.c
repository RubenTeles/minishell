/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_terminal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:37:10 by rteles            #+#    #+#             */
/*   Updated: 2022/09/30 22:03:40 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	__destroy_title(void)
{
	if (!(terminal())->title)
		return ;
	free((terminal())->title);
}

void	__destroy_all(void)
{
	(terminal())->destroy->title();
	if ((terminal())->var_exist("PATH"))
		(terminal())->destroy->path();
	(terminal())->destroy->commands();
	(terminal())->destroy->env_m();
	(terminal())->destroy->env_l();
	free((terminal())->update);
	free((terminal())->destroy);
	rl_clear_history();
}

void	new_terminal(char **env)
{
	(terminal())->env_l = NULL;
	(terminal())->env_m = NULL;
	(terminal())->env_count = 0;
	(terminal())->last_exit = 0;
	(terminal())->path = NULL;
	(terminal())->line = NULL;
	(terminal())->start = NULL;
	(terminal())->count_env = __count_env;
	(terminal())->variable_env = variable_env;
	(terminal())->add_var = add_var_if_exist;
	(terminal())->update_var = update_var;
	(terminal())->delete_var = delete_var;
	(terminal())->execute = ft_command_execute;
	(terminal())->var_exist = var_exist;
	__update();
	__destroy();
	create_env_l(env);
	(terminal())->update->all();
}

t_terminal	*terminal(void)
{
	static t_terminal	t;

	return (&t);
}
