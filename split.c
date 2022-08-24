/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:00:32 by ede-alme          #+#    #+#             */
/*   Updated: 2022/08/23 20:01:40 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//Função que quando chamada, adiciona a variavel $env na line... se o valor não existir, limpa a palavra $*** da line
void	ft_put_env(char *line, int index)
{
	printf("%c\n", line[index]);
}

//Função que separa todo o conteudo da line retornando *out que é o comando flag ou pipe
char	*ft_get_string(t_input *input, int *i)
{
	char	*out;
	int		len;
	int		new_i;

	len = 0;
	while (input->line[*i + len] && input->line[*i + len] != ' ')
	{
		if (input->line[*i + len] == '$')
			ft_put_env(input->line, *i + len);
		len++;
		if (input->line[*i + len - 1] == 39)
			while (input->line[*i + len] && input->line[*i + len] != 39)
				;
		if (input->line[*i + len - 1] == '"')
			while (input->line[*i + len] && input->line[*i + len++] != '"')
				if (input->line[*i + len++] == '$')
					ft_put_env(input->line, *i + (len - 1));
	}
	out = malloc(sizeof(char) * len + 1);
	out[len] = '\0';
	new_i = len;
	while (--len >= 0 && input->line[*i + len])
		out[len] = input->line[*i + len];
	*i = new_i + *i;
	return (out);
}

//Função de inicio, percorre um input recebido da função readline, ou seja vai percorrer a line até chegar ao fim e ierá armaznar todos os objetos num **array...
void	ft_split_prompt(t_input *input)
{
	int		i;
	char	*temp;

	temp = NULL;
	input->objects = 0;
	i = 0;
	while (input->line[i] != '\0')
	{
		if (input->line[i] != '\t' && input->line[i] != ' ')
		{
			temp = ft_get_string(input, &i);
			printf("%s\n", temp);
			free (temp);
		}
		if (!input->line[i])
			break ;
		i++;
	}
}
