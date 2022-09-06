/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:21:28 by ede-alme          #+#    #+#             */
/*   Updated: 2022/09/06 13:23:58 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	ft_get_size_command(char **commands)
{
	int	i;

	i = 0;
	while (commands && commands[i])
		i++;
	return (i);
}

void	ft_malloc_comando(t_data **data, t_data temp)
{
	int	i;

	i = 0;
	while (temp.start)
	{
		temp.start = temp.start->next;
		i++;
	}
	(*data)->comando = malloc(sizeof(char **) * (i + 1));
	(*data)->comando[i] = NULL;
}

void	get_comando(char *line, t_data *data)
{
	t_data	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	data->input = ft_split_line(line, 0, NULL, NULL);
	data->start = ft_parameters(data->input, NULL, NULL);
	temp = data;
	ft_malloc_comando(&data, *temp);
	while (data->start)
	{
		if (data->start->commands && data->start->commands[0])
			data->comando[j] = malloc(sizeof(char *)
					* (ft_get_size_command(data->start->commands) + 1));
		while (data->comando && data->comando[j]
			&& data->start->commands && data->start->commands[i])
			data->comando[j][i++] = data->start->commands[i];
		data->comando[j][i] = NULL;
		data->start = data->start->next;
		i = 0;
		j++;
	}
	data->comando[j] = NULL;
}
