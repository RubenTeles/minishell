/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:42:46 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/12 13:24:42 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

int	ft_istoken(char *token, t_token	*temp, int is_par, int is_token)
{
	if ((is_par < 0) || (is_token && (!fstrcmp("&&", token)
				|| !fstrcmp("||", token) || !fstrcmp("|", token)
				|| !fstrcmp("<", token) || !fstrcmp("<<", token)
				|| !fstrcmp(">", token) || !fstrcmp(">>", token))))
		return (ft_returnpipe(token, temp));
	return (0);
}

void	formate_tokens_main(t_data *data)
{
	int	i;
	int	j;
	int	is_wild;

	j = -1;
	while (data->comando[++j])
	{
		i = -1;
		while (data->comando[j][++i])
		{
			is_wild = ft_iswildcard(data->comando[j][i]);
			data->comando[j][i] = ft_formattoken(data->comando[j][i]);
			if (i && is_wild)
				data->comando[j] = ft_join_wildcard(data->comando[j], &i);
		}
	}
}

int	ft_readline_while_2(t_data *data)
{
	(terminal())->line = ft_check_cotes((terminal())->line);
	data->input = ft_split_line((terminal())->line, 0, NULL, NULL);
	if (!ft_multipipe(data->input) && !ft_check_parents(data->input)
		&& get_comando((terminal())->line, data))
	{
		formate_tokens_main(data);
		(terminal())->execute(data->comando, STDIN_FILENO);
		if ((terminal())->line
			&& !(string())->compare_n((terminal())->line, "", 1))
			add_history((terminal())->line);
		ft_free_data(data, (terminal())->line);
		return (0);
	}
	add_history((terminal())->line);
	free((terminal())->line);
	return (1);
}

void	ft_readline_while(void)
{
	t_data	data;

	while (1)
	{
		(terminal())->line = readline((terminal())->title);
		if (!(terminal())->line
			|| (string())->compare_n((terminal())->line, "exit", 5))
		{
			if ((terminal())->line)
				free((terminal())->line);
			ft_exit(0);
		}
		if ((string())->compare_n((terminal())->line, "", 1)
			|| ft_str_is((terminal())->line, ' ', '\t'))
		{
			free((terminal())->line);
			continue ;
		}
		if (ft_readline_while_2(&data))
			continue ;
	}
}
