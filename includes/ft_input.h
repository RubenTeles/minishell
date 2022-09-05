/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:14:11 by rteles            #+#    #+#             */
/*   Updated: 2022/09/05 22:40:19 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_INPUT_H
# define FT_INPUT_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_token	t_token;
typedef struct s_cms	t_cms;
typedef struct s_data	t_data;

struct s_token{
	char	*token;
	t_token	*next;
};

struct s_cms {
	char	**commands;
	t_cms	*next;
};

struct s_data {
	char	*comando[20][20];
	char	***comands;
	t_token	*input;
	t_cms	*start;
	int		max_c;
	int		*size;
};

void	get_comando(char *line, t_data *data);
t_data *data(void);

#endif