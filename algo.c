/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:43:15 by eberger           #+#    #+#             */
/*   Updated: 2023/03/31 15:30:02 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	create_list_map(t_list **list, char *path)
{
	char	*next_line;
	int		fd;

	fd = open(path, O_RDONLY);
	next_line = get_next_line(fd);
	while (next_line)
	{
		ft_lstadd_back(list, ft_lstnew(next_line));
		next_line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

int	flood(t_list **list, int *i, int x, int y)
{
	char	c;

	c = find_case(*list, x, y);
	if (c != '1' && c != '2')
	{
		if (c == 'C')
			i[0]++;
		if (c == 'E')
			i[1]++;
		change_case(*list, x, y, '2');
		flood(list, i, x + 1, y);
		flood(list, i, x - 1, y);
		flood(list, i, x, y + 1);
		flood(list, i, x, y - 1);
	}
	return (1);
}

int	find_start(t_list **list, int *loc)
{
	char	*str;
	t_list	*lst;

	lst = *list;
	str = lst->content;
	loc[0] = 0;
	loc[1] = 0;
	while (str[loc[0]] != 'P' && lst)
	{
		loc[0] = 0;
		while (str[loc[0]] != 'P' && str[loc[0]])
			loc[0]++;
		if (str[loc[0]] != 'P')
		{
			loc[1]++;
			lst = lst->next;
			str = lst->content;
		}
	}
	if (str[loc[0]] == 'P')
		return (1);
	else
		return (0);
}

int	find_all(t_list **list, char c)
{
	char	*str;
	t_list	*lst;
	int		count;

	lst = *list;
	count = 0;
	while (lst)
	{
		str = lst->content;
		while (*str)
		{
			if (*str == c)
				count++;
			str++;
		}
		lst = lst->next;
	}
	return (count);
}

int	algo_test(char *path)
{
	t_list	*list_map;
	int		i[2];
	int		loc[2];
	int		items;

	i[0] = 0;
	i[1] = 0;
	list_map = NULL;
	create_list_map(&list_map, path);
	if (find_all(&list_map, 'P') > 1)
		return (error_map("Plusieurs points de depart trouver", &list_map));
	if (!find_all(&list_map, 'P'))
		return (error_map("Aucun point de depart trouver", &list_map));
	find_start(&list_map, loc);
	items = find_all(&list_map, 'C');
	if (!items)
		return (error_map("Aucun item present sur la carte", &list_map));
	flood(&list_map, i, loc[0], loc[1]);
	if (i[0] != items || i[1] != 1)
		return (error_map("Item ou sortie non accessible", &list_map));
	return (ft_lstclear(&list_map, &free), 1);
}
