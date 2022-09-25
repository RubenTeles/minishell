/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:03:08 by ede-alme          #+#    #+#             */
/*   Updated: 2022/09/26 00:00:10 by ede-alme         ###   ########.fr       */
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
# include <string.h>
# include <ctype.h>
# include <ft_string.h>
# include <minishell.h>

typedef struct s_token	t_token;
typedef struct s_cms	t_cms;
typedef struct s_data	t_data;
typedef struct s_help	t_help;

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

struct s_help {
	int		i;
	int		j;
	int		cote;
};

//			---			            -> 1cotes.c
//This will see if cotes is closed, if is not, the shell continue take input*
char	*ft_check_cotes(char *line);
char	*ft_read_simple_cote(char *line, int *i, int *cote);
char	*ft_read_double_cote(char *line, int *i, int *cote);
char	*ft_new_input(char *line, char *nl);

//			---			            -> 2create_token.c
//Create a list of tokens read from line
t_token	*ft_split_line(const char *line, int i, t_token	*start, t_token	*end);
char	*ft_get_command(const char *line, int *idx);

//			---			            -> 2create_token.c
//join all tokens into a command array***
int		ft_get_size_command(char **commands);
void	ft_malloc_comando(t_data **data, t_data temp);
t_cms	*ft_parameters(t_token *tokens, t_cms *start, t_cms *end);
int		ft_count_param(t_token *temp);
void	ft_make_command(t_cms **aux, t_token **temp);

//			---			            -> 4create_data.c
//This functions will be called to start data
void	get_comando(char *line, t_data *data);

//			---			            -> 5format_token.c
//This functions will change the input format of token
char	*ft_formattoken(char *tk);
char	*ft_formatdouble(char *aux, char *token, int *i, int *j);
char	*ft_formatsimple(char *aux, char *token, int *i, int *j);
char	*ft_new_aux(char *aux, char index);
char	*ft_putvar(char *token, int *i, char *aux, int *j);

//			---			            -> 6free_input.c
//This functions will grant all input paramters are free after the execve functs
void	ft_free_data(t_data *data, char *line);
void	ft_free_input(t_token *input);
t_cms	*ft_free_start(t_cms *start);

//			---			            -> utils.c
//This functions will help process of parser
size_t	ft_strlen(const char *s);
int		fstrcmp(const char *s1, const char *s2);

#endif
