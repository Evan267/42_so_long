/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:35:21 by eberger           #+#    #+#             */
/*   Updated: 2023/07/05 11:22:31 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	badmap(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (ft_strncmp(file + (len - 4), ".ber", 4))
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_vars	*vars;

	vars = NULL;
	if (argc != 2)
		return (error_map("Nombre d'arguments incorrect", NULL));
	if (badmap(argv[1]))
		return (error_map("Map invalide", NULL));
	init_var(&vars, argv[1]);
	if (!create_map(vars->map))
		return (free_init_var(vars, NULL, NULL));
	if (algo_test(vars->map->path))
		return (free_init_var(vars, &(vars->map->list), NULL));
	vars->mlx = mlx_init(vars->map->width, vars->map->height, "so_long", false);
	if (!vars->mlx)
		return (free_init_var(vars, &(vars->map->list), NULL));
	if (!show_map(vars))
		return (1);
	mlx_key_hook(vars->mlx, hook, vars);
	mlx_loop(vars->mlx);
	mlx_terminate(vars->mlx);
	free_init_var(vars, &(vars->map->list), &(vars->assets));
	return (0);
}
