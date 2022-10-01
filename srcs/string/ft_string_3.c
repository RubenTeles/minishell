/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:50:21 by rteles            #+#    #+#             */
/*   Updated: 2022/09/07 18:55:52 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ft_string.h>

char	*ft_creatword(char const *s, int lenword, int index)
{
	char	*substr;
	int		i;

	i = 0;
	substr = (char *)malloc((lenword + 2) * sizeof(char));
	if (substr == 0)
		return (0);
	substr[lenword] = '/';
	substr[lenword + 1] = '\0';
	index -= lenword;
	while (i < lenword)
	{
		substr[i] = s[index];
		index++;
		i++;
	}
	return (substr);
}

char	*ft_strx(char const *s, char c, int w)
{
	int	i;
	int	a;
	int	len;

	i = 0;
	a = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == c || s[i + 1] == '\0')
		{
			if (s[i + 1] == '\0' && s[i] != c)
				return (ft_creatword(s, a + 1, i + 1));
			else if (a > 0)
			{
				len++;
				if (len == w)
					return (ft_creatword(s, a, i));
			}
			a = -1;
		}
		a++;
		i++;
	}
	return (0);
}

int	ft_lenchar(char const *s, char c)
{
	int	i;
	int	a;
	int	len;

	i = 0;
	a = 0;
	len = 1;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
		{
			if (a > 0 && s[i + 1] != '\0')
				len++;
			a = -1;
		}
		a++;
		i++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		len;
	char	**str;

	if (!s)
		return (0);
	len = ft_lenchar(s, c);
	str = (char **)malloc((len + 1) * sizeof(char *));
	if (str == 0)
		return (0);
	i = 0;
	str[len] = NULL;
	while (i < len)
	{
		str[i] = ft_strx(s, c, i + 1);
		i++;
	}
	return (str);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	str = malloc((len + 1) * sizeof(char));
	if (str == 0)
		return (0);
	len = 0;
	while (s[len])
	{
		str[len] = s[len];
		len++;
	}
	str[len] = '\0';
	return (str);
}
