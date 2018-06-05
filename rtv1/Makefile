# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/15 11:20:25 by cpieri            #+#    #+#              #
#    Updated: 2018/06/02 15:20:59 by tmilon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	rtv1

CC		=	gcc

#CFLAGS	=	-Wall -Wextra -Werror
CFLAGS = -O2

L_SDL	=	$(shell pkg-config --libs sdl2)

I_SDL	= 	$(shell pkg-config --cflags sdl2)

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
			textures.c			\
			limit.c				\
			exit.c

OBJ_NAME=	$(SRC_NAME:.c=.o)

SRC		=	$(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ		=	$(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

.PHONY:	all clean fclean re

all:		LFT $(NAME)

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

LFT:	
		@if [ ! -d "./libft/libft.a" ]; then \
			make -C ./libft/; \
		else \
			echo "Libft was already installed"; \
		fi
