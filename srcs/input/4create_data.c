/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4create_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:26:07 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/06 12:54:28 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	ft_last_token(t_token *temp)
{
	t_token	*start;

	start = temp;
	while (start)
	{
		if ((!fstrcmp("&&", start->token) || !fstrcmp("||", start->token)
				|| !fstrcmp("|", start->token)) && !start->next)
			return (1);
		start = start->next;
	}
	return (0);
}

int	ft_returnpipe(char *token, t_token *temp)
{
	printf("syntax error near unexpected token %s\n", token);
	ft_free_input(temp, 1);
	return (1);
}

int	ft_multipipe(t_token *input)
{
	int		is_pipe;
	t_token	*temp;

	is_pipe = 0;
	temp = input;
	if (!fstrcmp("|", input->token) || !fstrcmp("||", input->token)
		|| !fstrcmp("&&", input->token))
		return (ft_returnpipe(input->token, temp));
	else
	{
		input = input->next;
		while (input != NULL)
		{
			if (!fstrcmp("|", input->token) || !fstrcmp("||", input->token))
				is_pipe++;
			else
				is_pipe = 0;
			if (is_pipe > 1 || ((!fstrcmp("&&", input->token) || !fstrcmp("||",
							input->token) || !fstrcmp("|", input->token))
					&& !input->next))
				return (ft_returnpipe(input->token, temp));
			input = input->next;
		}
	}
	return (0);
}

int	get_comando(char *line, t_data *data)
{
	t_data	*temp;
	t_help	h;

	h.j = 0;
	data->input = ft_split_line(line, 0, NULL, NULL);
	if (ft_multipipe(data->input) || ft_check_parents(data->input))
		return (0);
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

int	ft_get_size_command(char **commands)
{
	int	i;

	i = 0;
	while (commands && commands[i])
		i++;
	return (i);
}
