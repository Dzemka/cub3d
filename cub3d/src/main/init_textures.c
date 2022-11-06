#include <cub3d.h>

static void set_color(char *addr, int *color)
{
    *color = addr[0];
    *color += addr[1] * 256;
    *color += addr[2] * 256 * 256;
    *color += 256 * 256 * 256;
}

static int fill_texture(int tex_id, t_game *game)
{
    int x;
    int y;
    t_data_img *img;

    img = game->tex_img[tex_id];
    y = -1;
    game->texture[tex_id] = malloc(sizeof(char *) * (img->height + 1));
    game->texture[tex_id][img->height] = NULL;
    while (++y < img->height)
    {
        game->texture[tex_id][y] = malloc(sizeof(char *) * (img->width + 1));
        game->texture[tex_id][y][img->width] = '\0';
        x = -1;
        while (++x < img->width)
            set_color(&img->addr[y * img->line_length + x * 4], &game->texture[tex_id][y][x]);
    }
    return (0);
}

static void get_textures(t_game *game)
{
    int y;
    int tex_id;
    char *path;

    tex_id = -1;

    while (++tex_id < TEX_COUNT)
    {
        game->tex_img[tex_id]->img = mlx_xpm_file_to_image(game->mlx, game->map->path_textures[tex_id], &game->tex_img[tex_id]->width,
                                                           &game->tex_img[tex_id]->height);
        if (!game->tex_img[tex_id]->img)
        {
            printf("%d %s : ", tex_id, game->map->path_textures[tex_id]);
            game_exit("Image error");
        }
        game->tex_img[tex_id]->addr = mlx_get_data_addr(game->tex_img[tex_id]->img, &game->tex_img[tex_id]->bpp, &game->tex_img[tex_id]->line_length,
                                                        &game->tex_img[tex_id]->endian);
        if (!game->tex_img[tex_id]->addr)
        {
            printf("%d %s : ", tex_id, game->map->path_textures[tex_id]);
            game_exit("Image address error");
        }
        fill_texture(tex_id, game);
    }
}

static int malloc_textures(t_game *game)
{
    int tex_id;

    game->tex_img = malloc(sizeof(t_data_img *) * (TEX_COUNT + 1));
    if (!game->tex_img)
        game_exit("Malloc error\n");
    game->texture = malloc(sizeof(int *) * (TEX_COUNT + 1));
    if (!game->texture)
        game_exit("Malloc error\n");
    tex_id = -1;
    while (++tex_id < TEX_COUNT)
    {
        game->tex_img[tex_id] = malloc(sizeof(t_data_img));
        if (!game->tex_img[tex_id])
            game_exit("Malloc error\n");
    }
    game->tex_img[tex_id] = NULL;
}

void init_textures(t_game *game)
{
    malloc_textures(game);
    get_textures(game);
}
