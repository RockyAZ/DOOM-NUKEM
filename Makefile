#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azaporoz <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/23 17:30:31 by azaporoz          #+#    #+#              #
#    Updated: 2018/07/23 17:30:31 by azaporoz         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SOURCE = main.c \
			additional.c \
			error.c \
			reader.c \
			prepare.c \
			ray_casting.c \
			draw_line.c \
			action.c \
			mouse.c \
			ray_simple.c \
			keys.c \

all:
	gcc -o wolf3d $(SOURCE) libft/libft.a -I./libft/ -I./Frameworks/SDL2.framework/Headers\
	 		   -I./Frameworks/SDL2_image.framework/Headers\
				-rpath @loader_path/Frameworks -F./Frameworks/ -framework SDL2 -framework SDL2_image

# NAME = wolf3d
# FLAGS = -Wall -Wextra -Werror
# SOURCE = main.c \
# 			additional.c \
# 			error.c \
# 			reader.c \
# 			prepare.c \
# 			ray_casting.c \
# 			draw_line.c \
# 			action.c \
# 			mouse.c \
# 			ray_simple.c \
# 			keys.c \

# HEADER = wolf.h
# OBJECTS = $(addprefix $(OBJDIR),$(SOURCE:.c=.o))
# OBJDIR = ./obj/

# SDL = -I./Frameworks/SDL2.framework/Headers -I./Frameworks/SDL2_image.framework/Headers -rpath @loader_path/Frameworks -F./Frameworks/ -framework SDL2 -framework SDL2_image

# SOIL_INC = -I ./inclide/
# SOIL_LIB = ./include/libSOIL.a

# LIBFT_INC = -I ./libft/
# LIBFT = ./libft/libft.a

# FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

# all: obj $(LIBFT) $(NAME)
# 	@printf "\033[0;31m\
# 卐卐卐卐卐卐卐卐卐▄▄卐卐卐卐卐卐卐卐卐卐\n\
# 卐卐卐卐卐卐卐▄▀卐卐▀▄卐卐卐卐卐卐卐卐卐\n\
# 卐卐卐卐卐卐▄▀卐卐卐▄▀█卐卐卐卐卐卐卐卐卐\n\
# 卐卐卐卐卐▄▀卐卐卐▄▀░▄▀░▄▀▄▄卐卐卐卐卐卐\n\
# 卐卐卐卐▄▀卐卐卐▄▀░▄▀░▄▀卐卐▀▄卐卐卐卐卐\n\
# 卐卐卐卐█▀▄卐卐卐▀█░▄▀卐卐卐卐▀▄卐卐卐卐\n\
# 卐卐▄▀▄░▀▄░▀▄卐卐卐▀卐卐卐▄█▄卐卐▀▄卐卐\n\
# 卐▄▀卐卐▀▄░▀▄░▀▄卐卐卐卐▄▀░█░▀▄卐卐▀▄卐\n\
# 卐█▀▄卐卐卐▀▄░█▀卐卐卐卐▀█░▀▄░▀▄░▄▀█卐\n\
# 卐▀▄░▀▄卐卐卐▀卐卐卐▄█▄卐卐卐▀▄░▀▄░█░▄▀\n\
# 卐卐▀▄░▀▄卐卐卐卐▄▀░█░▀▄卐卐卐▀▄░▀█▀卐卐\n\
# 卐卐卐▀▄░▀▄░▄▀░▄▀░█▀卐卐卐▄▀█卐卐卐卐卐\n\
# 卐卐卐卐▀▄░█░▄▀░▄▀卐卐卐▄▀░▄▀卐卐卐卐卐\n\
# 卐卐卐卐卐▀█▀░▄▀卐卐卐▄▀░▄▀卐卐卐卐卐卐\n\
# 卐卐卐卐卐卐卐卐█▀▄░▄▀░▄▀卐卐卐卐卐卐卐\n\
# 卐卐卐卐卐卐卐卐▀▄░█░▄▀卐卐卐卐卐卐卐卐\n\
# 卐卐卐卐卐卐卐卐卐▀█▀卐卐卐卐卐卐卐卐卐\n"

# obj:
# 	@mkdir -p $(OBJDIR)

# $(OBJDIR)%.o: %.c $(HEADER)
# 	@printf "\033[0;34m->    "
# 	gcc $(FLAGS) $(LIBFT_INC) -o $@ -c $<
# 	@printf "\n"

# $(NAME): $(OBJECTS)
# 	@gcc -o $(NAME) $(OBJECTS) $(SDL) $(SOIL_INC) $(SOIL_LIB) $(LIBFT) $(LIBFT_INC) $(FRAMEWORKS)

# $(LIBFT):
# 	@make -C ./libft/
# 	@printf "\033[0;32m\n\n|||||||||||||||||||||\nSTART LOADING WOLF\n|||||||||||||||||||||\n\n\n\n"

# clean:
# 	@/bin/rm -f $(OBJECTS)
# 	@/bin/rm -rf $(OBJDIR)
# 	@make clean -C ./libft/

# fclean: clean
# 	@make fclean -C ./libft/
# 	@/bin/rm -f $(NAME)

# re: fclean all
