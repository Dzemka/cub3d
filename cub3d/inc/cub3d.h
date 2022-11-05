#ifndef CUB3D_H
#define CUB3D_H

#include <libft.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include "keycodes.h"
#include <parser.h>

#define WIDTH 1920
#define HEIGHT 1080
#define TEX_WIDTH 64
#define TEX_HEIGHT 64
#define TEX_COUNT 12
#define SPRITE_COUNT 9

typedef struct s_data_img
{
	void *img;
	char *addr;
	int bpp;
	int line_length;
	int endian;
	int	width;
	int	height;
} t_data_img;

typedef struct s_coord
{
	double	y;
	double	x;
}	t_coord;

typedef struct s_player
{
	t_coord	dir;
	t_coord	plane;
	t_coord	pos;
}	t_player;

typedef struct s_ray
{
	t_coord	map;
	t_coord	dir;
	t_coord	deltaDist;
	t_coord	sideDist;
	t_coord	step;
	int		side;
	size_t	test;
}	t_ray;

typedef struct s_sprite
{
	t_coord	coord;
	int		id;
	int		order;
	double	distance;
} t_sprite;

typedef struct s_map
{
	void	*game;
	t_list	*lineList;
	t_list	*grid_ptr;
	char	**path_textures;
	char	**path_sprites;
	int		floor_color;
	int		ceiling_color;
	char	**map_grid;
	size_t	width;
	size_t	height;
	t_coord	player_p;
	char	player_orientation;
	int		sprite_count;
}	t_map;

typedef struct s_tid
{
	void	*game;
	int		num;
	int		y;
} t_tid;

typedef struct s_game
{
	struct s_map	*map;
	t_player		player;
	void			*mlx;
	void			*window;
	t_data_img		img;
	int				wall_color;
	int				**buffer;
	int				***texture;
	t_data_img		**tex_img;
	t_sprite		**sprite;
	double			*zBuffer;
	int				***sprite_tex;
	t_data_img		**sprite_img;
	//test
	t_tid			**tid;
	double			pitch;
	double			posZ;
	//test
} t_game;


int		game_start(t_game *game);
t_game	*init_game(int argc, char **argv);
void	init_map(t_game *game, int argc, char **argv);
int		cleaning_map(t_map **map);
void	game_clean(t_game **game);
void	draw_basic(t_game *game);
void	draw_walls(t_game *game);
void	draw_floor(t_game *game);
void	draw_sprites(t_game *game);
// int		init_sprites(t_game *game);
void	get_verline(int x, t_game *game, int *drawStart, int *drawEnd);
void	ft_pixel_put(t_data_img *data, int x, int y, int color);
void	hooks(t_game *game);


int		parse_tile(int x, int y, t_map *map, int *sprite_index);


// int		init_map(t_map **map, int argc, char **argv);
// void	player_init(t_game *game);
// int		init_graphic(t_game *game);


//parser
int		parse_map(t_game *game, int fd);
int		parse_textures(char *s, int i, t_map *map);
int		parse_color(char *s, int i, t_map *map);
int		parse_grid(t_map *map);

//utils
void	game_exit(char *error_message);
void	init_textures(t_game *game);
int		parse_error_message(char *str, int id);
int		cleaning_map(t_map **map);
void	fill_coord(double y, double x, t_coord *pos);


#endif
