/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4create_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:26:07 by ede-alme          #+#    #+#             */
/*   Updated: 2022/09/28 12:51:38 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	get_comando(char *line, t_data *data)
{
	t_data	*temp;
	int		i;
	int		j;

	i = -1;
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
		while ((++i + 1) && data->comando && data->comando[j]
			&& data->start->commands && data->start->commands[i])
			data->comando[j][i] = data->start->commands[i];
		data->comando[j][i] = NULL;
		data->start = ft_free_start(data->start);
		i = -1;
		j++;
	}
	data->comando[j] = NULL;
}
