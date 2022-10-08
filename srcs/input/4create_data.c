/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4create_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:26:07 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/08 19:01:56 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	ft_check_parents(t_token *input)
{
	int		is_par;
	char	*last_token;
	t_token	*temp;

	is_par = 0;
	temp = input;
	last_token = NULL;
	while (input)
	{
		if (is_par < 0 || (!fstrcmp(")", input->token) && (!fstrcmp("(",
						last_token))) || (!fstrcmp("(", last_token)
				&& ((!fstrcmp("&&", input->token) || !fstrcmp("||", input->token
						) || !fstrcmp("|", input->token) || !fstrcmp("<",
							input->token) || !fstrcmp("<<", input->token)))))
			return (ft_returnpipe(input->token, temp));
		if (!fstrcmp("(", input->token))
				is_par++;
		if (!fstrcmp(")", input->token))
				is_par--;
		last_token = input->token;
		input = input->next;
	}
	if (is_par != 0)
		return (ft_returnpipe(last_token, temp));
	return (0);
}

int	ft_returnpipe(char *token, t_token *temp)
{
	if (token)
		printf("syntax error near unexpected token `%s´\n", token);
	ft_free_input(temp, 1);
	return (1);
}

int	ft_multipipe(t_token *input)
{
	int		is_pipe;
	int		is_token;
	int		or_and;
	t_token	*temp;

	is_pipe = 0;
	is_token = 0;
	or_and = 0;
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
			if (!fstrcmp(">>", input->token) || !fstrcmp(">", input->token) || !fstrcmp("<", input->token) || !fstrcmp("<<", input->token))
				is_token++;
			else
				is_token = 0;
			if (!fstrcmp("&&", input->token) || !fstrcmp("||", input->token))
				or_and++;
			else
				or_and = 0;
			if (is_token > 1 || or_and > 1 || is_pipe > 1 || ((!fstrcmp("&&", input->token) || !fstrcmp("||", input->token) || !fstrcmp("|", input->token)) && !input->next))
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

int	ft_get_size_command(char **commands)
{
	int	i;

	i = 0;
	while (commands && commands[i])
		i++;
	return (i);
}
