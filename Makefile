# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/26 12:51:50 by seshevch          #+#    #+#              #
#    Updated: 2019/02/01 13:54:12 by seshevch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

LIB = libft/libft.a

FLAGS = -Wall -Wextra -Werror -g

SRCS = main.c

OBJ = main.o

INCL = ./libft/includes

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
		gcc $(FLAGS) $(OBJ) $(LIB) -o $(NAME)

$(OBJ): %.o: %.c
		gcc $(FLAGS) -c $< -o $@ -I $(INCL)

$(LIB):
		make -C ./libft

clean:
		rm -rf $(OBJ)
		make clean -C ./libft

fclean: clean
		make fclean -C ./libft
		rm -rf $(NAME)

re: fclean all
