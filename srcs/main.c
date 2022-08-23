/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:51:30 by ede-alme          #+#    #+#             */
/*   Updated: 2022/08/23 20:04:46 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//Teste de função ft_split_prompt, inicio da separação do input digitado no prompt
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
	}
	free (input.line);
	return (0);
}
