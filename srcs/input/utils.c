/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:35:27 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/10 19:44:43 by ede-alme         ###   ########.fr       */
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

int	fisalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_returnpipe(char *token, t_token *temp)
{
	if (token)
		printf("syntax error near unexpected token `%s´\n", token);
	ft_free_input(temp, 1);
	return (1);
}
