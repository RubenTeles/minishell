/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 20:12:17 by rteles            #+#    #+#             */
/*   Updated: 2022/09/26 05:12:33 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ft_string.h>

/*Da o numero de carateres*/
size_t	ft_strlen(const char *string)
{
	size_t	i;

	i = 0;
	if (!string)
		return (0);
	while (string[i])
		i++;
	return (i);
}

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	a;
	size_t	len;

	i = 0;
	a = 0;
	len = ft_strlen(s2);
	if (len == 0)
		return ((char *)s1);
	while (i < n && s1[i])
	{
		a = 0;
		while (s1[i + a] == s2[a] && ((i + a) < n) && s2[a] && s1[i + a])
			a++;
		if (a == len)
			return ((char *)&s1[i + a]);
		i++;
	}
	return (0);
}

int	ft_strlcpy(char *dest, const char *src, int size)
{
	int	i;

	i = 0;
	if (size == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (i < size - 1 && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	if (i < size)
		dest[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (str1[i] == str2[i] && i < n - 1 && str1[i] != '\0')
		i++;
	if ((unsigned char)str1[i] - (unsigned char)str2[i] == 0)
		return (1);
	return (0);
}

char	*ft_string_in_two_char(char *str, char c1, char c2)
{
	int	i;
	int	start;
	int	end;

	i = -1;
	start = -1;
	end = -1;
	while (str[++i])
	{
		if (start < 0 && str[i] == c1)
			start = i;
		else if (end < 0 && str[i] == c2)
			end = i;
	}
	if (start < 0)
		return (0);
	if (end > -1)
		return (ft_substr(str, start, end - (start)));
	return (ft_substr(str, start, ft_strlen(str) - (start)));
}
