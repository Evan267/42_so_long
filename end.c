/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:19:21 by eberger           #+#    #+#             */
/*   Updated: 2023/03/06 13:42:01 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	free_init_var(t_vars *vars, t_list **list, t_assets **assets)
{
	if (list)
		ft_lstclear(list, &free);
	if (assets)
		free(*assets);
	free(vars->map->path);
	free(vars->pers);
	free(vars->map);
	free(vars);
	return (0);
}

int	error_map(char *str, t_list **list)
{
	if (list)
		ft_lstclear(list, &free);
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
	return (0);
}

void	delete_img(t_vars *vars)
{
	mlx_delete_image(vars->mlx, vars->assets->img_lava);
	mlx_delete_image(vars->mlx, vars->assets->img_sol);
	mlx_delete_image(vars->mlx, vars->assets->img_pers_bottom);
	mlx_delete_image(vars->mlx, vars->assets->img_pers_top);
	mlx_delete_image(vars->mlx, vars->assets->img_pers_left);
	mlx_delete_image(vars->mlx, vars->assets->img_pers_right);
	mlx_delete_image(vars->mlx, vars->assets->img_items_lock);
	mlx_delete_image(vars->mlx, vars->assets->img_items_unlock);
	mlx_delete_image(vars->mlx, vars->assets->img_close_door);
	mlx_delete_image(vars->mlx, vars->assets->img_open_door);
	mlx_delete_image(vars->mlx, vars->assets->img_counter);
}

void	end(t_vars *vars)
{
	char	*counter;
	char	*str;
	int		s[2];

	counter = ft_itoa(vars->counter);
	str = ft_strjoin("Score : ", counter);
	s[0] = ft_strlen(str) * 10;
	s[1] = 20;
	if (s[0] > vars->map->width)
	{
		free(str);
		str = counter;
		s[0] = ft_strlen(str) * 10;
	}
	delete_img(vars);
	s[0] = vars->map->width / 2 - s[0] / 2;
	s[1] = vars->map->height / 2 - s[1] / 2;
	mlx_put_string(vars->mlx, str, s[0], s[1]);
	vars->end = 1;
	free(counter);
	free(str);
}
