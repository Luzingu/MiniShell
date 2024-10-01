# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/30 15:58:50 by mcaquart          #+#    #+#              #
#    Updated: 2024/10/01 00:44:22 by mcaquart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= 	minishell
CC				= 	cc
CFLAGS			= 	-Wall -Wextra -Werror
LDFLAGS			= 	-lreadline
LIBFT			= 	./libft
SRC				=	source/main.c							\
					source/token/token.c					\
					source/token/utils.c					\
					source/execute.c						\
					source/redir.c							\
					source/execute_builtin.c				\
					source/builtins/ft_echo.c				\
					source/builtins/ft_cd.c					\
					source/builtins/ft_pwd.c				\
					source/builtins/ft_exit.c				\
					source/environment/expand_variable.c	\
					source/environment/ft_export.c				\
					source/environment/ft_unset.c				\
					source/environment/ft_env.c				\
					source/ft_verifying_line.c				\
					source/ft_verifying_argument.c			\
					source/execute_cmd.c\
					source/shell_lavel.c\
					source/ft_free.c\
					source/heredoc.c\
					source/signal.c \
					source/utils_token.c\
					source/utils.c
OBJ		= $(SRC:.c=.o)

MAKEFLAGS	+= -silent

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT)
	$(CC) $(OBJ) $(LDFLAGS) $(LIBFT)/libft.a -o $(NAME)

clean:
	@make clean -C $(LIBFT)
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C $(LIBFT)
	@rm -rf $(NAME)

re: fclean all
