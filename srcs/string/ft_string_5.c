/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 23:41:10 by rteles            #+#    #+#             */
/*   Updated: 2022/10/10 01:29:43 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ft_string.h>

int	ft_power(int n)
{
	int	p;

	p = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		p++;
	}
	return (p);
}

char	*ft_mkitoax(int n, int i, int h)
{
	char	*str;

	str = (char *)malloc((i + 1) * sizeof(char));
	if (str == 0)
		return (0);
	str[i] = '\0';
	i--;
	if (h == 2)
	{
		str[i] = '8';
		h--;
		i--;
	}
	while (0 + h <= i)
	{
		str[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	if (h == 1)
		str[i] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	if (n < 0)
	{
		n *= -1;
		if (n == -2147483648)
			return (ft_mkitoax(214748364, 11, 2));
		return (ft_mkitoax(n, ft_power(n) + 1, 1));
	}
	else
		return (ft_mkitoax(n, ft_power(n), 0));
}

int	ft_isalnum(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9'))
			continue ;
		else
			return (0);
	}
	return (1);
}

int	ft_strcmp(char*s1, char*s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}
