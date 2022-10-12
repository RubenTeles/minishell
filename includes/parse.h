/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:03:08 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/12 13:25:17 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

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
	char	*aux;
	t_token	*temp;
};

//			---			            -> parser.c
/*This is the main of parse, it will call all functions and the call execution*/
void	ft_readline_while(void);
int		ft_readline_while_2(t_data *data);
void	formate_tokens_main(t_data *data);
int		ft_istoken(char *token, t_token	*temp, int is_par, int is_token);

//			---			            -> 1cotes.c
/*This is the first step of parse, it will see if cotes or backslash is closed,
if is not, the shell continue taking inputs into the line**/
char	*ft_check_cotes(char *line);
char	*ft_read_simple_cote(char *line, int *i, int *cote);
char	*ft_read_double_cote(char *line, int *i, int *cote);
char	*ft_new_input(char *line, char *nl);

//			---			            -> 2create_token.c
/*The second step of parse is break the input into tokens: words and operators.
I will use a char *t_token list*/
t_token	*ft_split_line(const char *line, int i, t_token	*start, t_token	*end);
char	*ft_get_command(const char *line, int *idx);
int		ft_check_pipe(const char *line, int *idx, int *j);
char	*ft_return_token(const char *line, int *idx, t_help *h);

//			---			            -> 3pipe.c
/*This step will use tokens list to create the command with paramters like 
$ echo "Hello World!"*/
int		get_comando(char *line, t_data *data);
int		ft_get_size_command(char **commands);
int		ft_multipipe(t_token *input);
int		ft_pipeerror(t_token *input, t_token *temp, int is_token);
int		ft_check_parents(t_token *input);

//			---			            -> 4create_data.c
//This step will join all commands into a ***array
t_cms	*ft_parameters(t_token *tokens, t_cms *start, t_cms *end);
int		ft_count_param(t_token *temp);
void	ft_make_command(t_cms **aux, t_token **temp);
void	ft_make_command2(t_cms **aux, t_token **temp, int i);
void	ft_malloc_comando(t_data **data, t_data temp);

//			---			            -> format_token.c
/*This functions will change the token to give to interpreter all token formated
how it should be displayed, for example, it will remove cotes, put variables into
paramters, it will identify the backslash etc*/
char	*ft_formattoken(char *tk);
char	*ft_formatdouble(char *aux, char *token, int *i, int *j);
char	*ft_formatsimple(char *aux, char *token, int *i, int *j);
char	*ft_new_aux(char *aux, char index);
char	*ft_putvar(char *token, int *i, char *aux, int *j);

//			---			            -> wildcards.c
//This functions will help process of wildcards
int		ft_iswildcard(char *token);
char	**ft_join_wildcard(char **comando, int *i);
char	**ft_take_wildcard(char **comando, int *i, char **new_command);

//			---			            -> utils.c
//This functions will help process of parser
int		fstrcmp(const char *s1, const char *s2);
char	*ft_exit_status(char *aux, int *j);
int		ft_str_is(char *line, char c, char d);
int		fisalnum(int c);
int		ft_returnpipe(char *token, t_token *temp);

//			---			            -> free_input.c
//This functions will grant all input paramters are free after the execve functs
void	ft_free_data(t_data *data, char *line);
void	ft_free_input(t_token *input, int token);
t_cms	*ft_free_start(t_cms *start);

//			---			            -> init_parse.c
//This functions will help process of main
void	formate_tokens_main(t_data *data);
char	**ft_join_wildcard(char **comando, int *i);

#endif
