/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2create_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:07:51 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/06 16:59:25 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*ft_return_token(const char *line, int *idx, t_help *h)
{
	h->aux = NULL;
	h->aux = malloc(sizeof(char) * h->j + 1);
	if (!h->aux)
		return (NULL);
	h->aux[h->j] = '\0';
	h->i = h->j;
	while (--(h->j) >= 0 && line[*idx + h->j])
		h->aux[h->j] = line[*idx + h->j];
	*idx = h->i + *idx;
	return (h->aux);
}

int	ft_check_pipe(const char *line, int *idx, int *j)
{
	if ((*j) == 0 && (line[(*idx)] == '>' || line[(*idx)] == '<' || line[(*idx)]
			== '|' || line[(*idx)] == '&' || line[(*idx) + (*j)] == '(' || line
			[(*idx) + (*j)] == ')') && ++(*j))
	{
		if (line[(*idx)] == '(' || line[(*idx)] == ')')
			return (0);
		if (line[(*idx)] == line[(*idx) + (*j)] && (*j)++)
			return (0);
	}
	else if ((line[(*idx) + (*j)] == '>' || line[(*idx) + (*j)] == '<' || line
			[(*idx) + (*j)] == '|' || line[(*idx) + (*j)] == '&' || line[(*idx)
				+ (*j)] == '(' || line[(*idx) + (*j)] == ')'))
		return (0);
	else if (line[*idx + *j] != ' ' )
		return (1);
	return (0);
}

char	*ft_get_command(const char *line, int *idx)
{
	t_help	h;

	h.cote = 0;
	h.j = 0;
	while ((line[*idx + h.j]) && (ft_check_pipe(line, idx, &h.j) || h.cote))
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
	return (ft_return_token(line, idx, &h));
}

/*Função de inicio, percorre um input recebido da função readline, ou seja vai
percorrer a line até chegar ao fim e ierá armazenar todos os objetos **array*/
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
		if (line[i] == ' ')
			i++;
	}
	return (start);
}
