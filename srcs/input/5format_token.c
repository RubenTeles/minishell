/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5format_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:15:52 by ede-alme          #+#    #+#             */
/*   Updated: 2022/09/26 21:58:29 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*ft_putvar(char *token, int *i, char *aux, int *j)
{
	int		index;
	int		temp;
	char	*var;
	char	*auxvar;
	char	*value;

	index = 0;
	while (token[(*i) + index] && isalnum(token[(*i) + index]))
		index++;
	var = malloc(sizeof(char) * index + 1);
	temp = (*i) + index;
	var[index] = '\0';
	while (--index >= 0)
		var[index] = token[(*i) + index];
	(*i) = temp;
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
		else if (token[(*i)] == '$' && token[(*i)] == '$' && token[(*i) + 1]
			&& isalnum(token[(*i) + 1]) && ++(*i))
			aux = ft_putvar(token, i, aux, j);
		else if (++(*j))
			aux = ft_new_aux(aux, token[(*i)++]);
	}
	return (aux);
}

char	*ft_formattoken(char *tk)
{
	char	*aux;
	t_help	h;

	h.i = 0;
	h.j = 0;
	h.cote = 0;
	aux = NULL;
	while (tk && tk[h.i])
	{
		if (tk[h.i] == '$' && tk[h.i + 1] && isalnum(tk[h.i + 1]) && ++(h.i))
			aux = ft_putvar(tk, &(h.i), aux, &(h.j));
		else if (tk[h.i] == '\'' && ++(h.i))
			aux = ft_formatsimple(aux, tk, &(h.i), &(h.j));
		else if (tk[h.i] == '"' && ++(h.i))
			aux = ft_formatdouble(aux, tk, &(h.i), &(h.j));
		else if (tk[h.i] == '\\' && (!tk[h.i + 1] || (tk[h.i + 1]
					&& tk[h.i + 1])) && ++(h.i) && tk[(h.i)] && ++(h.j))
			aux = ft_new_aux(aux, tk[(h.i)++]);
		else if (++(h.j))
			aux = ft_new_aux(aux, tk[(h.i)++]);
	}
	if (!aux && ++(h.j))
		aux = ft_new_aux(aux, tk[(h.i)]);
	free (tk);
	return (aux);
}
