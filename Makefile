#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpfeffer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/24 17:50:14 by jpfeffer          #+#    #+#              #
#    Updated: 2017/04/24 17:58:15 by jpfeffer         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

LEMIN = lem-in

C_FILES = lem-in.c

LIBFT		=	./libft/libft.a
PRINTF		=	./libraries/ft_printf/libftprintf.a
GNL			=	./libraries/get_next_line/libgnl.a
LIBLINK		=	-L ./libraries -llem-in
LIBRARY		=	./libraries/liblem-in.a

SRCS = $(C_FILES)

C_FLAGS = -Wall -Werror -Wextra

.PHONY: all library libft printf gnl test clean fclean re

all: library $(LEMIN)

library: libft printf gnl $(LIBRARY)

$(LIBRARY):
	@libtool -static -o ./libraries/liblem-in.a $(LIBFT) $(PRINTF) $(GNL)

libft: $(LIBFT)

$(LIBFT):
	@make -C ./libft

printf: $(PRINTF)

$(PRINTF):
	@make -C ./libraries/ft_printf

gnl: $(GNL)

$(GNL):
	@make -C ./libraries/get_next_line

$(LEMIN): $(C_FILES) lem-in.h
	@gcc $(C_FLAGS) $(LIBLINK) $(SRCS) -o lem-in

test: fclean library
	@gcc $(SRCS) $(LIBLINK) -o lem-in

ftest: fclean library
	@gcc $(SRCS) $(LIBLINK) -fsanitize=address -o lem-in

clean:
	@make clean -C ./libft
	@make clean -C ./libraries/ft_printf
	@make clean -C ./libraries/get_next_line

fclean: clean
	@rm -f $(LIBRARY) a.out lem-in
	@make fclean -C ./libft
	@make fclean -C ./libraries/ft_printf
	@make fclean -C ./libraries/get_next_line

re: fclean all