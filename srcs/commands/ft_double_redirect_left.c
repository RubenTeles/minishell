/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_redirect_left.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:34:08 by rteles            #+#    #+#             */
/*   Updated: 2022/10/10 22:14:57 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*ft_hereadoc(t_command *c, char *str, char **line, char *aux)
{
	while (1)
	{
		*line = readline("\033[1;36m> \033[0;37m");
		if (!*line && error_line(str))
			return (str);
		if ((string())->compare(c->command[1], *line))
			return (str);
		if (!str)
			str = (string())->join("\n", *line);
		else
		{
			aux = (string())->join(str, "\n");
			free(str);
			str = (string())->join(aux, *line);
			free(aux);
		}
		free(*line);
	}
	free(*line);
	return (str);
}

/*static void	double_2(char *str, char *line, char *aux)
{
	char	*history;

	history = (string())->join((terminal())->line, str);
	free((terminal())->line);
	aux = (string())->join(history, "\n");
	free(history);
	if (line)
		history = (string())->join(aux, line);
	else
		history = (string())->duplicate(aux);
	(terminal())->line = (string())->join(history, "\n");
	free(aux);
	free(history);
	//if (str && !(string())->compare_n(str, "", 1))
	//	double_2(str, line, aux);
}*/
int	double_left_redirect(t_command *c, char *str, char *line, char *aux)
{
	str = ft_hereadoc(c, str, &line, aux);
	write(c->fd[1], str, (string())->len(str));
	close(c->fd[1]);
	if (str)
		free(str);
	if (line)
		free(line);
	if (c->next && is_redirect_left(c->next->command[0]) > 0)
		c->fd[0] = management_left_redirect(c->next);
	return (c->fd[0]);
}

static void	double_redirect_left_execute(t_command *c, int in)
{
	if (!c->command[1])
	{
		printf("syntax error near unexpected token <<\n");
		c->exit_status = 2;
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
	c->choice = 10;
	return (c);
}
