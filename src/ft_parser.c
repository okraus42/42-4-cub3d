/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 15:25:48 by okraus            #+#    #+#             */
/*   Updated: 2023/12/29 16:43:56 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

// int	ft_process_file(char *file, unsigned int map[65536])
// {
// 	//check file extension
// 	//count new lines
// 	//get max line size
// 	//get map width and height
// 	//fill map
// 	//check edges
// 	//check exit if there even is one
// }

//add two timing functions to libft
//add other is functions to libft

int	ft_process_file(t_map *map)
{
	int	i;
	int fd;
	int	r;

	map->mapstr = NULL;
	map->northtexture = NULL;
	map->southtexture = NULL;
	map->westtexture = NULL;
	map->easttexture = NULL;
	map->e = -1;
	map->p = -1;
	map->h = 0;
	map->w = 0;
	map->f.a = 0xff;
	map->c.a = 0xff;
	i = 0;
	while (i < 65536)
	{
		map->m[i] = 0;
		++i;
	}
	fd = open(map->file, O_RDONLY);
	if (fd < 0)
	{
		ft_dprintf(2, "Error\n");
		ft_dprintf(2, "Could not open the file\n");
		return (0);
	}
	map->mapstr = ft_calloc(69632 + 1, sizeof(char));
	if (!map->mapstr)
	{
		ft_dprintf(2, "Error\n");
		ft_dprintf(2, "Malloc failure\n");
		return (0);
	}
	r = read(fd, map->mapstr, 69632);
	if (r <= 0)
	{
		free(map->mapstr);
		map->mapstr = NULL;
		ft_dprintf(2, "Error\n");
		ft_dprintf(2, "Reading error\n");
		return (0);
	}
	if (r == 69632)
	{
		free(map->mapstr);
		map->mapstr = NULL;
		ft_dprintf(2, "Error\n");
		ft_dprintf(2, "File too big\n");
		return (0);
	}
	r = close(fd);
	if (r < 0)
	{
		free(map->mapstr);
		map->mapstr = NULL;
		ft_dprintf(2, "Error\n");
		ft_dprintf(2, "Unexpected error closing the file\n");
		return (0);
	}
	return (1);
}