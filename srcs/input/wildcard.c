/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 12:32:59 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/12 13:23:29 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <ft_wildcard.h>

char	**ft_take_wildcard(char **comando, int *i, char **new_command)
{
	int		j;
	int		temp;
	int		parameters;
	char	**out;

	j = 0;
	temp = (*i);
	parameters = 0;
	while (comando && comando[parameters] && parameters < (*i))
		parameters++;
	while (new_command && new_command[j])
		j++;
	out = malloc(sizeof(char *) * (parameters + j + 1));
	out[parameters + j] = NULL;
	while (j >= 0)
	{
		out[parameters + j] = new_command[j];
		j--;
	}
	while (--parameters >= 0 && --temp >= 0)
		out[parameters] = comando[temp];
	free(comando[(*i)]);
	free(comando);
	free(new_command);
	return (out);
}

char	**ft_join_wildcard(char **comando, int *i)
{
	char	**new_command;

	new_command = ft_wildcard(comando[(*i)]);
	if (new_command)
		return (ft_take_wildcard(comando, i, new_command));
	return (comando);
}

int	ft_iswildcard(char *token)
{
	int	i;
	int	cote;
	int	wildcard;

	i = 0;
	cote = 0;
	wildcard = 0;
	while (token && token[i])
	{
		if (!cote && token[i] == '\\' && ++i && token[i])
			i++;
		else if (!cote && (token[i] == '\'' || token[i] == '"'))
			cote = token[i++];
		else if (cote && token[i] == cote && ++i)
			cote = 0;
		else if (!cote && token[i] == '*' && ++i)
			wildcard = 1;
		else
			i++;
	}
	return (wildcard);
}
