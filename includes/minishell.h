/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:03:04 by ede-alme          #+#    #+#             */
/*   Updated: 2022/08/23 20:20:44 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <ft_string.h>
# include <fcntl.h> 
# include <errno.h> 
# include <parse.h> 

/* Para incluir readline passos:
sudo apt-get install libreadline-dev

https://vcpkg.io/en/getting-started.html
*/

typedef struct s_update				t_update;
typedef struct s_destroy			t_destroy;
typedef struct s_env				t_env;
typedef struct s_terminal			t_terminal;
typedef struct s_command			t_command;

struct s_update {
	void		(*all)(void);
	void		(*env_m)(void);
	void		(*path)(void);
	void		(*title)(void);
};

struct s_destroy {
	void		(*all)(void);
	void		(*env_l)(void);
	void		(*env_m)(void);
	void		(*path)(void);
	void		(*title)(void);
	void		(*commands)(void);
};

struct s_env {
	char	*var;
	char	*val;
	t_env	*next;
};

struct s_terminal {
	char		*title;
	int			last_exit;
	int			env_count;
	char		**env_m;
	t_env		*env_l;
	char		**path;
	char		*line;
	t_command	*start;
	t_update	*update;
	t_destroy	*destroy;
	void		(*add_var)(char *var);
	void		(*update_var)(char *var, char *str);
	void		(*delete_var)(char *var);
	void		(*execute)(char ***commands, int in);
	void		(*count_env)(void);
	char		*(*variable_env)(char *var);
	int			(*var_exist)(char *str);
};

struct s_command {
	int			fd[2];
	int			pid;
	char		**command;
	int			count_cmd;
	char		*path;
	int			choice;
	int			exit_status;
	void		(*execute)(t_command *c, int in);
	t_command	*prev;
	t_command	*next;
};

//----Utils----//
t_terminal	*terminal(void);
void		new_terminal(char **env);
void		create_env_l(char **env);
void		execute(t_command *c, int option);
void		execute_in(t_command *c, int in);
int			management_input_execute(t_command *c);
int			error_line(char	*str);
t_command	*next_d_pipe_or_and(t_command *c);
void		ft_command_execute_2(void);

//----Redirect----//
char		*ft_str_file(int in);
int			is_redirect_right(char *command);
int			is_redirect_left(char *command);
t_command	*last_command_left_redirect(t_command *c);
int			management_left_redirect(t_command *c);
int			left_redirect(t_command *c);
int			\
double_left_redirect(t_command *c, char *str, char *line, char *aux);
int			is_d_pipe_or_and(t_command *c);
void		ft_permission_denied(t_command *c, int in);
int			is_parethenses(t_command *c);
int			is_ppa(t_command *c);
int			is_token(t_command *c);
int			ft_count_command(t_command *c);
int			is_in_p_pipe(t_command *c);
void		d_a_execute_3(t_command *c, int in, char *aux_line, char *line);

//----Terminal Methods----//
void		__count_env(void);
char		*variable_env(char *var);
void		update_var(char *var, char *str);
int			var_exist(char *str);
void		ft_command_execute(char ***commands, int in);
t_env		*create_var_env(char *env);
void		add_var_if_exist(char *var);
void		delete_var(char	*var);
char		*path_command(char *command);

//----Update and Destroy----//
void		__update(void);
void		__update_title(void);
void		__destroy(void);
void		__destroy_title(void);
void		__destroy_all(void);

//----Commands---//
t_command	*ft_cd(t_command *c);
t_command	*ft_echo(t_command *c);
t_command	*ft_env(t_command *c);
t_command	*ft_exit(t_command *c);
t_command	*ft_export(t_command *c);
t_command	*ft_pipe(t_command *c);
t_command	*ft_pwd(t_command *c);
t_command	*ft_unset(t_command *c);
t_command	*ft_redirect_right(t_command *c);
t_command	*ft_redirect_left(t_command *c);
t_command	*ft_double_redirect_right(t_command *c);
t_command	*ft_double_redirect_left(t_command *c);
t_command	*ft_double_and(t_command *c);
t_command	*ft_double_pipe(t_command *c);
t_command	*ft_parentheses(t_command *c);

#endif
