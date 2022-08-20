#include <minishell.h>

size_t	ft_strlen(const char *string)
{
	size_t	i;

	i = 0;
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

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		a;
	int		len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = ft_strlen(s1);
	a = ft_strlen(s2);
	len = a + i;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(&str[0], s1, i + 1);
	ft_strlcpy(&str[i], s2, a + 1);
	return (str);
}