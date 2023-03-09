/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:53:57 by eberger           #+#    #+#             */
/*   Updated: 2023/03/06 09:51:08 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	init(mlx_t *mlx, char *path, mlx_image_t **img)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
		return (0);
	*img = mlx_texture_to_image(mlx, texture);
	if (!*img)
		return (0);
	mlx_delete_texture(texture);
	return (1);
}

int	init_imgs(t_vars *vars)
{
	t_assets	*assets;
	mlx_t		*mlx;

	mlx = vars->mlx;
	assets = malloc(sizeof(t_assets));
	if (!assets)
		return (0);
	vars->assets = assets;
	if (!init(mlx, "./assets/lava_32.png", &(assets->img_lava))
		|| !init(mlx, "./assets/sol_32.png", &(assets->img_sol))
		|| !init(mlx, "./assets/char_bottom.png", &(assets->img_pers_bottom))
		|| !init(mlx, "./assets/char_top.png", &(assets->img_pers_top))
		|| !init(mlx, "./assets/char_left.png", &(assets->img_pers_left))
		|| !init(mlx, "./assets/char_right.png", &(assets->img_pers_right))
		|| !init(mlx, "./assets/items_lock.png", &(assets->img_items_lock))
		|| !init(mlx, "./assets/items_unlock.png", &(assets->img_items_unlock))
		|| !init(mlx, "./assets/close_door.png", &(assets->img_close_door))
		|| !init(mlx, "./assets/open_door.png", &(assets->img_open_door)))
		return (0);
	return (1);
}
