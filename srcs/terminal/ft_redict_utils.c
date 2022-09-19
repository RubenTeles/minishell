/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redict_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:12:42 by rteles            #+#    #+#             */
/*   Updated: 2022/09/19 23:14:41 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*copy_file(char *buffer, char *str, int size)
{
	char	*aux;
	int		i;

	aux = (string())->join(str, buffer);
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

	size = 1;
	total = 0;
	str = malloc(sizeof(char) * 1);
	str[0] = '\0';
	while (size > 0)
	{
		size = read(in, buffer, 1000);// -1 ERRO
		total += size;
		if (size > 0)
			str = copy_file(buffer, str, size);
	}
	return (str);
}

int	is_redirect_right(char *command)
{
	if (string()->compare_n(command, ">>", string()->len(command)))
		return (2);
	if (string()->compare_n(command, ">", string()->len(command)))
		return (1);
	return (0);
}

int	is_redirect_left(char *command)
{
	if (string()->compare_n(command, "<<", string()->len(command)))
		return (2);
	if (string()->compare_n(command, "<", string()->len(command)))
		return (1);
	return (0);
}

t_command *last_command_left_redirect(t_command *c)
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
