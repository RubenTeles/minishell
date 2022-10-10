/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 02:41:51 by rteles            #+#    #+#             */
/*   Updated: 2022/10/10 21:35:14 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WILDCARD_H
# define FT_WILDCARD_H

# include <minishell.h>
# include <dirent.h>

typedef struct s_wildcard			t_wildcard;
typedef struct s_list				t_list;
struct s_wildcard {
	char			*begin;
	char			**med;
	char			*final;
	char			*word;
	int				all;
	int				in_dir;
	char			*path;
	char			*parent;
	struct dirent	*rdir;
	t_wildcard		*next_dir;
};

struct s_list {
	char	*command;
	t_list	*next;
};

/*---Create---*/
void		ft_call(void);
char		**ft_wildcard(char	*command);
t_list		*begin(t_list *list, char *wildcard, char *path);
void		__destroy_wildcard(t_wildcard *w);

/*---Create 2---*/
t_wildcard	*create_wildcard(char *wildcard, int dir);
void		create_wildcard_2(t_wildcard *w, char *wildcard);
char		*wildcard_med(t_wildcard *w, char *sub);

/*---Validation---*/
int			ft_valid(t_wildcard *w, char *str, int i, int aux);
int			ft_valid_start(char *str, char *start);
int			ft_valid_final(char *str, char *final);
int			ft_valid_med(char *str, char *med, int i);

/*---Wildcard---*/
t_list		*ft_wildcard_valid(t_wildcard *w, t_list *l);
char		**ft_new_flags(t_list *list, int i);

/*---Utils---*/
t_list		*create_list(char *str);
char		**copy_double_string_and_free(char **src, char **dest, int extra);
int			is_dir_type(int type);
int			ft_hiden_files(t_wildcard *w, char *file, DIR *dir);

#endif
