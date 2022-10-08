/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:49:25 by rteles            #+#    #+#             */
/*   Updated: 2022/10/08 02:57:50 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <minishell.h>
#include <ft_wildcard.h>

t_list	*ft_wildcard_validation(t_wildcard *w, t_list *l, char *path, char *parent)
{
	DIR				*dir;
	struct dirent	*rdir;
	char			*aux;
	char			*path_dir;
	
	dir = opendir(path);
	rdir = readdir(dir);
	while (rdir)
	{
		if (ft_valid(w, rdir->d_name))
		{
			if (w->next_dir && rdir->d_type == DT_DIR)
			{
				aux = (string())->join("/", rdir->d_name);
				path_dir = (string())->join(path, aux);
				free(aux);
				aux = (string())->join(rdir->d_name, "/");
				l = ft_wildcard_validation(w->next_dir, l, path_dir, aux);
				free(aux);
				free(path_dir);
			}
		}
		rdir = readdir(dir);
	}
	closedir(dir);
	return (l);
}

