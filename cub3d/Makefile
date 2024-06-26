#TARGET
	NAME = cub3d

	OS = $(shell uname)
	ifeq ($(OS), Linux)
		MLX = mlx_linux
		MLX_LDFLAGS = -L/usr/include -lXext -lX11 -lm -lz
		LIB_MLX = mlx_Linux
	else
		MLX = mlx
		MLX_LDFLAGS = -framework OpenGL -framework AppKit
		LIB_MLX = mlx
	endif

#DIRECTORIES
	SRC_DIR = ./src/
	OBJ_DIR = ./obj/
	INC_DIR = ./inc/
	LIB_DIR = ./inc/libft/
	MLX_DIR	= $(INC_DIR)$(MLX)

#FILES
	SRC	=	cub3d.c \
			init_game.c \
			init_map.c \
			init_textures.c \
			init_health_frame.c \
			init_minimap_frame.c \
			cub3d_utils.c \
			parse_map.c \
			parse_tile.c \
			parse_textures.c \
			parse_color.c \
			parse_grid.c \
			parse_enemy.c \
			copy_grid.c \
			check_map_fill.c \
			game_start.c \
			draw_walls.c \
			draw_basic.c \
			draw_sprites.c \
			draw_weapon.c \
			draw_minimap.c \
			draw_hp.c \
			draw_dead_screen.c \
			door_update.c \
			enemy_draw_setting.c \
			enemy_actions.c \
			set_sprite_order.c \
			get_perp_wall_dist.c \
			get_start.c \
			malloc_start.c \
			hooks.c \
			key_hooks.c \
			mouse_hooks.c \
			player_move.c \

	OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)
	HEADER = $(INC_DIR)cub3d.h
	HEADER_LIB = $(LIB_DIR)/libft.h
	HEADER_MLX = $(INC_DIR)$(MLX)/mlx.h

	HEADERS = $(HEADER) $(HEADER_LIB) $(HEADER_MLX)

#FLAGS
	CFLAGS = -I$(INC_DIR) -I$(MLX_DIR) -I$(LIB_DIR) #-Wall -Wextra -Werror
	LDFLAGS = -L$(MLX_DIR) -l$(LIB_MLX) -L$(LIB_DIR) -lft $(MLX_LDFLAGS)

#COMMANDS
	CC = gcc
	RM = rm -rf

	VPATH = ./src/main/ ./src/parser/ ./src/initializer ./src/game/ ./src/hooks ./src/draw

.PHONY	: all clean fclean re libmlx

all	:	libft libmlx $(NAME)

libft	:
		$(MAKE) -C $(LIB_DIR)

libmlx	:
		$(MAKE) -C $(MLX_DIR)

$(NAME)	:	$(OBJ)
		$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)%.o:%.c $(HEADERS)
		mkdir -p $(OBJ_DIR)
		$(CC) $(CFLAGS) -c $< -o $@
clean	:
		$(RM) $(OBJ_DIR)
		$(MAKE) -C $(LIB_DIR) clean
		$(MAKE) -C $(MLX_DIR) clean

fclean	:	clean
		$(RM) $(NAME)
		$(MAKE) -C $(LIB_DIR) fclean

re		:	fclean	all
