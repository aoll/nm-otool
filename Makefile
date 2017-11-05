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



I_DIR= -I inc/ -I./libft/inc -I inc/en

ifeq ($(LANG),fr)
	I_DIR= -I inc/ -I./libft/inc -I inc/fr
endif

O_DIR= obj

MKDIR = mkdir

C_SRC =	check_valid_file.c \
		free_sort.c \
		ft_ar_file.c \
		ft_check_load.c \
		ft_copy_nlist.c \
		ft_copy_nlist64.c \
		ft_fat_file.c \
		ft_find_section.c \
		ft_find_section_64.c \
		ft_find_segment.c \
		ft_find_segment_64.c \
		ft_find_segment_section.c \
		ft_find_segment_section_64.c \
		ft_format_archive_name.c \
		ft_get_adress_str.c \
		ft_infos_segment.c \
		ft_infos_segment_64.c \
		ft_init_seg_infos.c \
		ft_otool.c \
		ft_print_adress.c \
		ft_print_archive_name.c \
		ft_print_padding_adresse.c \
		ft_sort.c \
		ft_sort64.c \
		handle.c \
		handle_64.c \
		handle_64_text.c \
		handle_text.c \
		main.c \
		print_outpout.c \
		print_outpout_64.c \
		print_outpout_format.c \
		print_outpout_format_64.c \
		print_text_text_section.c \
		sort_and_print_outpout.c \
		sort_and_print_outpout_64.c \
		swap_uint32.c

VPATH= src

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
