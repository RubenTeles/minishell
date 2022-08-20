/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:51:30 by ede-alme          #+#    #+#             */
/*   Updated: 2022/08/20 20:02:46 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_get_string(t_input *input, int *i)
{
	char	*out;
	int		len;
	int		new_i;

	len = 0;
	while (input->line[*i + len] && input->line[*i + len] != ' ')
	{
		if (input->line[*i + len] == '"')
			while (input->line[*i + len] && input->line[*i + len] != '"')
				len++;
		else
			len++;
	}
	out = malloc(sizeof(char) * len + 1);
	out[len] = '\0';
	new_i = len;
	while (--len >= 0 && input->line[*i + len])
		out[len] = input->line[*i + len];
	*i = new_i + *i;
	return (out);
}

void	ft_split_prompt(t_input *input)
{
	int		i;
	//char	*temp;

	//temp = NULL;
	input->objects = 0;
	i = 0;
	while (input->line[i])
	{
		if (input->line[i] != '\t' && input->line[i] != ' ')
			printf("%s\n", ft_get_string(input, &i));
		i++;
		printf("Imprimiu objeto\n");
	}
}

int	main(int argc, char **argv, char **env)
{
	t_input	input;

	(void)argc;
	(void)argv;
	(void)env;
	input.line = NULL;
	while (1)
	{
		input.line = readline("BASHINA$ ");
		ft_split_prompt(&input);
		printf("terminou funçao de objetos\n");
	}
	return (0);
}
