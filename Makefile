# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/14 17:07:06 by aollivie          #+#    #+#              #
#    Updated: 2017/07/25 16:54:21 by alex             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


DEBUG=no
CC=clang

ifeq ($(DEBUG), yes)
				CFLAGS= -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter -O1 -g #-fsanitize=address -fno-omit-frame-pointer # -g -fsanitize=address,undefined # -g -ansi -pedantic
else
		# CFLAGS= -Wall -Wextra -Werror #-O1 -g #-fsanitize=address -fno-omit-frame-pointer
		# CFLAGS= -shared -fPIC -Wall -Wextra -Werror
		CFLAGS=
		# CFLAGS=  -Wall -Wextra -Werror
endif

NAME = ft_otool

LIBFT =libft/libft.a



I_DIR= -I inc/ -I./libft/inc

O_DIR= obj

MKDIR = mkdir

C_SRC = main.c

VPATH= .:src

OBJS= $(C_SRC:%.c=$(O_DIR)/%.o)

.PHONY : all clean fclean re

all :
	make -C libft
	make -j $(NAME)

ifeq ($(DEBUG),yes)
				@echo "Generation mode debug"
else
				@echo "Generation mode release"
endif

$(NAME):$(OBJS)
				$(CC) $(CFLAGS) $(I_DIR) $^  $(LIBFT) -o $@


$(O_DIR)/%.o: %.c
				$(CC) $(CFLAGS) $(I_DIR) -c $< -o $@

$(OBJS): | $(O_DIR)

$(O_DIR):
				$(MKDIR) $(O_DIR)
clean :
		rm -rf $(O_DIR)
		make clean -C libft

fclean : clean
		@rm -rf $(NAME) libft_malloc.so
		make fclean -C libft

re : fclean all
