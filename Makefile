# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/17 18:52:37 by ede-alme          #+#    #+#              #
#    Updated: 2022/08/19 19:57:55 by ede-alme         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_PATH = ./srcs/
OBJ_PATH = ./objs/
INC_PATH = ./includes/

SRC_NAME = 	main.c \
			#ft_split.c \
			#ft_strnstr.c \
			#create_terminal.c \

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

CC = gcc
CFLAGS = -g -lreadline #-fsanitize=address -Wall -Wextra -Werror

$(OBJ_PATH)%.o:$(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -I $(INC_PATH) -o $@ -c $< -L/usr/local/lib -I/usr/local/include -lreadline

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ -L/usr/local/lib -I/usr/local/include -lreadline

all: $(NAME)

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re