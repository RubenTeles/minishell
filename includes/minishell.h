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
# include <ft_input.h>

/* Para incluir readline passos:
sudo apt-get install libreadline-dev

https://vcpkg.io/en/getting-started.html
*/

typedef struct s_update 			t_update;
typedef struct s_destroy 			t_destroy;
typedef struct s_env 				t_env;
typedef struct s_terminal 			t_terminal;
typedef struct s_command 			t_command;

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
	int			fd[2];
	char		*title;
	int			env_count;
	char		**env_m;
	t_env		*env_l;
	char		**path;
	t_command	*start;
	t_update	*update;
	t_destroy	*destroy;
	void		(*add_var)(char *var);
	void		(*update_var)(char *var, char *str);
	void		(*delete_var)(char *var);
	void		(*execute)(char ***commands);
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
	void		(*execute)(t_command *c, int in);
	t_command	*next;
};

//----Utils----//
t_terminal	*terminal(void);
void		new_terminal(char **env);
void		create_env_l(char **env);
void		execute(t_command *c, int in);

//----Terminal Methods----//
void	__count_env(void);
char	*variable_env(char *var);
void	update_var(char *var, char *str);
int		var_exist(char *str);
void	ft_command_execute(char ***comamands);
t_env	*create_var_env(char *env);
void	add_var_if_exist(char *var);
void	delete_var(char	*var);

//----Update and Destroy----//
void		__update(void);
void 		__update_title(void);
void		__destroy(void);
void		__destroy_title(void);
void		__destroy_all(void);

//----Commands----//
char	*path_command(char *command);

//----Para Apagar---//
void	*ft_cd(t_command *c);
void	*ft_echo(t_command *c);
void	*ft_env(t_command *c);
void	*ft_exit(t_command *c);
void	*ft_export(t_command *c);
void	*ft_pipe(t_command *c);
void	*ft_pwd(t_command *c);
void	*ft_unset(t_command *c);

#endif
