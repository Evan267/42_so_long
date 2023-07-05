/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:54:22 by eberger           #+#    #+#             */
/*   Updated: 2023/07/05 09:51:23 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	open_door(t_vars *vars, mlx_image_t *items_lock)
{
	int	x;
	int	y;

	if (vars->assets->img_items_unlock->count == items_lock->count
		&& vars->assets->img_close_door->instances->enabled == 1)
	{
		vars->assets->img_close_door->instances->enabled = 0;
		x = vars->assets->img_close_door->instances->x;
		y = vars->assets->img_close_door->instances->y;
		mlx_image_to_window(vars->mlx, vars->assets->img_open_door, x, y);
		mlx_set_instance_depth(vars->assets->img_open_door->instances, 2);
	}
}

static void	get_item(t_vars *vars, int x, int y)
{
	int			i;
	mlx_image_t	*lock;
	mlx_image_t	*unlock;
	int			inst_img;

	i = 0;
	lock = vars->assets->img_items_lock;
	unlock = vars->assets->img_items_unlock;
	while (i < (int)lock->count)
	{
		if (lock->instances[i].x == x * BOX
			&& lock->instances[i].y == y * BOX
			&& lock->instances[i].enabled == 1)
		{
			lock->instances[i].enabled = 0;
			inst_img = mlx_image_to_window(vars->mlx, unlock, BOX * x, BOX * y);
			mlx_set_instance_depth(&(unlock->instances[inst_img]), 2);
		}
		i++;
	}
	open_door(vars, lock);
}

static int	test_next(t_vars *vars, int x, int y)
{
	t_list	*list;
	void	*content;
	int		i;
	char	*str_counter;

	i = 0;
	list = vars->map->list;
	while (i++ < y)
		list = list->next;
	content = list->content;
	i = 0;
	while (i++ < x)
		content++;
	if (*(char *)content == '1')
		return (1);
	else if (*(char *)content == 'C')
		get_item(vars, x, y);
	vars->counter++;
	str_counter = ft_itoa(vars->counter);
	ft_putendl_fd(str_counter, 1);
	return (put_counter(vars, str_counter), 0);
}

static void	lower_upper(mlx_key_data_t *keydata, t_vars *vars)
{
	if (keydata->key == 264 || keydata->key == 83)
	{
		if (!test_next(vars, vars->pers->x, vars->pers->y + 1))
			vars->pers->y++;
		move_pers(vars, 0);
	}
	else if (keydata->key == 265 || keydata->key == 87)
	{
		if (!test_next(vars, vars->pers->x, vars->pers->y - 1))
			vars->pers->y--;
		move_pers(vars, 1);
	}
}

void	hook(mlx_key_data_t keydata, void *param)
{
	t_vars	*vars;

	vars = param;
	if (keydata.action == 1 && vars->end == 0)
	{
		lower_upper(&keydata, vars);
		if (keydata.key == 263 || keydata.key == 65)
		{
			if (!test_next(vars, vars->pers->x - 1, vars->pers->y))
				vars->pers->x--;
			move_pers(vars, 2);
		}
		else if (keydata.key == 262 || keydata.key == 68)
		{
			if (!test_next(vars, vars->pers->x + 1, vars->pers->y))
				vars->pers->x++;
			move_pers(vars, 3);
		}
		if (find_case(vars->map->list, vars->pers->x, vars->pers->y) == 'E'
			&& vars->assets->img_open_door->count)
			end(vars);
	}
	if (keydata.key == 256)
		mlx_close_window(vars->mlx);
}
