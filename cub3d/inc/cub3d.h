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

#define WIDTH 640
#define HEIGHT 480
#define TEX_WIDTH 64
#define TEX_HEIGHT 64

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
	t_coord	pos;
	int	tex_id;
} t_sprite;

typedef struct s_map
{
	t_list	*map_base;
	char	**path_textures;
	char	**map_grid;
	int		floor_color;
	int		ceiling_color;
	size_t	width;
	size_t	height;
	t_coord	player_p;
	char	player_orientation;
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
	int				tex_count;
	t_sprite		**sprite;
	int				*zBuffer;
	int				***sprite_tex;
	t_data_img		**sprite_img;
	//test
	t_tid			**tid;
	double			pitch;
	double			posZ;
	//test
} t_game;


void	game_start(t_game *game);
t_game	*game_init(int argc, char **argv);
int		cleaning_map(t_map **map);
void	*game_clean(t_game **game);
void	draw_basic(t_game *game);
void	draw_walls(t_game *game);
void	draw_floor(t_game *game);
void	draw_sprites(t_game *game);
int		get_sprites(t_game *game);
void	get_verline(int x, t_game *game, int *drawStart, int *drawEnd);
void	ft_pixel_put(t_data_img *data, int x, int y, int color);
void	hooks(t_game *game);

//parser
int		parse_map(t_map *map, int fd);
int		parse_textures(char *s, int i, t_map *map);
int		parse_color(char *s, int i, t_map *map);
int		parse_grid(char *s, int i, t_map *map);
int		copy_grid(t_list *ptr, t_map *map);

//utils
int		get_buffer(t_game *game);
int		get_textures(t_game *game);
int		parse_error_message(char *str, int id);
int		cleaning_map(t_map **map);
void	init_values(t_map *map);
void	fill_coord(double y, double x, t_coord *pos);


#endif
