#include <cub3d.h>

void    draw_minimap(t_game *game)
{
    int x;
    int y;
    int r;
    int radius;
    int c;
    char    *s;

    c = sqrt(WIDTH * WIDTH + HEIGHT * HEIGHT);
    y = -1;
    radius =  c / 20;
    while (++y < HEIGHT)
    {
        x = -1;
        while (++x < WIDTH)
        {
            r = (x - WIDTH / 10) * (x - WIDTH / 10) + (y - HEIGHT / 8) * (y - HEIGHT / 8);
            if (r < radius * radius + c / 10  && r > radius * radius - c / 10)
               ft_pixel_put(&game->img, x, y, 0xFF0000);
            if ((x == WIDTH / 10|| y == HEIGHT / 8) && r > radius * radius && r < (radius + 10) * (radius + 10))
                ft_pixel_put(&game->img, x, y, 0x00FF00);
        }
    }
    s = ft_itoa((int)game->player.pos.x);
    mlx_string_put(game->mlx, game->window, 960, 540, 0xF0F0F0, s);
    mlx_string_put(game->mlx, game->window, WIDTH / 10, HEIGHT / 8 - radius - 10, 0x0000FF, "N");
    mlx_string_put(game->mlx, game->window, WIDTH / 10, HEIGHT / 8 + radius + 20, 0x0000FF, "S");
    mlx_string_put(game->mlx, game->window, WIDTH / 10  - radius - 15, HEIGHT / 8 + 5, 0x0000FF, "W");
    mlx_string_put(game->mlx, game->window, WIDTH / 10  + radius + 15, HEIGHT / 8 + 5, 0x0000FF, "E");
}