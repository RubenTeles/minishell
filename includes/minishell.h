/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:03:04 by ede-alme          #+#    #+#             */
/*   Updated: 2022/08/20 14:21:26 by ede-alme         ###   ########.fr       */
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

/* Para incluir readline passos:
sudo apt-get install libreadline-dev
https://vcpkg.io/en/getting-started.html
*/

typedef struct s_terminal	t_terminal;

struct s_terminal {
	char	*title;
	char	***input;
	int		env_n;
	char	**env_m;
	char	**path;
	char	**export;
	int		(*count_env)();
	void	(*unset)(char *input);
	void	(*destroy)();
};

//----Utils----//
char		**ft_split(char const *s, char c);
size_t		ft_strlen(const char *string);
char		*ft_strnstr(const char *s1, const char *s2, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
t_terminal	*terminal(void);
void		new_terminal(char *title, char **env);

#endif
