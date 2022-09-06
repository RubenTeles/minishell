/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_terminal_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 22:57:46 by rteles            #+#    #+#             */
/*   Updated: 2022/09/07 00:35:06 by rteles           ###   ########.fr       */
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
	terminal()->replace_var("SHLVL", content);
	free(content);
}

static char	*create_export(char *var)
{
	int	i;
	char	*name_var;
	char	*variable;
	char	*str;

	i = string()->index_char(var, '=');
	name_var = malloc(sizeof(char) * i + 3);
	string()->copy_n(name_var, var, i + 2);
	str = string()->duplicate(string()->n_str(var, name_var, i + 2));
	name_var[i + 1] = '\"';
	name_var[i + 2] = '\0';
	variable = string()->join(str, "\"\0");
	free(str);
	str = string()->join(name_var, variable);
	free(name_var);
	free(variable);
	variable = string()->join("declare -x ", str);
	free(str);
	return (variable);
}

void	create_env(char **env)
{
	int	i;
	int	aux;

	i = -1;
	while (env[++i])
	{
		aux = ft_strlen(env[i]);
		terminal()->env_m[i] = malloc(sizeof(char) * aux + 1);
		ft_strlcpy(terminal()->env_m[i], env[i], aux + 1);
		terminal()->export[i] = create_export(env[i]);
	}
	terminal()->env_m[i] = malloc(sizeof(char) * 1);
	terminal()->env_m[i] = NULL;
	terminal()->export[i] = malloc(sizeof(char) * 1);
	terminal()->export[i] = NULL;
	change_shlvl();
}
