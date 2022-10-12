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

ORANGE = \033[0;33m
GREEN = \033[0;32m
RED = \033[0;31m
SRC_PATH = ./srcs/
SRC_PATH_COMMANDS = ./srcs/commands/
SRC_PATH_TERM = ./srcs/terminal/
SRC_PATH_STRING = ./srcs/string/
SRC_PATH_INPUT = ./srcs/input/
SRC_PATH_WILDCARD = ./srcs/wildcard/
OBJ_PATH = ./objs/
INC_PATH = ./includes/

SRC_NAME = 	main.c \

SRC_COMMANDS = 	ft_cd.c \
				ft_choice.c \
				ft_echo.c \
				ft_env.c \
				ft_exit.c \
				ft_export.c \
				ft_pipe.c \
				ft_pwd.c \
				ft_unset.c \
				ft_redirect_right.c \
				ft_redirect_left.c \
				ft_double_redirect_right.c \
				ft_double_redirect_left.c \
				ft_redict_utils.c \
				ft_management_execute.c \
				ft_double_and.c \
				ft_double_pipe.c \
				ft_d_and_pipe_utils.c \
				ft_parentheses.c \
				ft_parentheses_utils.c \

SRC_TERMINAL = 	create_terminal.c \
				create_terminal_2.c \
				terminal_methods.c \
				terminal_methods_2.c \
				_update.c \
				_update_2.c \
				_destroy.c \

SRC_STRING = 	ft_string.c \
				ft_string_2.c \
				ft_string_3.c \
				ft_string_4.c \
				ft_string_5.c \
				
SRC_INPUT = 	parser.c \
				1cotes.c \
				2create_token.c \
				3pipe.c \
				4create_data.c \
				format_token.c \
				free_input.c \
				wildcard.c \
				utils.c \

SRC_WILDCARD = 	ft_wildcard_create.c \
				ft_wildcard_create_2.c \
				ft_wildcard_validation.c \
				ft_wildcard_utils.c \
				ft_wildcard.c \


SRC = $(SRC_NAME) $(SRC_TERMINAL) $(SRC_STRING) $(SRC_INPUT) $(SRC_COMMANDS) $(SRC_WILDCARD)

OBJ_NAME = $(SRC:.c=.o)

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

CC = gcc

CFLAGS = -g -lreadline -Wall -Wextra -Werror -fsanitize=address

$(OBJ_PATH)%.o:$(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -I $(INC_PATH) -o $@ -c $< -L/usr/local/lib -I/usr/local/include -lreadline

$(OBJ_PATH)%.o:$(SRC_PATH_TERM)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -I $(INC_PATH) -o $@ -c $< -L/usr/local/lib -I/usr/local/include -lreadline

$(OBJ_PATH)%.o:$(SRC_PATH_STRING)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -I $(INC_PATH) -o $@ -c $< -L/usr/local/lib -I/usr/local/include -lreadline

$(OBJ_PATH)%.o:$(SRC_PATH_INPUT)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -I $(INC_PATH) -o $@ -c $< -L/usr/local/lib -I/usr/local/include -lreadline

$(OBJ_PATH)%.o:$(SRC_PATH_COMMANDS)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -I $(INC_PATH) -o $@ -c $< -L/usr/local/lib -I/usr/local/include -lreadline

$(OBJ_PATH)%.o:$(SRC_PATH_WILDCARD)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -I $(INC_PATH) -o $@ -c $< -L/usr/local/lib -I/usr/local/include -lreadline

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $@ -L/usr/local/lib -I/usr/local/include -lreadline
	@echo "\
	$(GREEN)**************************************************\n\
	** $(ORANGE)                     __        ___           $(GREEN)**\n\
	** $(ORANGE)|\  /| O |\   | O   |  \ |  | |    |    |    $(GREEN)**\n\
	** $(ORANGE)| \/ | | | \  | |   \__  |__| |__  |    |    $(GREEN)**\n\
	** $(ORANGE)|    | | |  \ | |      | |  | |    |    |    $(GREEN)**\n\
	** $(ORANGE)|    | | |   \| |   \__/ |  | |___ |___ |___ $(GREEN)**\n\
	** $(ORANGE)                                             $(GREEN)**\n\
	**************************************************\n\
	** $(ORANGE)       rteles              ede-alme          $(GREEN)**\n\
	**************************************************\033[0;37m"

all: $(NAME)

clean:
	@rm -rf $(OBJ_PATH)
	@echo "$(RED)Clean!"

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re