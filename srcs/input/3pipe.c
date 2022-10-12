/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3pipe.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:26:07 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/12 13:24:57 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	ft_check_parents(t_token *input)
{
	t_help	h;

	h.i = 0;
	h.temp = input;
	h.j = 0;
	while (input)
	{
		if (ft_istoken(input->token, h.temp, h.i, h.j))
			return (1);
		if (!fstrcmp("(", input->token))
				h.i++;
		if (!fstrcmp(")", input->token))
				h.i--;
		if (((!fstrcmp("&&", input->token) || !fstrcmp("||", input->token)
					|| !fstrcmp("|", input->token) || !fstrcmp("<", input
						->token) || !fstrcmp("<<", input->token) || !fstrcmp(">"
						, input->token) || !fstrcmp(">>", input->token))))
			h.j = 1;
		else
			h.j = 0;
		input = input->next;
	}
	if (h.i != 0)
		return (ft_returnpipe(input->token, h.temp));
	return (0);
}

int	ft_pipeerror(t_token *input, t_token *temp, int is_token)
{
	int		or_and;

	or_and = 0;
	while (input != NULL)
	{
		if (!fstrcmp(">>", input->token) || !fstrcmp(">", input->token)
			|| !fstrcmp("<", input->token) || !fstrcmp("<<", input->token)
			|| !fstrcmp("|", input->token) || !fstrcmp("||", input->token)
			|| !fstrcmp("&&", input->token))
			is_token++;
		else
			is_token = 0;
		if (!fstrcmp("&&", input->token) || !fstrcmp("||", input->token))
			or_and++;
		else
			or_and = 0;
		if ((is_token > 1 || or_and > 1) || ((!fstrcmp("&&", input
						->token) || !fstrcmp("||", input->token)
					|| !fstrcmp("|", input->token)) && !input->next))
			return (ft_returnpipe(input->token, temp));
		input = input->next;
	}
	return (0);
}

int	ft_multipipe(t_token *input)
{
	t_token	*temp;
	int		is_token;

	is_token = 0;
	temp = input;
	if (!fstrcmp("|", input->token) || !fstrcmp("||", input->token)
		|| !fstrcmp("&&", input->token))
		return (ft_returnpipe(input->token, temp));
	else
	{
		input = input->next;
		if (ft_pipeerror(input, temp, is_token))
			return (1);
	}
	return (0);
}

int	ft_get_size_command(char **commands)
{
	int	i;

	i = 0;
	while (commands && commands[i])
		i++;
	return (i);
}

int	get_comando(char *line, t_data *data)
{
	t_data	*temp;
	t_help	h;

	h.j = 0;
	if (data->input == NULL)
		data->input = ft_split_line(line, 0, NULL, NULL);
	data->start = ft_parameters(data->input, NULL, NULL);
	temp = data;
	ft_malloc_comando(&data, *temp);
	while (data->start)
	{
		h.i = -1;
		if (data->start->commands && data->start->commands[0])
			data->comando[h.j] = malloc(sizeof(char *)
					* (ft_get_size_command(data->start->commands) + 1));
		while ((++(h.i) + 1) && data->comando && data->comando[h.j]
			&& data->start->commands && data->start->commands[h.i])
			data->comando[h.j][h.i] = data->start->commands[h.i];
		data->comando[h.j][h.i] = NULL;
		data->start = ft_free_start(data->start);
		(h.j)++;
	}
	data->comando[h.j] = NULL;
	return (1);
}
