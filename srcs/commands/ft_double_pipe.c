/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:10:53 by rteles            #+#    #+#             */
/*   Updated: 2022/10/10 18:57:00 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	double_pipe_execute_3(t_command *c, int in, char *line)
{
	char		*aux_line;
	char		*aux_line_2;
	int			count;

	count = ft_count_command(c);
	aux_line_2 = (string())->duplicate((terminal())->line);
	while ((string())->index_char(aux_line_2, '|') != -1 && count >= 0)
	{
		aux_line = (string())->sub_split_option(aux_line_2, '|', 1);
		if (aux_line[0] == '|')
		{
			if (count == 0)
			{
				line = (string())->sub_split_option(aux_line, '|', 1);
				free(aux_line_2);
				free(aux_line);
				break ;
			}
			count--;
		}
		free(aux_line_2);
		aux_line_2 = (string())->duplicate(aux_line);
		free(aux_line);
	}
	d_a_execute_3(c, in, aux_line, line);
}

static void	double_pipe_execute_2(t_command *c, int in)
{
	t_command	*pipe_or_and;

	pipe_or_and = next_d_pipe_or_and(c);
	if ((terminal())->last_exit == 0)
	{
		c->exit_status = (terminal())->last_exit;
		if (c->next && (is_parethenses(c->next) > 0))
			c->next->execute(c->next, STDIN_FILENO);
		else if (pipe_or_and)
			pipe_or_and->execute(pipe_or_and, STDIN_FILENO);
		return ;
	}
	double_pipe_execute_3(c, in, 0);
}

static void	double_pipe_execute(t_command *c, int in)
{
	t_command	*aux;
	int			status;

	status = 0;
	(void)in;
	aux = (terminal())->start;
	while (aux != c)
	{
		waitpid(aux->pid, &status, 0);
		if (WIFEXITED(status) && aux->choice == 12 && aux->exit_status == 0)
			aux->exit_status = WEXITSTATUS(status);
		(terminal())->last_exit = aux->exit_status;
		if (aux->next == c)
			break ;
		aux = aux->next;
	}
	double_pipe_execute_2(c, in);
}

t_command	*ft_double_pipe(t_command *c)
{
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = double_pipe_execute;
	c->choice = 13;
	return (c);
}
