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

struct s_terminal {
	char	*title;
	int		env_count;
	char	**env_m;
	char	**path;
	char	**export;
	void	(*execute)(char *path_command);
	int		(*count_env)();
	char	*(*variable_env)(char *var);
	void	(*unset)(char *input);
	void	(*export_var)(char *var);
	void	(*destroy)();
};

//----Utils----//
t_terminal	*terminal();
void		new_terminal(char *title, char **env);

//----Terminal Methods----//
int 	__count_env(void);
char	*variable_env(char *var);
void	ft_execute(char *path_command);

//----Commands----//
char	*path_command(char *command);

#endif
