/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perso.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:18:42 by eberger           #+#    #+#             */
/*   Updated: 2023/03/31 16:06:53 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	print_or_change(t_vars *vars, mlx_image_t *img, int *loc)
{
	if (img->count)
	{
		img->instances->x = loc[1];
		img->instances->y = loc[0];
		img->instances->enabled = 1;
	}
	else
		print(vars, img, loc, 5);
}

int	print_pers(t_vars *vars)
{
	int	loc[2];

	loc[1] = (BOX * vars->pers->x) + (BOX / 8);
	loc[0] = BOX * vars->pers->y;
	if (vars->pers->orientation == 0)
		print_or_change(vars, vars->assets->img_pers_bottom, loc);
	else if (vars->pers->orientation == 1)
		print_or_change(vars, vars->assets->img_pers_top, loc);
	else if (vars->pers->orientation == 2)
		print_or_change(vars, vars->assets->img_pers_left, loc);
	else if (vars->pers->orientation == 3)
		print_or_change(vars, vars->assets->img_pers_right, loc);
	return (1);
}

void	move_pers(t_vars *vars, int orientation)
{
	if (vars->pers->orientation == 0)
		vars->assets->img_pers_bottom->instances->enabled = 0;
	else if (vars->pers->orientation == 1)
		vars->assets->img_pers_top->instances->enabled = 0;
	else if (vars->pers->orientation == 2)
		vars->assets->img_pers_left->instances->enabled = 0;
	else if (vars->pers->orientation == 3)
		vars->assets->img_pers_right->instances->enabled = 0;
	vars->pers->orientation = orientation;
	print_pers(vars);
}

void	print(t_vars *vars, mlx_image_t *img, int *loc, int z)
{
	int	inst_img;

	inst_img = mlx_image_to_window(vars->mlx, img, loc[1], loc[0]);
	mlx_set_instance_depth(&(img->instances[inst_img]), z);
}
