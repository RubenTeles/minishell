/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_create_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 02:47:31 by rteles            #+#    #+#             */
/*   Updated: 2022/10/10 00:38:14 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_wildcard.h>

char	*ft_ignore_wildcard(char *str)
{
	char		*aux_2;

	if (!str)
		return (str);
	while ((string())->index_char(str, '*') == 0)
	{
		aux_2 = (string())->sub_split_option(str, '*', 0);
		free(str);
		if (aux_2 && (string())->len(aux_2) == 0)
			str = aux_2;
		else
		{
			str = (string())->duplicate(aux_2);
			free(aux_2);
		}
	}
	return (str);
}

char	*wildcard_med(t_wildcard *w, char *sub)
{
	char	**aux_med;
	char	*aux_2;
	int		count;

	count = 0;
	while ((string())->index_char(sub, '*') > 0)
	{
		count++;
		aux_2 = (string())->sub_split_option(sub, '*', 0);
		aux_med = copy_double_string_and_free(w->med, aux_med, 1);
		aux_med[count - 1] = (string())->duplicate(aux_2);
		w->med = copy_double_string_and_free(aux_med, w->med, 0);
		free(aux_2);
		aux_2 = (string())->sub_split_option(sub, '*', 1);
		free(sub);
		aux_2 = ft_ignore_wildcard(aux_2);
		sub = (string())->duplicate(aux_2);
		free(aux_2);
		//printf("Med[%i]:\t%s\n", count - 1, w->med[count - 1]); //Retirar
	}
	return (sub);
}

void	create_wildcard_2(t_wildcard *w, char *wildcard)
{
	char		*aux;

	if ((string())->index_char(wildcard, '*') > 0)
		w->begin = (string())->sub_split_option(wildcard, '*', 0);
	else if (w->next_dir && (string())->index_char(wildcard, '*') == -1)
		w->begin = (string())->duplicate(wildcard);
	aux = (string())->sub_split_option(wildcard, '*', 1);
	aux = ft_ignore_wildcard(aux);
	aux = wildcard_med(w, aux);
	if (aux && (string())->index_char(aux, '*') == -1)
	{
		if (aux && (string())->len(aux) > 0)
			w->final = (string())->duplicate(aux);
		if (aux)
			free(aux);
		if ((string())->index_char(wildcard, '*') == 0 && !w->final
			&& !w->begin && !w->med)
			w->all = 1;
	}
}

static void	new_wildcard(t_wildcard	*w, int dir)
{
	w->begin = NULL;
	w->med = NULL;
	w->final = NULL;
	w->in_dir = dir;
	w->next_dir = NULL;
	w->all = 0;
}

t_wildcard	*create_wildcard(char *wildcard, int dir)
{
	t_wildcard	*w;
	char		*aux;
	int			i;

	w = malloc(sizeof(t_wildcard));
	if (!w)
		return (NULL);
	new_wildcard(w, dir);
	i = 0;
	while ((string())->index_char(&wildcard[i], '/') == 0)
		i++;
	if ((string())->index_char(wildcard, '/') > 0)
	{
		aux = (string())->sub_split_option(wildcard, '/', 1);
		w->next_dir = create_wildcard(aux, dir + 1);
		free(aux);
		aux = (string())->sub_split_option(wildcard, '/', 0);
		create_wildcard_2(w, aux);
		free(aux);
	}
	else
		create_wildcard_2(w, wildcard);
	return (w);
}
