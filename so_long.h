/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:22:04 by eberger           #+#    #+#             */
/*   Updated: 2023/03/06 11:42:45 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <memory.h>
# include "/Users/eberger/MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# ifndef BOX
#  define BOX 32
# endif

typedef struct s_pers {
	int	y;
	int	x;
	int	orientation;
	int	items_get;
}	t_pers;

typedef struct s_maps {
	char	*path;
	int		fd;
	int		size_box;
	int		line;
	int		column;
	int		height;
	int		width;
	t_list	*list;
}	t_maps;

typedef struct s_assets {
	mlx_image_t		*img_lava;
	mlx_image_t		*img_sol;
	mlx_image_t		*img_pers_bottom;
	mlx_image_t		*img_pers_top;
	mlx_image_t		*img_pers_left;
	mlx_image_t		*img_pers_right;
	mlx_image_t		*img_items_lock;
	mlx_image_t		*img_items_unlock;
	mlx_image_t		*img_close_door;
	mlx_image_t		*img_open_door;
	mlx_image_t		*img_counter;
}	t_assets;

typedef struct s_vars {
	int			counter;
	int			end;
	mlx_t		*mlx;
	t_maps		*map;
	t_assets	*assets;
	t_pers		*pers;
}	t_vars;

char		*ft_clear(char **str);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_linelen(char *s);
void		*ft_realloc(void *ptr, size_t size, size_t msize);
char		*get_next_line(int fd);

int			error_map(char *str, t_list **list);
char		find_case(t_list *list, int x, int y);
void		change_case(t_list *list, int x, int y, char c);
int			put_counter(t_vars *vars, char *str_counter);
void		init_var(t_vars **vars, char *path);
int			test_close(int size_list, int i, char *str);
int			free_init_var(t_vars *vars, t_list **list, t_assets **assets);

void		print(t_vars *vars, mlx_image_t *img, int *loc, int z);
int			create_map(t_maps *map);
int			show_map(t_vars *vars);
int			init_imgs(t_vars *vars);
int			print_pers(t_vars *vars);
void		move_pers(t_vars *vars, int orientation);
void		hook(mlx_key_data_t keydata, void *param);
int			algo_test(char *path);
void		end(t_vars *vars);

#endif
