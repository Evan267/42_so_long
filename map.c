#include "so_long.h"

int	create_map(t_maps *map)
{
	t_list	*lst;
	char	*next_line;

	map->size_box = 32;	
	map->fd = open("./map.ber", O_RDONLY);
	if (map->fd < 0)
		return (0);
	next_line = get_next_line(map->fd);
	lst = ft_lstnew(next_line);
	map->line = 0;
	map->column = ft_strlen(next_line) - 1;
	while (next_line)
	{
		next_line[ft_strlen(next_line) - 1] = 0;
		if (map->column != (int)ft_strlen(next_line))
			return (0);//free la liste si erreur
		next_line = get_next_line(map->fd);
		ft_lstadd_back(&lst, ft_lstnew(next_line));
		(map->line)++;
	}
	map->list = lst;
	map->width = map->size_box * map->column;
	map->height = map->size_box * map->line;
	close(map->fd);
	return (1);
}

int	print_pers(t_vars *vars)
{
	int	x;
	int	y;

	x = vars->pers->x;
	y = vars->pers->y;
	if (vars->pers->orientation == 0)
		mlx_image_to_window(vars->mlx, vars->assets->img_pers_bottom, 32 * x + 7, 32 * y + 8);
	else if (vars->pers->orientation == 1)
		mlx_image_to_window(vars->mlx, vars->assets->img_pers_top, 32 * x + 7, 32 * y + 8);
	else if (vars->pers->orientation == 2)
		mlx_image_to_window(vars->mlx, vars->assets->img_pers_left, 32 * x + 7, 32 * y + 8);
	else if (vars->pers->orientation == 3)
		mlx_image_to_window(vars->mlx, vars->assets->img_pers_right, 32 * x + 7, 32 * y + 8);
	return (1);
}

int	print_case(char c, int *loc, t_vars *vars)
{
	if (c == '1')
		mlx_image_to_window(vars->mlx, vars->assets->img_lava, 32 * loc[1], 32 * loc[0]);
	else
		mlx_image_to_window(vars->mlx, vars->assets->img_sol, 32 * loc[1], 32 * loc[0]);
	if (c == 'C')
		mlx_image_to_window(vars->mlx, vars->assets->img_items_lock, 32 * loc[1], 32 * loc[0]);
	if (c == 'E')
		mlx_image_to_window(vars->mlx, vars->assets->img_close_door, 32 * loc[1], 32 * loc[0]);
	if (c == 'P' && vars->pers->x == -1 && vars->pers->y == -1)
	{
		vars->pers->x = loc[1];
		vars->pers->y = loc[0];
	}
	return (0);
}	

int	show_map(t_vars *vars)
{
	t_list	*list;
	char	*str;
	int		loc[2];

	list = vars->map->list;
	vars->assets = init_imgs(vars->mlx);
	loc[0] = 0;
	while (loc[0] < vars->map->line)
	{
		loc[1] = 0;
		str = list->content;
		while (loc[1] < vars->map->column)
		{
			print_case(str[loc[1]], loc, vars);
			(loc[1])++;
		}
		list = list->next;
		(loc[0])++;
	}
	print_pers(vars);
	return (1);
}
