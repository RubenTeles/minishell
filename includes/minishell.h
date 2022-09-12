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


typedef struct s_destroy 			t_destroy;
typedef struct s_env 				t_env;
typedef struct s_terminal 			t_terminal;
typedef struct s_command 			t_command;

struct s_destroy {
	void		(*all)(void);
	void		(*env_l)(void);
	void		(*env_m)(void);
	void		(*path)(void);
	void		(*commands)(void);
};

struct s_env {
	char	*var;
	char	*val;
	t_env	*next;
};

struct s_terminal {
	int			fd[2];
	t_command	*start;
	char		*title;
	int			env_count;
	char		**env_m;
	t_env		*env_l;
	char		**path;
	t_destroy	*destroy;
	void		(*execute)(char ***commands);
	void		(*count_env)(void);
	char		*(*variable_env)(char *var);
	void		(*update_var)(char *var, char *str);
	void		(*unset)(char *input);
	void		(*export_var)(char *var);
	void		(*create_path)(void);
	int			(*index_var)(char *str);
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
void		new_terminal(char *title, char **env);
void		create_env_l(char **env);

//----Terminal Methods----//
void	__count_env(void);
char	*variable_env(char *var);
void	update_var(char *var, char *str);
int		index_var(char *str);
void	ft_command_execute(char ***comamands);
void	__destroy(void);
void	__destroy_all(void);


//----Commands----//
char	*path_command(char *command);

//----Para Apagar---//
t_command	*ft_echo(char **input);
t_command	*ft_cd(char **input);
t_command	*ft_env(char **input);
t_command	*ft_pwd(char **input);
t_command	*ft_pipe(char **input);
t_command	*ft_exit(char **input);
t_command	*ft_export(char **input);
t_command	*ft_choise(char **command);

//----TESTE----//
void	ft_pipex(char ***comands);

#endif
