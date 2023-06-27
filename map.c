/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:57:43 by eberger           #+#    #+#             */
/*   Updated: 2023/06/27 09:42:39 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	test_map_close(t_list *list, t_maps *map)
{
	int		i;
	t_list	*elem;
	char	*str;

	i = 0;
	elem = list;
	while (elem)
	{
		str = elem->content;
		if (!test_close(ft_lstsize(list), i, str))
			return (0);
		elem = elem->next;
		i++;
	}
	map->list = list;
	return (1);
}

char	*test_map(t_maps *map)
{
	char	*next_line;

	map->fd = open(map->path, O_RDONLY);
	if (map->fd < 0)
		return (error_map("map introuvable", NULL), NULL);
	next_line = get_next_line(map->fd);
	if (!next_line)
		return (error_map("map vide", NULL), NULL);
	map->line = 0;
	map->column = ft_strlen(next_line) - 1;
	return (next_line);
}

int	create_map(t_maps *map)
{
	t_list	*lst;
	char	*next_line;

	lst = NULL;
	next_line = test_map(map);
	if (!next_line)
		return (0);
	while (next_line)
	{
		if (next_line[ft_strlen(next_line) - 1] == '\n')
			next_line[ft_strlen(next_line) - 1] = 0;
		ft_lstadd_back(&lst, ft_lstnew(next_line));
		if (map->column != (int)ft_strlen(next_line))
			return (error_map("map : lignes de longueur differentes", &(lst)));
		next_line = get_next_line(map->fd);
		(map->line)++;
	}
	if (!test_map_close(lst, map))
		return (error_map("map: pas encadre par des obstacles", &(lst)));
	map->width = BOX * map->column;
	map->height = BOX * map->line;
	close(map->fd);
	return (1);
}

int	print_case(char c, int *loc, t_vars *vars)
{
	int	pix[2];

	pix[0] = loc[0] * BOX;
	pix[1] = loc[1] * BOX;
	if (!ft_strchr("01CEP", c))
		return (error_map("La carte ne peut contenir aue 01CEP", NULL));
	if (c == '1')
		print(vars, vars->assets->img_lava, pix, 1);
	else
		print(vars, vars->assets->img_sol, pix, 1);
	if (c == 'C')
		print(vars, vars->assets->img_items_lock, pix, 2);
	if (c == 'E')
		print(vars, vars->assets->img_close_door, pix, 2);
	if (c == 'P' && vars->pers->x == -1 && vars->pers->y == -1)
	{
		vars->pers->x = loc[1];
		vars->pers->y = loc[0];
	}
	return (1);
}	

int	show_map(t_vars *vars)
{
	t_list	*list;
	char	*str;
	int		loc[2];

	list = vars->map->list;
	if (!init_imgs(vars))
		return (0);
	loc[0] = 0;
	while (loc[0] < vars->map->line)
	{
		loc[1] = 0;
		str = list->content;
		while (loc[1] < vars->map->column)
		{
			if (!print_case(str[loc[1]], loc, vars))
				return (0);
			(loc[1])++;
		}
		list = list->next;
		(loc[0])++;
	}
	print_pers(vars);
	return (1);
}
