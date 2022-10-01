/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6free_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:18:49 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/01 20:16:07 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_cms	*ft_free_start(t_cms *start)
{
	t_cms	*temp;

	temp = start->next;
	free(start->commands);
	free(start);
	return (temp);
}

void	ft_free_input(t_token *input)
{
	if (input)
	{
		ft_free_input(input->next);
		free(input);
	}
}

void	ft_free_data(t_data *data, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->comando[j])
	{
		while (data->comando[j][i])
			free(data->comando[j][i++]);
		free(data->comando[j]);
		i = 0;
		j++;
	}
	if (data->input)
		ft_free_input(data->input);
	if (data->comando)
		free(data->comando);
	if (line)
		free(line);
}
