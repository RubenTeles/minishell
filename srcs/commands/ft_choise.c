/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_choise.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:25:52 by rteles            #+#    #+#             */
/*   Updated: 2022/09/02 01:11:14 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_choise(char *line)
{
	if (string()->compare_n(line, "echo", string()->len(line)))
		ft_echo(0);
	else if (string()->compare_n(line, "pwd", string()->len(line)))
		ft_pwd(0);
	else if (string()->compare_n(line, "env", string()->len(line)))
		ft_env(0);
	else if (string()->compare_n(line, "exit", string()->len(line)) ||
		!line)
		ft_exit(0);
	/*else if (command[0] == "export")
		ft_export(command);
	else if (command[0] == "unset")
		ft_unset(command);
	else if (command[0] == "cd")
		ft_cd(command);
	else
		ft_pipe(command);*/
}
