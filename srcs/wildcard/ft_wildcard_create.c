/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_create.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 02:40:53 by rteles            #+#    #+#             */
/*   Updated: 2022/10/10 21:31:40 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_wildcard.h>

char	**ft_new_flags(t_list *list, int i)
{
	t_list	*start;
	char	**flags;

	start = list;
	while (list && ++i)
		list = list->next;
	flags = malloc(sizeof(char *) * (i));
	flags[i - 1] = NULL;
	i = -1;
	while (start)
	{
		flags[++i] = (string())->duplicate(start->command);
		free (start->command);
		list = start;
		start = start->next;
		free(list);
	}
	return (flags);
}

void	__destroy_wildcard(t_wildcard *w)
{
	int	i;

	if (w->word)
		free(w->word);
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
	t_wildcard		*w;
	int				i;
	char			*aux;

	i = 0;
	if (wildcard[i] == '/')
	{
		while (wildcard[i] == '/')
			i++;
		aux = (string())->sub_str(wildcard, i, (string())->len(wildcard) - i);
		w = create_wildcard(aux, 0);
		free(aux);
		w->parent = (string())->sub_str(wildcard, 0, i);
	}
	else
		w = create_wildcard(wildcard, 0);
	w->path = path;
	list = ft_wildcard_valid(w, list);
	if (w->parent)
		free(w->parent);
	__destroy_wildcard(w);
	return (list);
}

char	**ft_wildcard(char	*command)
{
	char			buffer[1001];
	char			**flag;
	int				i;
	t_list			*list;
	t_list			*start;

	i = 0;
	list = create_list(command);
	start = list;
	if ((string())->index_char(command, '*') >= 0)
	{
		if (command[i] == '/')
			list = begin(list, command, "/");
		else
			list = begin(list, command, getcwd(buffer, 1001));
	}
	if (!start->next)
	{
		free(start);
		return (NULL);
	}
	flag = ft_new_flags(start->next, 1);
	free(start);
	return (flag);
}

//teste
//void	ft_call(void)
//{
//	char	**result;
//	int		i;
//
//	result = ft_wildcard("***");
//	i = -1;
//	while (result[++i])
//	{
//		printf("%s ", result[i]);
//		free(result[i]);
//	}
//	free(result);
//	printf("\n%i\n", i);
//}
//