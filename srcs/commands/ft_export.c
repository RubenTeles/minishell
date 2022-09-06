/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 22:41:55 by rteles            #+#    #+#             */
/*   Updated: 2022/09/07 00:10:05 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	export_execute(t_command *c, int in)
{
	printf("export\n");
	int	i;
	
	i = -1;
	if (c->count_cmd < 2)
		while (terminal()->export[++i])
			printf("%s \n", terminal()->export[i]);
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
	char	*input_4[3] = {"export", "Adeus=hehe", NULL};
	t_command *command;

	command = new_command(input_1);
	command->execute(command, 0);
    
	return (command);
}
