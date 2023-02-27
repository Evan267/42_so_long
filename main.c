#include "so_long.h"
#include <stdio.h>
#include <stdlib.h>

void	move_pers(t_vars *vars, int orientation)
{
	if (vars->pers->orientation == 0)
	{
		vars->assets->img_pers_bottom->instances->enabled = 0;
		vars->assets->img_pers_bottom->count = 0;
	}
	else if (vars->pers->orientation == 1)
	{
		vars->assets->img_pers_top->instances->enabled = 0;
		vars->assets->img_pers_top->count = 0;
	}
	else if (vars->pers->orientation == 2)
	{
		vars->assets->img_pers_left->instances->enabled = 0;
		vars->assets->img_pers_left->count = 0;
	}
	else if (vars->pers->orientation == 3)
	{
		vars->assets->img_pers_right->instances->enabled = 0;
		vars->assets->img_pers_right->count = 0;
	}
	vars->pers->orientation = orientation;
	print_pers(vars);
}

void	open_door(t_vars *vars, mlx_image_t *items_lock)
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
	}
}

void	get_item(t_vars *vars, int x, int y)
{
	int			i;
	mlx_image_t	*items_lock;

	i = 0;
	items_lock = vars->assets->img_items_lock;
	while (i < items_lock->count)
	{
		if (items_lock->instances[i].x == x * 32
				&& items_lock->instances[i].y == y * 32
				&& items_lock->instances[i].enabled == 1)
		{
			items_lock->instances[i].enabled = 0;
			mlx_image_to_window(vars->mlx, vars->assets->img_items_unlock, 32 * x, 32 * y);
		}
		i++;
	}
	open_door(vars, items_lock);
}

int	test_next(t_vars *vars, int x, int y)
{
	t_list	*list;
	void	*content;
	int		i;

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
	return (vars->counter++, 0);
}

void	hook(mlx_key_data_t keydata, void* param)
{
	t_vars	*vars;

	vars = param;
	if (keydata.action == 1)
	{
		printf("%i\n", keydata.key);
	   	if (keydata.key == 264)
		{
			if (!test_next(vars, vars->pers->x, vars->pers->y + 1))
				vars->pers->y++;
			move_pers(vars, 0);
		}
		else if (keydata.key == 265)
		{
			if (!test_next(vars, vars->pers->x, vars->pers->y - 1))
				vars->pers->y--;
			move_pers(vars, 1);
		}
		else if (keydata.key == 263)
		{
			if (!test_next(vars, vars->pers->x - 1, vars->pers->y))
				vars->pers->x--;
			move_pers(vars, 2);
		}
		else if (keydata.key == 262)
		{
			if (!test_next(vars, vars->pers->x + 1, vars->pers->y))
				vars->pers->x++;
			move_pers(vars, 3);
		}
	}
}

void	init_var(t_vars **vars)
{
	*vars = malloc(sizeof(t_vars));
	(*vars)->map = malloc(sizeof(t_maps));
	(*vars)->pers= malloc(sizeof(t_pers));
	(*vars)->counter = 0;
	(*vars)->pers->y = -1;
	(*vars)->pers->x = -1;
	(*vars)->pers->orientation = 0;
	(*vars)->pers->items_get = 0;
}

int32_t	main(void)
{
	t_vars	*vars;

	vars = NULL;
	init_var(&vars);
	if (!create_map(vars->map))
		return(EXIT_FAILURE);
	if (!(vars->mlx = mlx_init(vars->map->width, vars->map->height, "so_long", false)))
		return(EXIT_FAILURE);
	if (!algo_test("./map.ber"))
		return(EXIT_FAILURE);
	show_map(vars);
	mlx_key_hook(vars->mlx, hook, vars);
	mlx_loop(vars->mlx);

	mlx_terminate(vars->mlx);
	return (EXIT_SUCCESS);
}
