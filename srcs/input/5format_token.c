/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5format_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:15:52 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/04 21:32:03 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*ft_putvar(char *token, int *i, char *aux, int *j)
{
	t_help	h;
	char	*var;
	char	*auxvar;
	char	*value;

	h.i = 0;
	if (token[(*i) + h.i] == '?' && ++(*i))
		return (ft_exit_status(aux, j));
	while (token[(*i) + h.i] && fisalnum(token[(*i) + h.i]))
		h.i++;
	var = malloc(sizeof(char) * h.i + 1);
	h.j = (*i) + h.i;
	var[h.i] = '\0';
	while (--h.i >= 0)
		var[h.i] = token[(*i) + h.i];
	(*i) = h.j;
	value = (terminal())->variable_env(var);
	free (var);
	auxvar = (string())->join(aux, value);
	if (!auxvar)
		auxvar = (string())->duplicate(value);
	(*j) = (*j) + (string())->len(value);
	free(value);
	free (aux);
	return (auxvar);
}

char	*ft_new_aux(char *aux, char index)
{
	char	*temp;
	int		i;

	i = 0;
	temp = aux;
	while (aux && aux[i])
		i++;
	aux = malloc(sizeof(char) * i + 1 + 1);
	i = 0;
	if (!aux)
		return (temp);
	while (temp && temp[i])
	{
		aux[i] = temp[i];
		i++;
	}
	if (temp)
		free (temp);
	if (aux)
		aux[i] = index;
	aux[i + 1] = '\0';
	return (aux);
}

char	*ft_formatsimple(char *aux, char *token, int *i, int *j)
{
	while (token && token[*i])
	{
		if (token[*i] == '\'' && ++(*i))
			break ;
		else if (++(*j))
			aux = ft_new_aux(aux, token[(*i)++]);
	}
	return (aux);
}

char	*ft_formatdouble(char *aux, char *token, int *i, int *j)
{
	while (token && token[(*i)])
	{
		if (token[(*i)] == '\"' && ++(*i))
			break ;
		if (token[(*i)] == '\\' && token[(*i) + 1] && (token[(*i) + 1] == '$'
				|| token[(*i) + 1] == '"' || token[(*i) + 1] == '\\') && ++(*i)
			&& ++(*j))
			aux = ft_new_aux(aux, token[(*i)++]);
		else if (token[(*i)] == '$' && token[(*i) + 1]
			&& (fisalnum(token[(*i) + 1])
				|| token[(*i) + 1] == '?') && ++(*i))
			aux = ft_putvar(token, i, aux, j);
		else if (++(*j))
			aux = ft_new_aux(aux, token[(*i)++]);
	}
	return (aux);
}

char	*ft_formattoken(char *tk)
{
	t_help	h;

	h.i = 0;
	h.j = 0;
	h.cote = 0;
	h.aux = NULL;
	while (tk && tk[h.i])
	{
		if (tk[h.i] == '$' && tk[h.i + 1]
			&& (fisalnum(tk[h.i + 1]) || tk[h.i + 1] == '?') && ++h.i)
			h.aux = ft_putvar(tk, &(h.i), h.aux, &(h.j));
		else if (tk[h.i] == '\'' && ++(h.i))
			h.aux = ft_formatsimple(h.aux, tk, &(h.i), &(h.j));
		else if (tk[h.i] == '"' && ++(h.i))
			h.aux = ft_formatdouble(h.aux, tk, &(h.i), &(h.j));
		else if (tk[h.i] == '\\' && (!tk[h.i + 1] || (tk[h.i + 1]
					&& tk[h.i + 1])) && ++(h.i) && tk[(h.i)] && ++(h.j))
			h.aux = ft_new_aux(h.aux, tk[(h.i)++]);
		else if (++(h.j))
			h.aux = ft_new_aux(h.aux, tk[(h.i)++]);
	}
	if (!h.aux && ++(h.j))
		h.aux = ft_new_aux(h.aux, tk[(h.i)]);
	free (tk);
	return (h.aux);
}
