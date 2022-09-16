/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_right.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:33:17 by rteles            #+#    #+#             */
/*   Updated: 2022/09/16 18:40:30 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*copy_file(char *buffer, char *str, int size)
{
	char	*aux;
	int		i;

	printf("%s", buffer);
	aux = (string())->join(str, buffer);
	free(str);
	i = -1;
	while (size > ++i)
		buffer[i] = '\0';
	return (aux);
}

char	*str_file(int in)
{
	char			buffer[1000];
	int				size;
	char			*str;

	size = 1;
	str = malloc(sizeof(char) * 1);
	str[0] = '\0';
	while (size > 0)
	{
		size = read(in, buffer, 1000);
		if (size > 0)
			str = copy_file(buffer, str, size);
	}
	return (str);
}

static void	redirect_right_execute(t_command *c, int in)
{
	char	*str;

	execute(c, in, 0);
	if (!c->command[1])
	{
		printf("syntax error near unexpected token `newline'\n");
		return ;
	}
	str = str_file(in);
	c->fd[1] = open(c->command[1], O_WRONLY | O_CREAT);
	write(c->fd[1], str, (string())->len(str));
	free(str);
	execute(c, in, 1);
}

void	*ft_redirect_right(t_command *c)
{
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = redirect_right_execute;
}
