/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:49:25 by rteles            #+#    #+#             */
/*   Updated: 2022/10/10 01:50:01 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <minishell.h>
#include <ft_wildcard.h>

t_list	*wildcard_empty(t_list *l, char *parent)
{
	l->next = create_list((string())->duplicate(parent));
	l = l->next;
	return (l);
}

t_list	*ft_wildcard_new(t_list *l, char *parent, char *read_dir)
{
	if (parent)
		l->next = create_list((string())->join(parent, read_dir));
	else
		l->next = create_list((string())->duplicate(read_dir));
	l = l->next;
	return (l);
}

t_list	*ft_wildcard_valid(t_wildcard *w, t_list *l, char *path, char *parent)
{
	DIR				*dir;
	struct dirent	*rdir;
	char			*aux;
	char			*aux_2;
	char			*path_dir;

	if (w->in_dir > 0 && w->begin == 0 && w->final == 0 && w->med == 0
		&& w->word == 0 && w->all == 0)
		return (wildcard_empty(l, parent));
	if (w->word && (string())->compare(w->word, "/"))
	{
		aux = (string())->join(parent, "/");
		l = ft_wildcard_valid(w->next_dir, l, path, aux);
		free(aux);
		return (l);
	}
	dir = opendir(path);
	if (!dir)
		return (l);
	rdir = readdir(dir);
	while (rdir)
	{
		if (w->all == 1 || ft_valid(w, rdir->d_name, 0, 0))
		{
			if (w->next_dir && is_dir_type(rdir->d_type))
			{
				if ((!w->word && (rdir->d_name[0] == '.' && !w->begin))
					|| (w->word && !(string())->compare(rdir->d_name, w->word)))
				{
					rdir = readdir(dir);
					continue ;
				}
				aux = (string())->join("/", rdir->d_name);
				path_dir = (string())->join(path, aux);
				free(aux);
				if (parent)
					aux = (string())->join(parent, rdir->d_name);
				else
					aux = (string())->duplicate(rdir->d_name);
				aux_2 = (string())->join(aux, "/");
				free(aux);
				l = ft_wildcard_valid(w->next_dir, l, path_dir, aux_2);
				free(aux_2);
				free(path_dir);
			}
			if (!w->next_dir)
			{
				if ((!w->word && (rdir->d_name[0] == '.' && !w->begin))
					|| (w->word && !(string())->compare(rdir->d_name, w->word)))
				{
					rdir = readdir(dir);
					continue ;
				}
				l = ft_wildcard_new(l, parent, rdir->d_name);
			}
		}
		rdir = readdir(dir);
	}
	closedir(dir);
	return (l);
}

char	**ft_new_flags(t_list *list, int i)
{
	char	**flags;

	if (list->next)
		flags = ft_new_flags(list->next, i + 1);
	else
	{
		flags = malloc(sizeof(char *) * (i + 1));
		flags[i] = NULL;
	}
	flags[i - 1] = (string())->duplicate(list->command);
	free (list->command);
	free(list);
	return (flags);
}
