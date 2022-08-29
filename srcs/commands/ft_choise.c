/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_choise.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:25:52 by rteles            #+#    #+#             */
/*   Updated: 2022/08/29 22:33:17 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void     ft_choise(char **command)
{
	if (command[0] == "echo")
		ft_echo(command);
	else if (command[0] == "cd")
		ft_cd(command);
	else if (command[0] == "pwd")
		ft_pwd(command);
	else if (command[0] == "export")
		ft_export(command);
	else if (command[0] == "unset")
		ft_unset(command);
	else if (command[0] == "env")
		ft_env(command);
	else if (command[0] == "exit")
		ft_exit(command);
	else
		ft_pipe(command);
}
