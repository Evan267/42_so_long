#include "so_long.h"

static mlx_image_t	*init_img(mlx_t *mlx, char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(path);
	img = mlx_texture_to_image(mlx, texture);
	return (img);
}

t_assets	*init_imgs(mlx_t *mlx)
{
	t_assets	*assets;

	assets = malloc(sizeof(t_assets));
	assets->img_lava = init_img(mlx, "./assets/lava_32.png");
	assets->img_sol = init_img(mlx, "./assets/sol_32.png");
	assets->img_pers_bottom = init_img(mlx, "./assets/char_bottom.png");
	assets->img_pers_top = init_img(mlx, "./assets/char_top.png");
	assets->img_pers_left = init_img(mlx, "./assets/char_left.png");
	assets->img_pers_right = init_img(mlx, "./assets/char_right.png");
	assets->img_items_lock = init_img(mlx, "./assets/items_lock.png");
	assets->img_items_unlock = init_img(mlx, "./assets/items_unlock.png");
	assets->img_close_door = init_img(mlx, "./assets/close_door.png");
	assets->img_open_door = init_img(mlx, "./assets/open_door.png");
	return (assets);
}
