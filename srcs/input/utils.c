/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:35:27 by ede-alme          #+#    #+#             */
/*   Updated: 2022/09/30 18:39:26 by rteles           ###   ########.fr       */
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

	value = (string())->int_in_str((terminal())->last_exit);
	(*j) += (string())->len(value);
	if (aux && aux[0])
		auxvar = (string())->join(aux, value);
	else
		return (value);
	free(aux);
	return (auxvar);
}

int	ft_str_is(char *line, char c, char d)
{
	int	i;

	i = 0;
	while (line && line[i] && (line[i] == c || line[i] == d))
		i++;
	if (line && line[i])
		return (0);
	return (1);
}
