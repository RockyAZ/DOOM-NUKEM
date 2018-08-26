#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azaporoz <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/27 18:52:16 by azaporoz          #+#    #+#              #
#    Updated: 2018/06/25 20:07:23 by azaporoz         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = gcc
SOURCE = ft_atoi.c \
			ft_bzero.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_strcat.c \
			ft_strchr.c \
			ft_strcmp.c \
			ft_strcpy.c \
			ft_strdup.c \
			ft_strlcat.c \
			ft_strlen.c \
			ft_strncat.c \
			ft_strncmp.c \
			ft_strncpy.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strstr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_memalloc.c \
			ft_memdel.c \
			ft_strnew.c \
			ft_strdel.c \
			ft_strclr.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strmap.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strequ.c \
			ft_strnequ.c \
			ft_strsub.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_strsplit.c \
			ft_itoa.c \
			ft_putchar.c \
			ft_putstr.c \
			ft_putendl.c \
			ft_putnbr.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_lstnew.c \
			ft_lstdelone.c \
			ft_lstdel.c \
			ft_lstadd.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_swap.c \
			ft_sqrt.c \
			ft_countint.c \
			ft_demcalc.c \
			ft_strrev.c \
			get_next_line.c \
			ft_abs.c \
			ft_count_words.c \
			ft_max.c \
			ft_min.c \
			ft_putnbr_end.c \


HEADER = ./libft.h
OBJECTS = $(SOURCE:.c=.o)
NAME = libft.a
RM = rm -f

all: print $(NAME)
	@printf "\033[0;32m\n\n\nLIBFT DONE\n\n"

print:
	@printf "\033[0;32mSTART LOADING LIBFT\n\n\n"

$(NAME): $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
		@printf "\033[0;31m ->"
clean:
	@$(RM) $(OBJECTS)
	@printf "\033[0;35m\
░░░░░░░░░░▄▄▀▀▀▀▀▀▀▀▄▄\n\
░░░░░░░░▄▀▀░░░░░░░░░░░░▀▄▄\n\
░░░░░░▄▀░░░░░░░░░░░░░░░░░░▀▄\n\
░░░░░▌░░░░░░░░░░░░░▀▄░░░░░░░▀▀▄\n\
░░░░▌░░░░░░░░░░░░░░░░▀▌░░░░░░░░▌\n\
░░░▐░░░░░░░░░░░░▒░░░░░▌░░░░░░░░▐\n\
░░░▌▐░░░░▐░░░░▐▒▒░░░░░▌░░░░░░░░░▌\n\
░░▐░▌░░░░▌░░▐░▌▒▒▒░░░▐░░░░░▒░▌▐░▐\n\
░░▐░▌▒░░░▌▄▄▀▀▌▌▒▒░▒░▐▀▌▀▌▄▒░▐▒▌░▌\n\
░░░▌▌░▒░░▐▀▄▌▌▐▐▒▒▒▒▐▐▐▒▐▒▌▌░▐▒▌▄▐\n\
░▄▀▄▐▒▒▒░▌▌▄▀▄▐░▌▌▒▐░▌▄▀▄░▐▒░▐▒▌░▀▄\n\
▀▄▀▒▒▌▒▒▄▀░▌█▐░░▐▐▀░░░▌█▐░▀▄▐▒▌▌░░░▀\n\
░▀▀▄▄▐▒▀▄▀░▀▄▀░░░░░░░░▀▄▀▄▀▒▌░▐\n\
░░░░▀▐▀▄▒▀▄░░░░░░░░▐░░░░░░▀▌▐\n\
░░░░░░▌▒▌▐▒▀░░░░░░░░░░░░░░▐▒▐\n\
░░░░░░▐░▐▒▌░░░░▄▄▀▀▀▀▄░░░░▌▒▐\n\
░░░░░░░▌▐▒▐▄░░░▐▒▒▒▒▒▌░░▄▀▒░▐\n\
░░░░░░▐░░▌▐▐▀▄░░▀▄▄▄▀░▄▀▐▒░░▐\n\
░░░░░░▌▌░▌▐░▌▒▀▄▄░░░░▄▌▐░▌▒░▐\n\
░░░░░▐▒▐░▐▐░▌▒▒▒▒▀▀▄▀▌▐░░▌▒░▌\n\
░░░░░▌▒▒▌▐▒▌▒▒▒▒▒▒▒▒▐▀▄▌░▐▒▒﻿\n\
ALL CLEAN\n"

fclean: clean
	@$(RM) $(NAME)
	@echo "\033[0;31mALL F_CLEAN"

re: fclean all
	@echo "\033[0;33mALL RE"