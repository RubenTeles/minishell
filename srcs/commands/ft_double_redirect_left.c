/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_redirect_left.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:34:08 by rteles            #+#    #+#             */
/*   Updated: 2022/09/23 21:34:53 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	error_line(char	*str)
{
	printf("\033[1;33mwarning\033[0;37m: here-document at line ");
	printf("%zu delimited by end-of-file\n", (string())->len(str));
	return (1);
}

static char	*ft_hereadoc(t_command *c, char *str, char *line, char *aux)
{
	while (1)
	{
		line = readline("\033[1;36m> \033[0;37m");
		if (!line && error_line(str))
			break ;
		if ((string())->compare_n(c->command[1], line,
				(string())->len(c->command[1])))
			break ;
		if (!str)
			str = (string())->join("\n", line);
		else
		{
			aux = (string())->join(str, "\n");
			free(str);
			str = (string())->join(aux, line);
			free(aux);
		}
		free(line);
	}
	free(line);
	return (str);
}

int	double_left_redirect(t_command *c, char *str, char *line, char *aux)
{
	str = ft_hereadoc(c, str, line, aux);
	if (str != NULL && !(string())->compare_n(str, "", 1))
		add_history(str);
	write(c->fd[1], str, (string())->len(str));
	close(c->fd[1]);
	if (str)
		free(str);
	if (c->next && is_redirect_left(c->next->command[0]) > 0)
		c->fd[0] = management_left_redirect(c->next);
	return (c->fd[0]);
}

static void	double_redirect_left_execute(t_command *c, int in)
{
	if (!c->command[1])
	{
		printf("syntax error near unexpected token\n");
		return ;
	}
	in = management_input_execute(c);
	if (in == -1)
		return ;
	if (c->next != NULL)
		c->next->execute(c->next, in);
}

t_command	*ft_double_redirect_left(t_command *c)
{
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = double_redirect_left_execute;
	return (c);
}
