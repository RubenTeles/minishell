/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_terminal_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 22:57:46 by rteles            #+#    #+#             */
/*   Updated: 2022/09/12 18:28:28 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_atoi(char *str)
{
	int			i;
	int			s;
	long long	n;

	i = 0;
	s = 1;
	n = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		if (n * s > 2147483647)
			return (-1);
		else if (n * s < -2147483648)
			return (0);
		i++;
	}
	return (n * s);
}

static void	change_shlvl(void)
{
	char	*content;
	int		level;
	int		i;

	content = terminal()->variable_env("SHLVL");
	level = ft_atoi(content);
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
	terminal()->update_var("SHLVL", content);
	free(content);
}

t_env	*create_var_env(char *env)
{
	t_env	*var;

	var = malloc(sizeof(t_env));
	var->var = string()->sub_split_option(env, '=', 0);
	var->val = string()->sub_split_option(env, '=', 1);
	var->next = 0;
	return (var);
}

void	create_env_m(void)
{
	int		i;
	t_env	*aux;
	char	*str;

	terminal()->destroy->env_m();
	aux = terminal()->env_l;
	terminal()->count_env();
	terminal()->env_m = malloc(sizeof(char *) * terminal()->env_count + 1);
	i = 0;
	while (aux)
	{
		str = string()->join(aux->var, "=");
		terminal()->env_m[i] = string()->join(str, aux->val);
		free(str);
		aux = aux->next;
		i++;
	}
	terminal()->env_m[i] = malloc(sizeof(char) * 1);
	terminal()->env_m[i] = NULL;
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
		if (!terminal()->env_l)
			terminal()->env_l = aux_env;
		else
			var_env->next = aux_env;
		var_env = aux_env;
	}
	terminal()->env_count = i;
	change_shlvl();
	create_env_m();
	//add_var_env("Comida");
}
