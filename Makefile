# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aluzingu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/30 15:58:50 by mcaquart          #+#    #+#              #
#    Updated: 2024/09/14 00:39:42 by aluzingu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
LDFLAGS = -lreadline
LIBFT	= ./libft
SRC		=	source/main.c\
			source/read.c\
			source/execute.c\
			source/builtins/ft_cd.c\
			source/builtins/ft_exit.c\
			source/environment/executable.c\
			source/environment/expand_variable.c\
			source/environment/export.c\
			source/environment/unset.c\
			source/utils/util.c\
			source/utils/split_advenced.c
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
