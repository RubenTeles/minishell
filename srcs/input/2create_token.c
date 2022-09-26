/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:07:51 by ede-alme          #+#    #+#             */
/*   Updated: 2022/09/25 23:08:57 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*ft_get_command(const char *line, int *idx)
{
	char	*out;
	t_help	h;

	h.cote = 0;
	h.j = 0;
	while ((line[*idx + h.j]) && (line[*idx + h.j] != ' ' || h.cote))
	{
		if (line[*idx + h.j] == '\\' && (!h.cote || h.cote == '"')
			&& line[*idx + h.j + 1] && ++h.j)
			h.j++;
		else if (!h.cote && (line[*idx + h.j] == 34 || line[*idx + h.j] == 39))
			h.cote = line[*idx + h.j++];
		else if (h.cote && line[*idx + h.j] == h.cote && h.j++)
			h.cote = 0;
		else
			h.j++;
	}
	out = malloc(sizeof(char) * h.j + 1);
	out[h.j] = '\0';
	h.i = h.j;
	while (--h.j >= 0 && line[*idx + h.j])
		out[h.j] = line[*idx + h.j];
	*idx = h.i + *idx;
	return (out);
}

//Função de inicio, percorre um input recebido da função readline, ou seja vai percorrer a line até chegar ao fim e ierá armaznar todos os objetos num **array...
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