/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 22:41:55 by rteles            #+#    #+#             */
/*   Updated: 2022/09/13 03:42:14 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	show_export(t_command *c, int in)
{
	t_env	*aux;
	char	**env_ter;

	dup2(in, STDIN_FILENO);
	if (c->next != NULL)
		dup2(c->fd[1], STDOUT_FILENO);
	if (in != STDIN_FILENO)
		close(in);
	close(c->fd[1]);
	aux = terminal()->env_l;
	while (aux)
	{
		write(STDOUT_FILENO, "declare -x ", 11);
		write(STDOUT_FILENO, aux->var, string()->len(aux->var));
		if (aux->val)
		{
			write(STDOUT_FILENO, "=\"", 2);
			write(STDOUT_FILENO, aux->val, string()->len(aux->val));
			write(STDOUT_FILENO, "\"", 1);
		}
		write(STDOUT_FILENO, "\n", 1);
		aux = aux->next;
	}
}

static void	export_execute(t_command *c, int in)
{
	printf("export\n");
	int	i;
	
	i = 0;
	if (c->count_cmd < 2)
		show_export(c, in);
	else
	{
		while (c->command[++i])
			terminal()->add_var(c->command[i]);
	}
	if (c->next != NULL)
		c->next->execute(c->next, c->fd[0]);
}

static t_command *new_command(char	**command)
{
	t_command	*c;

	c = malloc(sizeof(t_command));
	if (!c)
		return (NULL);
	c->command = command;
	c->count_cmd = 0;
	if (command)
		while (command[c->count_cmd])
			c->count_cmd++;
	c->path = 0;
	c->next = NULL;
	c->execute = export_execute;
	return (c);
}

t_command	*ft_export(char **input)
{
	(void)input;
	char	*input_1[3] = {"export", NULL};
	char	*input_2[3] = {"export", "Ola=", NULL};
	char	*input_3[3] = {"export", "Ola", NULL};
	char	*input_4[3] = {"export", "Ola=hehe", NULL};
	t_command *command;

	command = new_command(input_2);
	command->execute(command, 0);

	command = new_command(input_1);
	command->execute(command, 0);
	return (command);
}
