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
			error.c \
			bsp.c \
			vector_calc.c \
			angle_calc.c \
			add_func.c \
			draw.c
# drawing_wall.c			
all:
	gcc -o doom-nukem $(SOURCE) libft/libft.a -I./libft/ -I./Frameworks/SDL2.framework/Headers\
	 		   -I./Frameworks/SDL2_image.framework/Headers\
				-rpath @loader_path/Frameworks -F./Frameworks/ -framework SDL2 -framework SDL2_image