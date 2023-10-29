/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mazegen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 13:32:35 by okraus            #+#    #+#             */
/*   Updated: 2023/10/29 17:38:57 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/header/libft.h"
#include <math.h>
#include <time.h>

// compile with libft.h
// pass number for width and height like 15 15

void	map_print(unsigned char map[16641], int w, int h)
{
	int	i;

	i = 0;
	while (i < w * h)
	{
		if (map[i] == 0)
			ft_printf("%^*C  %0C", 0x000000);
		else if (map[i] == 1)
			ft_printf("%^*C  %0C", 0x333333);
		else if (map[i] == 2)
			ft_printf("%^*C  %0C", 0x777777);
		else if (map[i] == 4)
			ft_printf("%^*C  %0C", 0xffffff);
		else if (map[i] == 8)
			ft_printf("%^*C  %0C", 0x555555);
		else if (map[i] == 16)
			ft_printf("%^*C  %0C", 0x775555);
		else if (map[i] == 32)
			ft_printf("%^*C  %0C", 0x557755);
		else if (map[i] == 64)
			ft_printf("%^*C  %0C", 0x557777);
		else if (map[i] == 128)
			ft_printf("%^*C  %0C", 0x775577);
		++i;
		if (i % w == 0)
			ft_printf("\n");
	}
}

void	map_prefill(unsigned char map[16641], int w, int h)
{
	int	i;

	i = 0;
	while (i < w * h)
	{
		if ((i / w) & 1 && !(i & 1))
			map[i] = 2;
		else if (i > w && i < (h - 1) * w && i % w && i % w < (w - 1))
			map[i] = 1;
		else
			map[i] = 0;
		++i;
	}
}

int	mg_north(unsigned char map[16641], int w,  int p)
{
	if (map[p - w] == 0 )	//	do not care about walls
		return (0);
	if (map[p - (w * 2)] == 2)
	{
		map[p - (w * 2)] = 16;
		map[p - (w)] = 8;
		return (p - (w * 2));
	}
	else					//	do not care about previously visited location
		return (0);
	return (p);
}

int	mg_south(unsigned char map[16641], int w, int p)
{
	if (map[p + w] == 0)
		return (0);
	if (map[p + (w * 2)] == 2)
	{
		map[p + (w * 2)] = 32;
		map[p + (w)] = 8;
		return (p + (w * 2));
	}
	return (p);
}

int	mg_east(unsigned char map[16641], int p)
{
	if (map[p + 1] == 0)
		return (0);
	if (map[p + 2] == 2)
	{
		map[p + 2] = 64;
		map[p + 1] = 8;
		return (p + 2);
	}
	return (p);
}

int	mg_west(unsigned char map[16641], int p)
{
	if (map[p - 1] == 0)
		return (0);
	if (map[p - 2] == 2)
	{
		map[p - 2] = 128;
		map[p - 1] = 8;
		return (p - 2);
	}
	return (p);
}

int	check_unvisited_neighbours(unsigned char map[16641], int w, int p)
{
	if (map[p - 1] != 0 && map[p - 2] == 2)
		return (0);
	if (map[p + 1] != 0 && map[p + 2] == 2)
		return (0);
	if (map[p - w] != 0 && map[p - (w * 2)] == 2)
		return (0);
	if (map[p + w] != 0 && map[p + (w * 2)] == 2)
		return (0);
	return (1);
}

int	maze_gen(unsigned char map[16641], int w, int h)
{
	int		i;
	int		d;
	t_list	*lst;
	t_list	*ltemp;
	int		*temp;

	i = 0;
	srand(time(0));
	while (!((i / w) & 1 && !(i & 1)))
		i = rand() % (w * h);
	map[i] = 4;
	temp = malloc(sizeof(int));
	if (!temp)
		return (1);
	*temp = i;
	lst = ft_lstnew(temp);
	if (!lst)
		return (1);
	while (lst)
	{
		//ft_printf("i = %i\n", i);
		//map_print(map, w, h);
		//ft_printf("\n");
		d = rand() % 4;
		if (d == 0)			// maze North
			d = mg_north(map, w, i);
		else if (d == 1)	// maze East
			d = mg_east(map, i);
		else if (d == 2)	// maze South
			d = mg_south(map, w, i);
		else if (d == 3)	// maze West
			d = mg_west(map, i);
		if (d)
		{
			//add new location to the list of active locations
			temp = malloc(sizeof(int));
			if (!temp)
				return (1);
			ltemp = ft_lstnew(temp);
			if (!ltemp)
				return (1);
			*temp = d;
			ft_lstadd_front(&lst, ltemp);
		}
		// check if newest list has neigbours if not remove from the list
		while (lst && check_unvisited_neighbours(map, w, *(int *)lst->content))
		{
			ltemp = lst->next;
			ft_lstdelone(lst, free);
			lst = ltemp;
		}
		if (lst)
			i = *(int *)lst->content;
	}
	return (0);
}

int	main(int ac, char *av[])
{
	int				width;
	int				height;
	unsigned char	map[16641];

	if (ac != 3)
		return (2);
	width = ft_atoi(av[1]);
	height = ft_atoi(av[2]);
	if (width < 3 || height < 3 || width > 64 || height > 64)
		return (1);
	map_prefill(map, (width * 2 + 1), (height * 2 + 1));
	//prefill map
	//create maze
	maze_gen(map, (width * 2 + 1), (height * 2 + 1));
	//print maze
	map_print(map, (width * 2 + 1), (height * 2 + 1));
	return (0);
}