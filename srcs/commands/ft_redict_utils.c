/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redict_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:12:42 by rteles            #+#    #+#             */
/*   Updated: 2022/10/11 21:33:44 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*copy_file(char *buffer, char *str, int size)
{
	char	*aux;
	char	*aux_2;
	int		i;

	aux = NULL;
	aux_2 = malloc(sizeof(char) * (size + 1));
	i = -1;
	aux_2[size] = '\0';
	while (size > ++i)
	{
		aux_2[i] = buffer[i];
		buffer[i] = '\0';
	}
	if ((string())->len(str) > 0)
		aux = (string())->join(str, aux_2);
	free(str);
	if (aux)
		return (aux);
	return (aux_2);
}

char	*ft_str_file(int in)
{
	char	buffer[1001];
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
