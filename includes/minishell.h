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

/* Para incluir readline passos:
sudo apt-get install libreadline-dev

https://vcpkg.io/en/getting-started.html
*/


typedef struct s_input	t_input;

struct s_input {
	char	*line;
	int		objects;
	char	**values;
};

typedef struct s_terminal 			t_terminal;
typedef struct s_command 			t_command;

struct s_terminal {
	int			fd[2];
	t_command	*start;
	char		*title;
	int			env_count;
	char		**env_m;
	char		**path;
	char		**export;
	void		(*execute)(void);
	int			(*count_env)();
	char		*(*variable_env)(char *var);
	void		(*unset)(char *input);
	void		(*export_var)(char *var);
	void		(*destroy)();
};

struct s_command {
	int			fd[2];
	int			pid;
	char		**command;
	char		*path;
	void		(*execute)(t_command *c, int in);
	t_command	*next;
};

//----Utils----//
t_terminal	*terminal(void);
void		new_terminal(char *title, char **env);
t_input 	*inpt(void);

//----Terminal Methods----//
int 	__count_env(void);
char	*variable_env(char *var);
void 	ft_execute(void);

//----Commands----//
char	*path_command(char *command);

//----Para Apagar---//
void    ft_echo(char **input);
void    ft_env(char **input);
void    ft_pwd(char **input);

#endif
