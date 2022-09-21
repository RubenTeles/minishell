/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:03:08 by ede-alme          #+#    #+#             */
/*   Updated: 2022/09/21 21:29:14 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_token	t_token;
typedef struct s_cms	t_cms;
typedef struct s_data	t_data;

struct s_token{
	char	*token;
	t_token	*next;
};

struct s_cms {
	char	**commands;
	t_cms	*next;
};

struct s_data {
	char	***comando;
	t_token	*input;
	t_cms	*start;
};

//			---			            -> ->split_line.c
//Split the line functions in tokens array*
t_token	*ft_split_line(const char *line, int i, t_token	*start, t_token	*end);
char	*ft_get_command(const char *line, int *i);

//			---			            -> ->create_comands.c
//Create commands with tokens to be passed to the command line array**
t_cms	*ft_parameters(t_token *tokens, t_cms *start, t_cms *end);
int		ft_count_param(t_token *temp);
void	ft_make_command(t_cms **aux, t_token **temp);

//			---			            -> ->create_comands.c
//join all commands into a single array***
void	get_comando(char *line, t_data *data);
void	ft_malloc_comando(t_data **data, t_data temp);
int		ft_get_size_command(char **commands);

//			---			            -> -> free_inputs.c
//This functions will grant all input paramters are free after the execve functs
t_cms	*ft_free_start(t_cms *start);
void	ft_free_data(t_data *data, char *line);
void	ft_free_input(t_token *input);

#endif
