/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redict_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:12:42 by rteles            #+#    #+#             */
/*   Updated: 2022/10/05 18:18:01 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*copy_file(char *buffer, char *str, int size)
{
	char	*aux;
	int		i;

	aux = (string())->join(str, buffer);
	if (aux[(string())->len(aux) - 1] != '\n')
		aux[(string())->len(aux) - 1] = '\0';
	free(str);
	i = -1;
	while (size > ++i)
		buffer[i] = '\0';
	return (aux);
}

char	*ft_str_file(int in)
{
	char	buffer[1000];
	int		size;
	char	*str;
	int		total;

	size = 1000;
	total = 0;
	str = malloc(sizeof(char) * 1);
	str[0] = '\0';
	while (size == 1000 && in != STDIN_FILENO)
	{
		size = read(in, buffer, 1000);
		total += size;
		if (size > 0)
			str = copy_file(buffer, str, size);
	}
	return (str);
}

int	is_redirect_right(char *command)
{
	int	i;

	i = (string())->len(command);
	if (i == 2 && (string())->compare_n(command, ">>",
			(string())->len(command)))
		return (2);
	if (i == 1 && (string())->compare_n(command, ">",
			(string())->len(command)))
		return (1);
	return (0);
}

int	is_redirect_left(char *command)
{
	int	i;

	i = (string())->len(command);
	if (i == 2 && (string())->compare_n(command, "<<",
			(string())->len(command)))
		return (2);
	if (i == 1 && (string())->compare_n(command, "<",
			(string())->len(command)))
		return (1);
	return (0);
}

t_command	*last_command_left_redirect(t_command *c)
{
	t_command	*last;

	last = c;
	while (last)
	{
		if (last->next && is_redirect_left(last->next->command[0]))
			last = last->next;
		else
			break ;
	}
	return (last);
}
