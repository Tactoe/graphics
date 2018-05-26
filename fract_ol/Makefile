# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blsegal <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/05 12:14:54 by blsegal           #+#    #+#              #
#    Updated: 2018/02/14 14:55:29 by tmilon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
SRC = main.c fracts.c display.c init_struct.c inputs.c colors.c \
	  utils.c inputs_mouse.c antialiasing.c
INC  = minilibx_macos/
FRAMEWORK = -framework OpenGL -framework AppKit
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Werror -Wextra
CC = gcc
LIST_OBJS = $(LIST_SRCS:$(SRCS)/%.c=$(OBJS)/%.o)
LIBFT = libft/
MLX = minilibx_macos/
INC_LIBFT = $(LIBFT)

all : $(NAME)

$(NAME) : libft $(OBJ)
	make -C libft
	make -C $(MLX)
	gcc $(CFLAGS) -I $(INC) -I $(INC_LIBFT) -L $(LIBFT) -lft $(OBJ) -o $(NAME) $(MLX)/libmlx.a $(FRAMEWORK)

clean :
	/bin/rm -f $(OBJ)
	make clean -C $(LIBFT)
	make clean -C $(MLX)

fclean : clean
	make fclean -C $(LIBFT)
	make clean -C $(MLX)
	/bin/rm -f $(NAME)

re : fclean all
