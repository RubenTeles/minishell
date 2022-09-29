/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 20:18:02 by rteles            #+#    #+#             */
/*   Updated: 2022/09/29 23:38:05 by rteles           ###   ########.fr       */
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

	len = (string())->len(str2) + 1;
	free(str1);
	str1 = malloc(sizeof(char) * len);
	if (!str1)
		return (0);
	(string())->copy_n(str1, str2, len);
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

char	*split_two_str(char *str, char c, int option)
{
	int	index;
	int	len;

	if (!str || !c)
		return (0);
	index = (string())->index_char(str, c);
	if (index == -1 && option == 0)
		return ((string())->duplicate(str));
	else if (index == -1 && option == 1)
		return (0);
	len = (string())->len(str);
	if (option == 0)
		return ((string())->sub_str(str, 0, index));
	return ((string())->sub_str(str, index + 1, len - (index + 1)));
}

int	ft_atoi(char *str)
{
	int			i;
	int			s;
	long long	n;

	i = 0;
	s = 1;
	n = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		if (n * s > 2147483647)
			return (-1);
		else if (n * s < -2147483648)
			return (0);
		i++;
	}
	return (n * s);
}
