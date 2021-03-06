# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anastasia <anastasia@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/23 19:16:42 by anastasia         #+#    #+#              #
#    Updated: 2021/05/16 19:00:47 by anastasia        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	wolf3d

SRC				=	main.c \
					parser.c \
					utils.c \
					utils_list.c \
					parse_flag.c \
					valid_map.c \
					flood_fill.c \
					raycast.c \
					mlx_init.c \
					texture_wall.c \
					texture_cell_floor.c \
					cast_sprite.c \
					sort_sprite.c \
					key_press.c \
					parse_map.c \
					perp_wall.c \

SRCS			=	$(addprefix $(SRCS_DIR), $(SRC))
OBJS			=	$(addprefix $(OBJS_DIR), $(OBJ))

SRCS_DIR		=	./src/
OBJS_DIR		=	./objs/
LIBFT_DIR		=	./libft/
MLX_DIR			=	./mlx

I_INC			=	-I ./includes/ -I ./libft/includes/

RM 				=	rm -rf

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror

LIBFT			=	@make -sC $(LIBFT_DIR)

MLX				=	@make -sC $(MLX_DIR)

all:				$(NAME)

OBJ				=	$(SRC:.c=.o)

$(OBJS_DIR)%.o:		$(SRCS_DIR)%.c ./includes/wolf3d.h
					mkdir -p $(OBJS_DIR)
					$(CC) $(CFLAGS) -c $< -o $@ $(I_INC) -Imlx

$(NAME):			$(OBJS) ./includes/wolf3d.h
					$(LIBFT)
					$(MLX)
					$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L mlx -lmlx -framework OpenGL -framework AppKit -L $(LIBFT_DIR) -lft $(I_INC)

clean:
					$(RM) $(OBJS_DIR)
					@make clean -C $(LIBFT_DIR)
					@make clean -C $(MLX_DIR)

fclean:				clean
					$(RM) $(NAME)
					@make fclean -C $(LIBFT_DIR)

re:					fclean all

.PHONY:				all clean fclean re