SRCS	= main.c get_next_line.c get_next_line_utils.c map.c assets.c algo.c perso.c hook.c tools.c end.c

OBJS	= ${SRCS:.c=.o}

LFT		= libft/libft.a

MLX		= mlx42

HEAD	= so_long.h /Users/$$USER/MLX42/include

NAME	= so_long

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

.c.o:	
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${MLX} ${LFT} ${OBJS}
			${CC} ${OBJS} -L ./libft -lft "/Users/$$USER/MLX42/build/libmlx42.a" -lglfw -L"/Users/$$USER/.brew/opt/glfw/lib/" -framework Cocoa -framework OpenGL -framework IOKit -o ${NAME}

${LFT}:
			make -s -C libft
			make bonus -C libft

all:		${NAME}

${MLX}:	
			@if [ -d /Users/$$USER/MLX42/.git ]; then \
				echo "MLX42 est presente"; \
			else \
				cd && git clone https://github.com/codam-coding-college/MLX42.git; \
			fi
			@if [ -f /Users/$$USER/MLX42/build/libmlx42.a ]; then \
				echo "La libraire est presente"; \
			else \
				cd /Users/$$USER/MLX42 && cmake -B build && make -s -C build; \
			fi

clean:
			${RM} ${OBJS}
			make clean -C libft

fclean:		clean
			${RM} ${NAME}
			make fclean -C libft

re:			fclean all

.PHONY: all clean fclean re
