/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 20:18:02 by rteles            #+#    #+#             */
/*   Updated: 2022/09/06 23:12:16 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ft_string.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (!s)
		return (0);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	ft_strlcpy(&str[0], s + start, len + 1);
	return (str);
}

char	*replace_str(char *str1, char *str2)
{
	int	len;
	
	len = string()->len(str2) + 1;
	free(str1);
	str1 = malloc(sizeof(char) * len);
	if (!str1)
		return (0);
	string()->copy_n(str1, str2, len);
	return (str1);
}

int	index_char(char *str, char c)
{
	int	i;

	i = -1;
	if (!str || !c)
		return (-1);
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	if (str[i] == c)
		return (i);
	return (-1);
}
