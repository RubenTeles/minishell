# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/17 18:52:37 by ede-alme          #+#    #+#              #
#    Updated: 2022/08/23 20:19:01 by ede-alme         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_PATH = ./srcs/
SRC_PATH_COMMANDS = ./srcs/commands/
SRC_PATH_TERM = ./srcs/terminal/
SRC_PATH_STRING = ./srcs/string/
SRC_PATH_INPUT = ./srcs/input/
OBJ_PATH = ./objs/
INC_PATH = ./includes/

SRC_NAME = 	main.c \

SRC_COMMANDS = 	ft_echo.c \
				ft_choise.c \
				ft_cd.c \
				ft_env.c \
				ft_exit.c \
				ft_pwd.c \

SRC_TERMINAL = 	create_terminal.c \
				terminal_methods.c \
				commands_1.c \
				ft_execute.c \

SRC_STRING = 	ft_string.c \
				ft_string_2.c \
				ft_string_3.c \
				ft_string_4.c \
				ft_string_5.c \
				
SRC_INPUT = 	input_1.c \

SRC = $(SRC_NAME) $(SRC_TERMINAL) $(SRC_STRING) $(SRC_INPUT) $(SRC_COMMANDS)

OBJ_NAME = $(SRC:.c=.o)

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

CC = gcc
CFLAGS = -g -lreadline #-fsanitize=address -Wall -Wextra -Werror

$(OBJ_PATH)%.o:$(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -I $(INC_PATH) -o $@ -c $< -L/usr/local/lib -I/usr/local/include -lreadline

$(OBJ_PATH)%.o:$(SRC_PATH_TERM)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -I $(INC_PATH) -o $@ -c $< -L/usr/local/lib -I/usr/local/include -lreadline

$(OBJ_PATH)%.o:$(SRC_PATH_STRING)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -I $(INC_PATH) -o $@ -c $< -L/usr/local/lib -I/usr/local/include -lreadline

$(OBJ_PATH)%.o:$(SRC_PATH_INPUT)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -I $(INC_PATH) -o $@ -c $< -L/usr/local/lib -I/usr/local/include -lreadline

$(OBJ_PATH)%.o:$(SRC_PATH_COMMANDS)%.c
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