/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:35:21 by eberger           #+#    #+#             */
/*   Updated: 2023/03/06 13:41:48 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char *argv[])
{
	t_vars	*vars;

	vars = NULL;
	if (argc != 2)
		return (error_map("Nombre d'arguments incorrect", NULL));
	init_var(&vars, argv[1]);
	if (!create_map(vars->map))
		return (free_init_var(vars, NULL, NULL));
	if (!algo_test(vars->map->path))
		return (free_init_var(vars, &(vars->map->list), NULL));
	vars->mlx = mlx_init(vars->map->width, vars->map->height, "so_long", false);
	if (!vars->mlx)
		return (free_init_var(vars, &(vars->map->list), NULL));
	if (!show_map(vars))
		return (0);
	mlx_key_hook(vars->mlx, hook, vars);
	mlx_loop(vars->mlx);
	mlx_terminate(vars->mlx);
	free_init_var(vars, &(vars->map->list), &(vars->assets));
	return (1);
}
