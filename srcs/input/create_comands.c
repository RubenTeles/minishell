/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_comands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:18:34 by ede-alme          #+#    #+#             */
/*   Updated: 2022/09/06 13:23:03 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	ft_make_command(t_cms **aux, t_token **temp)
{
	int	i;

	i = 0;
	if (!strcmp("<", (*temp)->token) || !strcmp("<<", (*temp)->token)
		|| !strcmp(">", (*temp)->token) || !strcmp(">>", (*temp)->token))
	{
		(*aux)->commands[i++] = (*temp)->token;
		(*temp) = (*temp)->next;
	}
	while ((*temp))
	{
		if (!strcmp("<", (*temp)->token) || !strcmp("<<", (*temp)->token)
			|| !strcmp(">", (*temp)->token) || !strcmp(">>", (*temp)->token))
			break ;
		if (!strcmp("|", (*temp)->token))
		{
			(*temp) = (*temp)->next;
			break ;
		}
		(*aux)->commands[i++] = (*temp)->token;
		(*temp) = (*temp)->next;
	}
}

int	ft_count_param(t_token *temp)
{
	int	i;

	i = 0;
	while (temp)
	{
		if (!strcmp("|", temp->token) || !strcmp("<", temp->token)
			|| !strcmp("<<", temp->token) || !strcmp(">", temp->token)
			|| !strcmp(">>", temp->token))
			break ;
		i++;
		temp = temp->next;
	}
	return (i);
}

t_cms	*ft_parameters(t_token *tokens, t_cms *start, t_cms *end)
{
	t_cms	*aux;
	t_token	*temp;
	int		i;

	temp = tokens;
	if (!tokens)
		return (NULL);
	i = ft_count_param(temp);
	aux = malloc(sizeof(t_cms));
	aux->next = NULL;
	if (start == NULL)
		start = aux;
	else
		end->next = aux;
	end = aux;
	aux->commands = malloc(sizeof(char *) * (i + 1));
	aux->commands[i] = NULL;
	temp = tokens;
	ft_make_command(&aux, &temp);
	if (temp)
		start = ft_parameters(temp, start, end);
	return (start);
}
