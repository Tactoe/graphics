# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blsegal <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/05 12:14:54 by blsegal           #+#    #+#              #
#    Updated: 2018/02/06 13:18:48 by tmilon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
SRC = main.c get_data.c display.c init_struct.c inputs.c
INC  = ./minilibx_macos/
FRAMEWORK = -framework OpenGL -framework AppKit
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Werror -Wextra
CC = gcc
LIST_OBJS = $(LIST_SRCS:$(SRCS)/%.c=$(OBJS)/%.o)
CFLAGS = -Werror -Wextra -Wall
LIBFT = libft/
INC_LIBFT = $(LIBFT)

all : $(NAME)

$(NAME) : libft $(OBJ)
	make -C libft
	gcc $(CFLAGS) -I $(INC) -I $(INC_LIBFT) -L $(LIBFT) -lft $(OBJ) -o $(NAME) minilibx_macos/libmlx.a $(FRAMEWORK)

clean :
	/bin/rm -f $(OBJ)
	make clean -C libft

fclean : clean
		 make fclean -C libft
		 /bin/rm -f $(NAME)

re : fclean all
