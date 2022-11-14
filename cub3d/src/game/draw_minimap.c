#include <cub3d.h>

void draw_minimap(t_game *game)
{
    int x;
    int y;
    int r;
    int radius;
    int c;
    char *s;
    char *temp;
    int center_x;
    int center_y;

    c = sqrt(WIDTH * WIDTH + HEIGHT * HEIGHT);
    center_x = WIDTH / 10;
    center_y = HEIGHT / 6;
    y = -1;
    radius = c / 15;
    while (++y < HEIGHT)
    {
        x = -1;
        while (++x < WIDTH)
        {
            r = (x - center_x) * (x - center_x) + (y - center_y) * (y - center_y);
            if (r < radius * radius + c / 10 && r > radius * radius - c / 10)
                ft_pixel_put(&game->img, x, y, 0xFF0000);
            if ((x == center_x || y == center_y) && r > radius * radius && r < (radius + 10) * (radius + 10))
                ft_pixel_put(&game->img, x, y, 0x00FF00);
        }
    }
    ft_pixel_put(&game->img, center_x, center_y, 0xFF0000);
    s = ft_itoa((int)game->player.pos.x);
    temp = ft_strjoin("x : ", s);
    mlx_put_image_to_window(game->mlx, game->window, game->img.img, 0, 0);
    free(s);
    mlx_string_put(game->mlx, game->window, center_x - 50, center_y + radius + 30, 0xF0F0F0, temp);
    free(temp);
    s = ft_itoa((int)game->player.pos.y);
    temp = ft_strjoin("y : ", s);
    free(s);
    mlx_string_put(game->mlx, game->window, center_x + 30,center_y + radius + 30, 0xF0F0F0, temp);
    free(temp);
    mlx_string_put(game->mlx, game->window, center_x, center_y - radius - 20, 0x0000FF, "N");
    mlx_string_put(game->mlx, game->window, center_x, center_y + radius + 20, 0x0000FF, "S");
    mlx_string_put(game->mlx, game->window, center_x - radius - 15, center_y + 5, 0x0000FF, "W");
    mlx_string_put(game->mlx, game->window, center_x + radius + 15, center_y + 5, 0x0000FF, "E");
}
