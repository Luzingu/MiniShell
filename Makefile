# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aluzingu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/08 16:43:35 by aluzingu          #+#    #+#              #
#    Updated: 2024/07/08 16:43:36 by aluzingu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = push_swap
RM = rm -drf
SRC_PATH = src/
OBJ_PATH = obj/
INC = ./includes
DIR = ./src/

SRCS = main.c utils.c utils2.c utils3.c utils4.c utils5.c utils6.c initialization.c push.c rev_rotate.c rotate.c swap.c ft_split.c

OBJS = $(addprefix $(OBJ_PATH), $(SRCS:.c=.o))

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJ_PATH)

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(OBJS): | $(OBJ_PATH)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

