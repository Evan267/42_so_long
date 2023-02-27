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
# define BUFFER_SIZE 1024
# endif

typedef struct s_pers {
	int	y;
	int	x;
	int	orientation;
	int	items_get;
}	t_pers;

typedef struct	s_maps {
	int		fd;
	int		size_box;
	int		line;
	int		column;
	int		height;
	int		width;
	t_list	*list;
}	t_maps;

typedef struct	s_assets {
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
}	t_assets;

typedef	struct	s_vars {
	int			counter;
	mlx_t		*mlx;
	t_maps		*map;
	t_assets	*assets;
	t_pers		*pers;
}	t_vars;

char	*ft_clear(char **str);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_linelen(char *s);
void	*ft_realloc(void *ptr, size_t size, size_t msize);
char	*get_next_line(int fd);

int		create_map(t_maps *map);
int		show_map(t_vars *vars);
t_assets	*init_imgs(mlx_t *mlx);
int		print_pers(t_vars *vars);
int		algo_test(char *path);

int				create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b);
unsigned char	get_t(int trgb);
unsigned char	get_r(int trgb);
unsigned char	get_g(int trgb);
unsigned char	get_b(int trgb);

#endif
