/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_create_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 02:47:31 by rteles            #+#    #+#             */
/*   Updated: 2022/10/08 21:53:00 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_wildcard.h>

void	wildcard_med(t_wildcard *w, char *sub)
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
		sub = (string())->duplicate(aux_2);
		free(aux_2);
		printf("Med[%i]:\t%s\n", count - 1, w->med[count - 1]);
	}
}

void	create_wildcard_2(t_wildcard *w, char *wildcard)
{
	char		*aux;
	int			i;

	if ((string())->index_char(wildcard, '*') > 0)
		w->begin = (string())->sub_split_option(wildcard, '*', 0);
	else if (w->next_dir && (string())->index_char(wildcard, '*') == -1)
		w->begin = (string())->duplicate(wildcard);
	aux = (string())->sub_split_option(wildcard, '*', 1);
	i = 0;
	while ((string())->index_char(&aux[i], '*') == 0)
		i++;
	wildcard_med(w, &aux[i]);
	if (aux && (string())->index_char(&aux[i], '*') == -1)
	{
		if (&aux[i] && (string())->len(&aux[i]) > 0)
			w->final = (string())->duplicate(&aux[i]);
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
