/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:49:25 by rteles            #+#    #+#             */
/*   Updated: 2022/10/10 21:32:24 by rteles           ###   ########.fr       */
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

t_list	*ft_wildcard_valid_3(t_wildcard *w, t_list *l, char *aux)
{
	aux = (string())->join("/", w->rdir->d_name);
	w->next_dir->path = (string())->join(w->path, aux);
	free(aux);
	if (w->parent)
		aux = (string())->join(w->parent, w->rdir->d_name);
	else
		aux = (string())->duplicate(w->rdir->d_name);
	w->next_dir->parent = (string())->join(aux, "/");
	free(aux);
	l = ft_wildcard_valid(w->next_dir, l);
	free(w->next_dir->path);
	free(w->next_dir->parent);
	return (l);
}

t_list	*ft_wildcard_valid_2(t_wildcard *w, t_list *l, DIR *dir)
{
	while (w->rdir)
	{
		if (w->all == 1 || ft_valid(w, w->rdir->d_name, 0, 0))
		{
			if (w->next_dir && is_dir_type(w->rdir->d_type))
			{
				if (ft_hiden_files(w, w->rdir->d_name, dir))
					continue ;
				l = ft_wildcard_valid_3(w, l, 0);
			}
			if (!w->next_dir)
			{
				if (ft_hiden_files(w, w->rdir->d_name, dir))
					continue ;
				l = ft_wildcard_new(l, w->parent, w->rdir->d_name);
			}
		}
		w->rdir = readdir(dir);
	}
	return (l);
}

t_list	*ft_wildcard_valid(t_wildcard *w, t_list *l)
{
	DIR	*dir;

	if (w->in_dir > 0 && w->begin == 0 && w->final == 0 && w->med == 0
		&& w->word == 0 && w->all == 0)
		return (wildcard_empty(l, w->parent));
	dir = opendir(w->path);
	if (!dir)
		return (l);
	w->rdir = readdir(dir);
	l = ft_wildcard_valid_2(w, l, dir);
	closedir(dir);
	return (l);
}

/* OLD
t_list	*ft_wildcard_valid(t_wildcard *w, t_list *l)
{
	DIR				*dir;
	char			*aux;

	if (w->in_dir > 0 && w->begin == 0 && w->final == 0 && w->med == 0
		&& w->word == 0 && w->all == 0)
		return (wildcard_empty(l, w->parent));
	dir = opendir(w->path);
	if (!dir)
		return (l);
	w->rdir = readdir(dir);
	while (w->rdir)
	{
		if (w->all == 1 || ft_valid(w, w->rdir->d_name, 0, 0))
		{
			if (w->next_dir && is_dir_type(w->rdir->d_type))
			{
				if (ft_hiden_files(w, w->rdir->d_name))
				{
					w->rdir = readdir(dir);
					continue ;
				}
				aux = (string())->join("/", w->rdir->d_name);
				w->next_dir->path = (string())->join(w->path, aux);
				free(aux);
				if (w->parent)
					aux = (string())->join(w->parent, w->rdir->d_name);
				else
					aux = (string())->duplicate(w->rdir->d_name);
				w->next_dir->parent = (string())->join(aux, "/");
				free(aux);
				l = ft_wildcard_valid(w->next_dir, l);
				free(w->next_dir->path);
				free(w->next_dir->parent);
			}
			if (!w->next_dir)
			{
				if (ft_hiden_files(w, w->rdir->d_name))
				{
					w->rdir = readdir(dir);
					continue ;
				}
				l = ft_wildcard_new(l, w->parent, w->rdir->d_name);
			}
		}
		w->rdir = readdir(dir);
	}
	closedir(dir);
	return (l);
}*/
