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

#define FOV 0.66

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
	t_coord	*dir;
	t_coord	*plane;
	t_coord	*pos;
}	t_player;

typedef struct s_ray
{
	t_coord	map;
	t_coord	dir;
	t_coord	deltaDist;
	t_coord	sideDist;
	t_coord	step;
	int		side;
}	t_ray;

typedef struct s_wall_verline
{
	t_ray	ray;
	int		x;
	double	perpWallDist;
	int		lineHeight;
	int		texNum;
	int		texX;
	double	texY;
	int		drawStart;
	int		drawEnd;
	double	step;
} t_wall_verline;

typedef struct s_sprite_draw
{
	int			sprite_height;
	int			sprite_width;
	int			drawStartX;
	int			drawEndX;
	int			drawStartY;
	int			drawEndY;
	double		start_tex_y;
	double		start_tex_x;
	double		step_y;
	double		step_x;
	int			tex_id;
	double		draw_distance;

} t_sprite_draw;


typedef struct s_sprite
{
	t_coord	*coord;
	int		id;
	int		order;
	double	distance;
	size_t	frame;
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
	t_coord	*player_p;
	char	player_orientation;
	int		sprite_count;
}	t_map;

typedef struct s_game
{
	struct s_map	*map;
	t_player		*player;
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
	double			pitch;
	double			posZ;
	//test
} t_game;


int		game_start(t_game *game);
t_game	*init_game(int argc, char **argv);
void	init_map(t_game *game, int argc, char **argv);
int		cleaning_map(t_map **map);
void	game_clean(t_game **game);
void	get_perp_wall_dist(t_wall_verline *verline, t_game *game);


void	draw_basic(t_game *game);
void	draw_walls(t_game *game);
void	draw_basic(t_game *game);
void	draw_sprites(t_game *game);
void	set_sprite_order(t_game *game);
void	ft_pixel_put(t_data_img *data, int x, int y, int color);
void	hooks(t_game *game);


int		parse_tile(int x, int y, t_map *map, int *sprite_index);

//parser
void	parse_map(t_game *game, int fd);
int		parse_textures(char *s, int pos, t_map *map);
int		parse_color(char *s, int i, t_map *map);
void	parse_grid(t_game *game);
void	rgb_to_num(char **rgb, int *set_color);


//utils
void	game_exit(char *error_message);
void	init_textures(t_game *game);
int		parse_exit(char *str, int id);
int		cleaning_map(t_map **map);
void	fill_coord(double y, double x, t_coord *pos);

#endif
