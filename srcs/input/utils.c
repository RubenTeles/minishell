/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:35:27 by ede-alme          #+#    #+#             */
/*   Updated: 2022/09/28 12:58:39 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	fstrcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1 && s2 && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

char	*ft_exit_status(char *aux, int *j)
{
	char	*value;
	char	*auxvar;

	value = (string())->duplicate("Value");
	(*j) += (string())->len(value);
	if (aux && aux[0])
		auxvar = (string())->join(aux, value);
	else
		return (value);
	free(aux);
	return (auxvar);
}

int	ft_str_is(char *line, char c)
{
	int	i;

	i = 0;
	while (line && line[i] && line[i] == c)
		i++;
	if (line && line[i])
		return (0);
	return (1);
}
