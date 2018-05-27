# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/15 11:20:25 by cpieri            #+#    #+#              #
#    Updated: 2018/05/27 14:10:15 by tmilon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	rtv1

CC		=	gcc

#CFLAGS	=	-Wall -Wextra -Werror

L_SDL	=	$(shell pkg-config --libs sdl2/lib/pkgconfig/sdl2.pc)

I_SDL	= 	$(shell pkg-config --cflags sdl2/lib/pkgconfig/sdl2.pc)

SDL_VER	=	2.0.8

PATH_SDL=	$(addprefix $(PWD), /sdl2)

CPPFLAGS=	-Iincludes

FLAGSFT	=	-L./libft -lft

SRC_PATH=	srcs

OBJ_PATH=	obj

SRC_NAME= 	main.c				\
			display.c			\
			init_struct.c		\
			inputs.c			\
			colors.c 			\
			utils.c				\
			vector.c			\
			intersection.c		\
			normal.c			\
			parsing.c 			\
			create_obj.c		\
			camera.c			\
			img.c				\
			matrix.c			\
			rotation_matrix.c	\
			ray_adapter.c		\
			parse_2.c			\
			light.c				\
			exit.c				\
			textures.c

OBJ_NAME=	$(SRC_NAME:.c=.o)

SRC		=	$(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ		=	$(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

.PHONY:	all clean fclean re

all:		LFT SDL2 $(NAME)

$(NAME):	libft $(OBJ)
			@make -C libft
			$(CC) $(CFLAGS) $(FLAGSFT) -lpthread -o $(NAME) $(OBJ) $(CPPFLAGS)\
			$(L_SDL) $(I_SDL)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
			@mkdir $(OBJ_PATH) 2> /dev/null || true
			@$(CC) $(CFLAGS) $(CPPFLAGS) $(I_SDL) -o $@ -c $<

clean:
			@echo "cleaning"
			@make clean -C ./libft/
			@/bin/rm -f $(OBJ)
			@rmdir $(OBJ_PATH) 2> /dev/null || true
			@/bin/rm -rf $(PATH_SDL)

fclean:		clean
			@make fclean -C ./libft/
			@/bin/rm -f $(NAME)

re:			fclean all

SDL2:
		@if [ ! -d "./sdl2" ]; then \
			echo "Compiling sdl2..."; \
			curl -OL http://www.libsdl.org/release/SDL2-$(SDL_VER).tar.gz && \
			tar -zxf SDL2-$(SDL_VER).tar.gz && \
			rm SDL2-$(SDL_VER).tar.gz && \
			mkdir -p $(PATH_SDL) && \
			cd SDL2-$(SDL_VER) && \
			sh configure -q --prefix=$(PATH_SDL) && \
			make && \
			make install && \
			cd .. && \
			rm -rf SDL2-$(SDL_VER); \
		else \
			echo "SDl2-$(SDL_VER) already installed"; \
		fi

LFT:	
		@if [ ! -d "./libft/libft.a" ]; then \
			make -C ./libft/; \
		else \
			echo "Libft was already installed"; \
		fi
