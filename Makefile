# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbie <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/15 11:55:43 by pbie              #+#    #+#              #
#    Updated: 2016/05/19 14:54:01 by pbie             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CFLAGS = -g -Wall -Werror -Wextra -I includes

SRC = srcs/main.c \
			srcs/printcolor.c \
			srcs/checks.c \
			srcs/setup.c \
			srcs/flags.c \
			srcs/path.c \
			srcs/alphaspace.c \
			srcs/print.c \
			srcs/printpermissions.c \
			srcs/lg_r.c \
			srcs/lists.c \
			srcs/ft_list_swap.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@make -C libft
	@gcc $(CFLAGS) -o $(NAME) $(OBJ) -I libft/includes/libft.h libft/libft.a
	@echo "$(NAME) created"

clean :
	make -C libft clean
	rm -rf $(OBJ)
	@echo "OBJ deleted"

fclean : clean
	rm -rf $(NAME)
	rm -rf libft/libft.a
	@echo "$(NAME) deleted"

re : fclean all

.PHONY: all clean fclean re
