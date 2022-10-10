/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_validation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 02:45:03 by rteles            #+#    #+#             */
/*   Updated: 2022/10/10 18:43:56 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_wildcard.h>

int	ft_valid_start(char *str, char *start)
{
	int	len;
	int	i;

	i = 0;
	len = (string())->len(start);
	while (len > i && str[i] && start[i] && (str[i] == start[i]))
		i++;
	if (i == len)
		return (i);
	return (0);
}

int	ft_valid_med(char *str, char *med, int i)
{
	int	a;
	int	len;
	int	start;

	start = i;
	a = 0;
	len = (string())->len(med);
	if (!str || !med)
		return (0);
	while (med[a] && str[i + a] && (med[a] == str[i + a]))
		a++;
	while (med[a] && str[i] && (med[a] != str[i]))
	{
		i++;
		a = 0;
		while (med[a] && str[i + a] && (med[a] == str[i + a]))
			a++;
	}
	if (a == len)
		return (i + a - 1);
	return (start);
}

int	ft_valid_final(char *str, char *final)
{
	int	len;
	int	i;

	i = 0;
	len = (string())->len(str) - (string())->len(final);
	while (str[len + i] && final[i] && (str[len + i] == final[i]))
		i++;
	if (str[len + i] == final[i])
		return (1);
	return (0);
}

int	ft_valid(t_wildcard *w, char *str, int i, int aux)
{
	int	a;

	if (w->word)
		return ((string())->compare(str, w->word));
	if (w->begin)
	{
		aux = ft_valid_start(str, w->begin);
		if ((aux - i) == 0)
			return (0);
		i = aux;
	}
	if (w->med)
	{
		a = -1;
		while (w->med[++a])
		{
			aux = ft_valid_med(str, w->med[a], i);
			if ((aux - i) == 0)
				return (0);
			i = aux;
		}
	}
	if (w->final && !ft_valid_final(str, w->final))
		return (0);
	return (1);
}
