# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/11 17:53:17 by agiraud           #+#    #+#              #
#    Updated: 2023/10/24 18:31:07 by agiraud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	Cub3D

LIBFT	=	libft/libft.a

MLX		=	minilibx-linux/libmlx.a

SRCS	=	src/cub3d.c \
			src/init.c \
			src/parsing.c \
			src/parsing_utils.c \
			src/parsing_id.c \
			src/read_map.c \
			src/exit.c \
			src/mlx_utils.c \
			src/raycasting.c \
			src/raycasting_utils.c \
			src/render_ray.c \
			src/key.c \
			src/move.c

HEADERS	=	inc/cub3d.h

OBJS	=	${SRCS:.c=.o}

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -I./libft -I./include -I./minilibx-linux

RM		=	rm -f

all:		${NAME}

${NAME}:	${OBJS} ${LIBFT} ${MLX}
			${CC} ${OBJS} ${LIBFT} ${MLX} -lXext -lX11 -lm -o ${NAME}

${LIBFT}:
			make -C libft

${MLX}:
			make -C minilibx-linux

%.o:		%.c	${HEADERS}
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
			${RM} ${OBJS} ${OBJS_B}
			make -C libft clean

fclean:		clean
			${RM} ${NAME} ${NAME_B} ${LIBFT}

re:			fclean all

.PHONY:		all clean fclean re
