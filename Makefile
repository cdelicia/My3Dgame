# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdelicia <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/28 13:12:26 by cdelicia          #+#    #+#              #
#    Updated: 2019/10/05 16:38:18 by cdelicia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
LIBFT = ./libft/libft.a
CUB = srcs/main.c srcs/map.c srcs/ray.c srcs/move.c srcs/free.c srcs/draw.c \
 	srcs/check.c srcs/legend_check.c srcs/map_check.c srcs/image.c \
	srcs/bmp.c srcs/draw2.c srcs/sprite.c srcs/draw3.c
OBJ = $(CUB:.c=.o)
GCCDBG = gcc -Wall -Werror -Wextra -g -fsanitize=address
GCC = gcc -Wall -Werror -Wextra
HDR = ./includes/cub3d.h
MLX = libmlx.dylib
LMLX = -L. -lmlx
GREEN = \033[1;32m
YELLOW = \033[0;33m
DEFAULT = \033[0m

all: $(MLX) $(NAME)

%.o: %.c
	@$(GCC) -c $< -o $@

$(MLX):
	@echo "\n$(GREEN)[0%              ]$(DEFAULT) 0/4 Installation in progress.$(DEFAULT)"
	@cd mlx_mms && make
	@mv mlx_mms/libmlx.dylib ./libmlx.dylib
	@echo "\n$(GREEN)[===25%          ]$(DEFAULT) 1/4 Step: miniLibX is ready.$(DEFAULT)"

$(NAME): $(OBJ)
	@echo "\n$(GREEN)[======50%       ]$(DEFAULT) 2/4 Step: all o-files is compile.$(DEFAULT)"
	@echo "\n$(GREEN)[=========75%    ]$(DEFAULT) 3/4 Step: libft.a is ready.$(DEFAULT)"
	@$(GCC) $(LMLX) $(LIBFT) $(OBJ) -o $(NAME)
	@echo "\n$(GREEN)[============100%]$(DEFAULT) 4/4 Step: cub3D is ready.$(DEFAULT)"
	@echo "\n$(YELLOW)Start with command:$(DEFAULT) ./cub3D test.cub (beach.cub)$(DEFAULT)"

clean:
	@rm -f $(OBJ)
	@cd mlx_mms && make clean
	@rm -f screenshot.bmp

fclean: clean
	@rm -f $(NAME)
	@rm -f libmlx.dylib

re: fclean all

bonus: all

norm:
	norminette ./*.c ./cub3d.h

save:
	./cub3D map.cub --save

.PHONY: all clean fclean re bonus save norm
