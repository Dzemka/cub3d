/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 08:02:16 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 08:20:44 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include "keycodes.h"

# define WIDTH 1920
# define HEIGHT 1080
# define TEX_COUNT 14
# define SPRITE_COUNT 9
# define ENEMY_COUNT 4
# define NO_TEXTURE 0
# define SO_TEXTURE 1
# define WE_TEXTURE 2
# define EA_TEXTURE 3
# define S0 4
# define S1 5
# define S2 6
# define S3 7
# define S4 8
# define S5 9
# define S6 10
# define S7 11
# define DOOR_TEXTURE 12
# define WEAPON_TEXTURE 13
# define FLOOR_COLOR 14
# define CEILLING_COLOR 15
# define FOV 0.66
# define PLAYER_MOVE_SPEED 0.15
# define ENEMY_MOVE_SPEED 30
# define ENEMY_WALK_SPEED 30
# define ENEMY_ATTACK_SPEED 30
# define ENEMY_SPAWN_SPEED 80
# define ENEMY_DEATH_SPEED 50
# define ENEMY_DAMAGE 15
# define PLAYER_DAMAGE 30
# define RANGE_MINIMAP 30
# define SPEED_DOOR_CLOSING 15

typedef struct s_data_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_data_img;

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
	int		health;
	size_t	frame;
	int		weapon_action;
	int		attack;
	int		action;
}	t_player;

typedef struct s_ray
{
	t_coord	map;
	t_coord	dir;
	t_coord	delta_dist;
	t_coord	side_dist;
	t_coord	step;
	int		side;
}	t_ray;

typedef struct s_wall_verline
{
	t_ray	ray;
	int		x;
	double	perpwalldist;
	int		lineheight;
	int		texnum;
	int		tex_x;
	double	tex_y;
	int		drawstart;
	int		drawend;
	double	step;
}	t_wall_verline;

typedef struct s_sprite_draw
{
	int			sprite_height;
	int			sprite_width;
	int			drawstart_x;
	int			drawend_x;
	int			drawstart_y;
	int			drawend_y;
	double		start_tex_y;
	double		start_tex_x;
	double		step_y;
	double		step_x;
	int			tex_id;
	double		draw_distance;
	double		tex_x;
	double		tex_y;
}	t_sprite_draw;

typedef struct s_sprite
{
	t_coord	coord;
	int		id;
	int		main_id;
	int		order;
	double	distance;
	size_t	frame;
}	t_sprite;

typedef struct s_enemy
{
	int			sprite_index;
	int			count_actions;
	int			count_spawn;
	int			count_walk;
	int			count_attack;
	int			count_dead;
	size_t		frame;
	int			action;
	int			health;
}	t_enemy;

typedef struct s_door_map
{
	size_t	frame;
	int		open;
	int		is_vertical;
}	t_door_map;

typedef struct s_map
{
	void		*game;
	t_list		*linelist;
	t_list		*grid_ptr;
	char		**path_textures;
	int			floor_color;
	int			ceiling_color;
	char		**map_grid;
	size_t		width;
	size_t		height;
	t_coord		player_p;
	char		player_orientation;
	int			sprite_count;
	int			enemy_count;
	int			door_count;
	t_sprite	**sprite_base;
	t_enemy		**enemy_base;
	t_door_map	**door_map;
}	t_map;

typedef struct s_game
{
	struct s_map	*map;
	t_player		player;
	void			*mlx;
	void			*window;
	t_data_img		img;
	int				**buffer;
	int				***texture;
	t_data_img		**tex_img;
	t_sprite		**sprite;
	t_enemy			**enemy;
	double			*zbuffer;
	int				**health_frame_buffer;
	int				**minimap_frame_buffer;
	int				(*funct)(struct s_game *game);
	t_coord			coord_start_hp;
	int				minimap_size;
	double			pitch;
}	t_game;

//main
int		game_start(t_game *game);

//utils
void	game_exit(char *error_message);
int		parse_exit(char *str, int id);
void	fill_coord(double y, double x, t_coord *pos);

//initializer
void	get_start(t_game *game);
void	malloc_start(t_game *game);
t_game	*init_game(int argc, char **argv);
void	init_map(t_game *game, char **argv);
void	init_weapon(t_game *game);
void	init_health_frame(t_game *game);
void	init_minimap_frame(t_game *game);
void	init_textures(t_game *game);

//draw
int		draw_game(t_game *game);
void	draw_basic(t_game *game);
int		draw_dead_screen(t_game *game);
void	draw_walls(t_game *game);
void	get_perp_wall_dist(t_wall_verline *verline, t_game *game);
void	draw_basic(t_game *game);
void	draw_sprites(t_game *game);
void	set_sprite_order(t_game *game);
void	enemy_draw_setting(int i, t_sprite_draw *draw_data, t_game *game);
void	spawn_action(int id, t_game *game);
void	move_action(t_game *game, int id, int i);
void	attack_action(t_game *game, int id);
void	death_action(t_game *game, int id);
void	draw_weapon(t_game *game);
void	draw_minimap(t_game *game);
void	draw_hp(t_game *game);
void	door_update(t_game *game);
void	ft_pixel_put(t_data_img *data, int x, int y, int color);

//parser
void	parse_map(t_game *game, int fd);
int		parse_textures(char *s, int pos, t_map *map);
int		parse_color(char *s, int i, t_map *map);
int		parse_enemy(char *s, int i, t_map *map);
int		parse_weapon(char *s, int i, t_map *map);
void	parse_grid(t_game *game);
void	rgb_to_num(char **rgb, int *set_color);
void	copy_grid(t_map *map);
void	parse_tile(int x, int y, t_map *map, int *sprite_index);
void	check_map_fill(t_game *game);

//hooks
void	hooks(t_game *game);
int		key_hooks(int keycode, t_game *game);
void	player_move(int keycode, t_game *game);
int		mouse_move(int x, int y, t_game *game);
int		mouse_press(int button, int x, int y, t_game *game);

#endif
