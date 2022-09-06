/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:16:06 by ede-alme          #+#    #+#             */
/*   Updated: 2022/09/06 13:23:53 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*ft_get_command(const char *line, int *i)
{
	char	*out;
	int		len;
	int		new_i;
	int		ignore;

	ignore = 0;
	len = 0;
	while ((line[*i + len]) && (line[*i + len] != ' ' || ignore))
	{
		if (line[*i + len] == '\"' || line[*i + len] == '\'')
			ignore = !ignore;
		if (line[*i + len] == ignore && len++)
			break ;
		len++;
	}
	out = malloc(sizeof(char) * len + 1);
	out[len] = '\0';
	new_i = len;
	while (--len >= 0 && line[*i + len])
		out[len] = line[*i + len];
	*i = new_i + *i;
	return (out);
}

t_token	*ft_split_line(const char *line, int i, t_token	*start, t_token	*end)
{
	t_token	*aux;

	while (line[i] != '\0')
	{
		if (line[i] != '\t' && line[i] != ' ')
		{
			aux = malloc(sizeof(t_token));
			aux->next = NULL;
			aux->token = ft_get_command(line, &i);
			if (start == NULL)
				start = aux;
			else
				end->next = aux;
			end = aux;
		}
		if (!line[i])
			break ;
		i++;
	}
	return (start);
}
