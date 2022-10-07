/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:49:25 by rteles            #+#    #+#             */
/*   Updated: 2022/10/06 13:01:29 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <minishell.h>

typedef struct s_wildcard			t_wildcard;
struct s_wildcard {
	
	char	*begin;
	char	**med;
	char	*final;
	int		in_dir;
};

void	__destroy_wildcard(t_wildcard *w)
{
	int	i;

	if (w->med)
	{
		i = -1;
		while (w->med[++i])
			free(w->med[i]);
		free(w->med);
		w->med = NULL;
	}
	if (w->begin)
		free(w->begin);
	if (w->final)
		free(w->final);
	free(w);
}

char	**copy_double_string_and_free(char **src, char **dest, int extra)
{
	int	i;


	i = 0;
	if (!src)
	{
		dest = malloc(sizeof(char *) * (i + extra + 1));
		dest[i + extra] = NULL;
		return (dest);
	}
	while (src[i])
		i++;
	dest = malloc(sizeof(char *) * (i + extra + 1));
	if (!dest)
		return (0);
	i = -1;
	while (src[++i])
	{
		(string())->copy_n(dest[i], src[i], string()->len(src[i] + 1));
		free(src[i]);
	}
	free(src);
	src = NULL;
	dest[i + extra] = NULL;
	return (dest);
}


void	wildcard_med(t_wildcard *w, char *sub)
{
	char	**aux_med;
	char	*aux_2;
	int		count;

	count = 1;
	while ((string())->index_char(sub, '*') > 0)
	{
		count++;
		aux_2 = (string())->sub_split_option(sub, '*', 0);
		aux_med = copy_double_string_and_free(w->med, aux_med, 1);
		aux_med[count - 1] = (string())->duplicate(aux_2);
		w->med = copy_double_string_and_free(aux_med, w->med, 0);
		free(aux_2);
		aux_2 = (string())->sub_split_option(sub, '*', 1);
		free(sub);
		sub = (string())->duplicate(aux_2);
		free(aux_2);
	}
}

t_wildcard	*create_wildcard(char *wildcard)
{
	t_wildcard	*w;
	char		*aux;
	char		*aux_2;

	w = malloc(sizeof(t_wildcard));
	if (!w)
		return (NULL);
	w->begin = NULL;
	w->med = NULL;
	w->final = NULL;
	w->in_dir = 0;
	if ((string())->index_char(wildcard, '*') > 0)
		w->begin = (string())->sub_split_option(0, '*', 0);
	aux = (string())->sub_split_option(wildcard, '*', 1);
	while ((string())->index_char(aux, '*') == 0)
		aux++;
	if ((string())->index_char(aux, '*') == -1)
	{
		if ((string())->len(aux) > 0)
			w->final = (string())->duplicate(aux);
		free(aux);
		return (w);;
	}
	wildcard_med(w, aux);
	//falta o w->in_dir
	return (w);
}

int	ft_valid_str(char *str1, char *str2, int i)
{
	int	a;

	a = 0;
	if (!str2 || !str2[i])
		return (0);
	while (str1[a] && str2[i] && (str1[a] != str2[i]))
		i++;
	while (str1[a] && str2[i] && (str1[a] == str2[i]))
	{
		i++;
		a++;
	}
	if (str1[a] == '\0')
		return (i);
	return (0);
}

int	ft_valid(t_wildcard *w, char *str)
{
	int	i;
	int	aux;
	int	a;

	i = 0;
	if (w->begin)
	{
		aux = ft_valid_str(w->begin, str, i);
		if ((aux - i) == 0)
			return (0);
		i = aux;
	}
	if (w->med)
	{
		a = -1;
		while (w->med[++a])
		{
			aux = ft_valid_str(w->med[a], str, i);
			if ((aux - i) == 0)
				return (0);
			i = aux;
		}
	}
	if (w->final)
	{
		aux = ft_valid_str(w->final, str, i);
		if ((aux - i) == 0)
			return (0);
		i = aux;
		if (str[i] != '\0')
			return (0);
	}
	return (1);
}

char	**begin(DIR *dir, char **command, char *wildcard, char *path)
{
	DIR				*aux_dir;
	int				file;
	struct dirent	*rdir;
	t_wildcard		*w;

	w = create_wildcard(wildcard);
	file = 0;
	while (rdir = readdir(dir))
	{
		if (ft_valid(w, rdir->d_name))
			printf("%s\t", rdir->d_name);
		/*if (rdir->d_name != '.')
		{
			file++;
			


			if (file % 8 == 0)
				printf("\n");
			printf("%s", rdir->d_name);
			if (rdir->d_type == DT_DIR)
				printf("/");
			printf("\t");
		}*/
	}
	printf("\n");
	__destroy_wildcard(w);
	return (command);
}

char	**ft_wildcard(char	**command)
{
	char			buffer[1001];
	DIR				*dir;
	int				i;

	i = -1;
	dir = opendir(getcwd(buffer, 1001));
	while (command[++i])
	{
		if ((string())->index_char(command[i], '*') >= 0)
			command = begin(dir, command, command[i], getcwd(buffer, 1001));
	}
	closedir(dir);
	return (command);
}

void	ft_call(void)
{
	char	**commands;
	int		i;
	//[3] = {"ls", "*.c", NULL};
	commands = malloc(sizeof(char *) * 3);
	commands[0] = malloc(sizeof(char) * 3);
	commands[0][0] = 'l';
	commands[0][1] = 's';
	commands[0][2] = '\0';
	commands[1] = malloc(sizeof(char) * 4);
	commands[1][0] = '*';
	commands[1][1] = '.';
	commands[1][2] = '*';
	commands[1][3] = '\0';
	commands[2] = NULL;
	commands = ft_wildcard(commands);
	i = -1;
	while (commands[++i])
	{
		//printf("%s\n", commands[i]);
		free(commands[i]);
	}
	free(commands);
}
