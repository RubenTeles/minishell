/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1cotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:01:38 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/01 20:14:52 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

char	*ft_new_input(char *line, char *nl)
{
	char	*new;
	char	*temp;

	new = readline("\033[1;36m> \033[0;37m");
	if (!new)
		return (line);
	if (new[0])
	{
		if (nl)
		{
			temp = (string())->join(line, nl);
			free(line);
		}
		else
			temp = line;
		line = (string())->join(temp, new);
	}
	else
	{
		temp = line;
		line = (string())->join(temp, "\n");
	}
	free(new);
	free(temp);
	return (line);
}

char	*ft_read_double_cote(char *line, int *i, int *cote)
{
	(*cote) = '"';
	while (line && line[*i] && (*cote))
	{
		if (line[*i] == '"' && ++(*i))
			(*cote) = 0;
		else if (line[*i] == '\\' && ++(*i) && !line[*i])
			line = ft_new_input(line, NULL);
		else
			(*i)++;
	}
	return (line);
}

char	*ft_read_simple_cote(char *line, int *i, int *cote)
{
	(*cote) = '\'';
	while (line && line[*i] && (*cote))
	{
		if (line[*i] == '\'' && ++(*i))
			(*cote) = 0;
		else
			(*i)++;
	}
	return (line);
}

char	*ft_check_cotes(char *line)
{
	int	i;
	int	cote;

	i = 0;
	cote = 0;
	while (line && line[i])
	{
		if (line[i] == '"' && ++i)
			line = ft_read_double_cote(line, &i, &cote);
		else if (line[i] == '\'' && ++i)
			line = ft_read_simple_cote(line, &i, &cote);
		else if (line[i] == '\\' && ++i && !line[i])
			line = ft_new_input(line, NULL);
		else
			i++;
	}
	if (cote)
	{
		line = ft_new_input(line, "\n");
		line = ft_check_cotes(line);
	}
	return (line);
}
