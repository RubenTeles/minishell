/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 02:48:32 by rteles            #+#    #+#             */
/*   Updated: 2022/10/10 21:30:33 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_wildcard.h>

t_list	*create_list(char *str)
{
	t_list	*l;

	l = malloc(sizeof(t_list));
	if (!l)
		return (NULL);
	l->command = str;
	l->next = NULL;
	return (l);
}

char	**copy_double_string_and_free_2(char **dest, int extra)
{
	dest = malloc(sizeof(char *) * (extra + 1));
	dest[extra] = NULL;
	return (dest);
}

char	**copy_double_string_and_free(char **src, char **dest, int extra)
{
	int	i;
	int	len;

	i = 0;
	if (!src)
		return (copy_double_string_and_free_2(dest, extra));
	while (src[i])
		i++;
	dest = malloc(sizeof(char *) * (i + extra + 1));
	if (!dest)
		return (0);
	dest[i + extra] = NULL;
	i = -1;
	while (src[++i])
	{
		len = (string())->len(src[i]);
		dest[i] = malloc(sizeof(char) * (len + 1));
		(string())->copy_n(dest[i], src[i], len + 1);
		free(src[i]);
	}
	free(src);
	src = NULL;
	return (dest);
}

int	is_dir_type(int type)
{
	if (type == DT_UNKNOWN || type == DT_FIFO || type == DT_CHR
		|| type == DT_DIR || type == DT_BLK || type == DT_LNK
		|| type == DT_SOCK || type == DT_WHT)
		return (1);
	return (0);
}

int	ft_hiden_files(t_wildcard *w, char *file, DIR *dir)
{
	if ((!w->word && (file[0] == '.' && !w->begin))
		|| (w->word && !(string())->compare(file, w->word)))
	{
		w->rdir = readdir(dir);
		return (1);
	}
	return (0);
}
