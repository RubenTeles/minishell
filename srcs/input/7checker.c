/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7checker.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:45:44 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/05 19:18:56 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	ft_check_parents(t_token *input)
{
	int		is_par;
	char	*last_token;
	t_token	*temp;

	is_par = 0;
	temp = input;
	while (input)
	{
		if (!fstrcmp("(", input->token))
				is_par++;
		if (!fstrcmp(")", input->token))
				is_par--;
		if (is_par < 0)
			return (ft_returnpipe(input->token, temp));
		last_token = input->token;
		input = input->next;
	}
	if (is_par != 0)
		return (ft_returnpipe(last_token, temp));
	return (0);
}
