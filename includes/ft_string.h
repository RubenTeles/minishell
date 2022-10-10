/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:38:50 by rteles            #+#    #+#             */
/*   Updated: 2022/10/10 01:08:04 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_string				t_string;
struct s_string {
	size_t	(*len)(const char *string);
	char	**(*split)(char const *s, char c);
	char	*(*n_str)(const char *s1, const char *s2, size_t n);
	int		(*copy_n)(char *dest, const char *src, int size);
	char	*(*join)(char const *s1, char const *s2);
	int		(*only_this_chars)(char *s1, char *s2);
	char	*(*pos_char)(const char *string, int c);
	char	*(*pos_char_last)(const char *string, int c);
	char	*(*duplicate)(const char *s);
	int		(*compare)(char*s1, char*s2);
	int		(*compare_n)(const char *str1, const char *str2, size_t n);
	char	*(*sub_str)(char const *s, unsigned int start, size_t len);
	char	*(*sub_str_chars)(char *str, char c1, char c2);	
	char	*(*sub_split_option)(char *str, char c, int option);
	char	*(*replace)(char *str1, char *str2);
	int		(*index_char)(char *str, char c);
	int		(*str_in_int)(char *str);
	char	*(*int_in_str)(int n);
	int		(*is_alfanumeric)(char *str);
};

size_t		ft_strlen(const char *string);
char		**ft_split(char const *s, char c);
char		*ft_strnstr(const char *s1, const char *s2, size_t n);
int			ft_strlcpy(char *dest, const char *src, int size);
char		*ft_strdup(const char *s);
int			ft_strncmp(const char *str1, const char *str2, size_t n);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_string_in_two_char(char *str, char c1, char c2);
char		*replace_str(char *str1, char *str2);
int			index_char(char *str, char c);
char		*split_two_str(char *str, char c, int option);
int			ft_atoi(char *str);
char		*ft_itoa(int n);
int			ft_isalnum(char *str);
int			ft_strcmp(char*s1, char*s2);
t_string	*string(void);

#endif
