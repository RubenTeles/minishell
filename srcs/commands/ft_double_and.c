/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_and.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:10:42 by rteles            #+#    #+#             */
/*   Updated: 2022/10/10 18:56:04 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_count_command(t_command *c)
{
	int			len;
	int			count;
	t_command	*aux;

	count = 0;
	len = (string())->len(c->command[0]);
	aux = (terminal())->start;
	while (aux && (aux != c))
	{
		if (len == 2
			&& (string())->compare_n(aux->command[0], c->command[0], 2))
			count++;
		aux = aux->next;
	}
	return (count);
}

void	d_a_execute_3(t_command *c, int in, char *aux_line, char *line)
{
	t_data		data;

	if (!is_in_p_pipe(c))
		in = STDIN_FILENO;
	aux_line = (string())->duplicate((terminal())->line);
	ft_command_execute_2();
	free((terminal())->line);
	(terminal())->line = line;
	data.input = NULL;
	get_comando((terminal())->line, &data);
	formate_tokens_main(&data);
	(terminal())->execute((&data)->comando, in);
	ft_free_data(&data, (terminal())->line);
	(terminal())->line = aux_line;
}

static void	double_and_execute_2(t_command *c, int in, char *line)
{
	char		*aux_line;
	char		*aux_line_2;
	int			count;

	count = ft_count_command(c);
	aux_line_2 = (string())->duplicate((terminal())->line);
	while ((string())->index_char(aux_line_2, '&') != -1 && count >= 0)
	{
		aux_line = (string())->sub_split_option(aux_line_2, '&', 1);
		if (aux_line[0] == '&')
		{
			if (count == 0)
			{
				line = (string())->sub_split_option(aux_line, '&', 1);
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

static void	double_and_execute(t_command *c, int in)
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
	if ((terminal())->last_exit != 0)
		return ;
	double_and_execute_2(c, in, 0);
}

t_command	*ft_double_and(t_command *c)
{
	if (!c->command)
		return (c);
	while (c->command[c->count_cmd])
		c->count_cmd++;
	c->execute = double_and_execute;
	c->choice = 12;
	return (c);
}
