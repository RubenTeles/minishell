/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:39:43 by rteles            #+#    #+#             */
/*   Updated: 2022/10/10 01:08:39 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>
#include <minishell.h>

static int	ft_str_s_str(char *s1, char *s2)
{
	size_t	i;
	size_t	a;

	i = -1;
	if (!s1 || !s2)
		return (0);
	while (s1[++i])
	{
		a = -1;
		while (s2[++a])
		{
			if (s1[i] == s2[a])
				break ;
		}
		if (s1[i] == s2[a])
			continue ;
		return (0);
	}
	return (1);
}

static char	*ft_strrchr(const char *string, int c)
{
	int		i;
	char	*rstr;

	i = 0;
	while (string[i])
		i++;
	rstr = (char *)string;
	while (i >= 0)
	{
		if (rstr[i] == (unsigned char)c)
			return (&rstr[i]);
		i--;
	}
	return (0);
}

static char	*ft_strchr(const char *string, int c)
{
	int		i;
	char	*rtstr;

	i = 0;
	rtstr = (char *)string;
	while (rtstr[i])
	{
		if (rtstr[i] == (unsigned char)c)
			return (&rtstr[i]);
		i++;
	}
	if (rtstr[i] == c)
		return (&rtstr[i]);
	return (0);
}

static char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		a;
	int		len;

	str = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	i = ft_strlen(s1);
	a = ft_strlen(s2);
	len = a + i;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	ft_strlcpy(&str[0], s1, i + 1);
	ft_strlcpy(&str[i], s2, a + 1);
	return (str);
}

/*
len:

split:

n_str:

copy_n:
Copia a string SRC para a string DEST num determinado numero de caracteres

join:

search_chars:
Procura se a string tem apenas estes caracteres,
Retorna 1 se tiver alem destes.

pos_char:
Retorna a primeira posição do char procurado.

pos_char_last:
Retorna a ultima posição do char procurado.

duplicate:
Duplica uma string (é preciso dar free);

compare_n:
Compara 2 strings, com n casas. Retorna 1 se for verdadeiro ou 0 se nao.

sub_str:
Substring, uma nova string que começa apartir de x casa com x len.

sub_str_chars:
Substring, um nova string que começa apartir de c1, ate c2.

sub_split_option:
Nova string, divida por um caracter. Se a opção for 0 é do inicio ate ao c,
se for 1 é do c ate '\0'.
Retorna Null se der erro.

replace:
Muda o valor da str1 para o str2.
Retorna -1 se nao conseguir

index_char:
retorna o index do char na string, ou -1 se nao tiver.

str_in_int:
converte str de numeros em int.

int_in_str:
converte int em str.

int	ft_isalnum:
verifica se a string contem apenas caracteres alfa numericos 
retorna 1 se sim, ou 0 se nao.

*/
t_string	*string(void)
{
	static t_string	s = {ft_strlen, ft_split, ft_strnstr, ft_strlcpy,
		ft_strjoin, ft_str_s_str, ft_strchr, ft_strrchr, ft_strdup, ft_strcmp,
		ft_strncmp, ft_substr, ft_string_in_two_char, split_two_str,
		replace_str, index_char, ft_atoi, ft_itoa, ft_isalnum};

	return (&s);
}
