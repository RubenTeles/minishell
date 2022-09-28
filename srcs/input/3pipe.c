/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3pipe.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:11:37 by ede-alme          #+#    #+#             */
/*   Updated: 2022/09/28 12:51:23 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	ft_make_command(t_cms **aux, t_token **temp)
{
	int	i;

	i = 0;
	if (!fstrcmp("<", (*temp)->token) || !fstrcmp("<<", (*temp)->token)
		|| !fstrcmp(">", (*temp)->token) || !fstrcmp(">>", (*temp)->token))
	{
		(*aux)->commands[i++] = (*temp)->token;
		(*temp) = (*temp)->next;
	}
	while ((*temp) && (*temp)->token)
	{
		if (!fstrcmp("<", (*temp)->token) || !fstrcmp("<<", (*temp)->token)
			|| !fstrcmp(">", (*temp)->token) || !fstrcmp(">>", (*temp)->token))
			break ;
		if (!fstrcmp("|", (*temp)->token) || !fstrcmp("||", (*temp)->token))
		{
			free ((*temp)->token);
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
		if ((i) && (!fstrcmp("|", temp->token) || !fstrcmp("<", temp->token)
				|| !fstrcmp("<<", temp->token) || !fstrcmp(">", temp->token)
				|| !fstrcmp(">>", temp->token)))
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
	aux->commands = malloc((sizeof(char *) * (i + 1)));
	aux->commands[i] = NULL;
	temp = tokens;
	ft_make_command(&aux, &temp);
	if (temp)
		start = ft_parameters(temp, start, end);
	return (start);
}

void	ft_malloc_comando(t_data **data, t_data temp)
{
	int	i;

	i = 0;
	while (temp.start)
	{
		temp.start = temp.start->next;
		i++;
	}
	(*data)->comando = malloc(sizeof(char **) * (i + 1));
	(*data)->comando[i] = NULL;
}

int	ft_get_size_command(char **commands)
{
	int	i;

	i = 0;
	while (commands && commands[i])
		i++;
	return (i);
}
