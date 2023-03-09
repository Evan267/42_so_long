/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:54:10 by eberger           #+#    #+#             */
/*   Updated: 2023/03/06 11:35:10 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	test_close(int size_list, int i, char *str)
{
	if (i == 0 || i == size_list)
	{
		while (*str)
		{
			if (*str != '1')
				return (0);
			str++;
		}
	}
	else
	{
		if (str[0] != '1' || str[ft_strlen(str) - 1] != '1')
			return (0);
	}
	return (1);
}

char	find_case(t_list *list, int x, int y)
{
	char	*chr;

	while (y--)
		list = list->next;
	chr = list->content;
	return (chr[x]);
}

void	change_case(t_list *list, int x, int y, char c)
{
	char	*chr;

	while (y--)
		list = list->next;
	chr = list->content;
	chr[x] = c;
}

int	put_counter(t_vars *vars, char *str_counter)
{
	if (vars->assets->img_counter)
		mlx_delete_image(vars->mlx, vars->assets->img_counter);
	vars->assets->img_counter = mlx_put_string(vars->mlx, str_counter, 10, 5);
	free(str_counter);
	return (0);
}

void	init_var(t_vars **vars, char *path)
{
	*vars = malloc(sizeof(t_vars));
	(*vars)->map = malloc(sizeof(t_maps));
	(*vars)->pers = malloc(sizeof(t_pers));
	(*vars)->map->path = ft_strjoin("./", path);
	(*vars)->end = 0;
	(*vars)->counter = 0;
	(*vars)->pers->y = -1;
	(*vars)->pers->x = -1;
	(*vars)->pers->orientation = 0;
	(*vars)->pers->items_get = 0;
}
