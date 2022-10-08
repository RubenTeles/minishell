/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_create.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 02:40:53 by rteles            #+#    #+#             */
/*   Updated: 2022/10/08 16:15:07 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_wildcard.h>

void	__destroy_wildcard(t_wildcard *w)
{
	int	i;

	if (w->begin)
		free(w->begin);
	if (w->med)
	{
		i = -1;
		while (w->med[++i])
			free(w->med[i]);
		free(w->med);
		w->med = NULL;
	}
	if (w->final)
		free(w->final);
	if (w->next_dir)
		__destroy_wildcard(w->next_dir);
	free(w);
}

t_list	*begin(t_list *list, char *wildcard, char *path)
{
	struct dirent	*rdir;
	t_wildcard		*w;
	int				i;
	char			*aux;
	char			*parent;

	i = 0;
	parent = NULL;
	if (wildcard[i] == '/')
	{
		while (wildcard[i] == '/')
			i++;
 		aux = (string())->sub_str(wildcard, i, (string())->len(wildcard) - i);
		w = create_wildcard(aux, 0);
		free(aux);
		parent = (string())->sub_str(wildcard, 0, i);
	}
	else
		w = create_wildcard(wildcard, 0);
	list = ft_wildcard_validation(w, list, path, parent);
	__destroy_wildcard(w);
	return (list);
}

char	**ft_wildcard(char	**command)
{
	char			buffer[1001];
	char			*path;
	int				i;
	int				aux;
	t_list			*start;
	t_list			*list;

	i = 0;
	start = create_list(command[0]);
	list = start;
	while (command[++i])
	{
		if ((string())->index_char(command[i], '*') >= 0)
		{
			aux = 0;
			if (command[i][aux] == '/')
				path = "/";
			else
				path = getcwd(buffer, 1001);
			while (command[i][aux] == '/')
				aux++;
			list = begin(list, command[i], path);
		}
		else
			list->next = create_list(command[i]);
	}
	//conversao lista para **comandos
	return (command);
}

void	ft_call(void)
{
	char	*commands[3] = {"ls", "///*", NULL};
	char	**result;
	int		i;

	result = ft_wildcard(commands);
	i = -1;
	while (commands[++i])
	{
		//printf("%s\n", commands[i]);
		//free(commands[i]);
	}
	//free(commands);
}
