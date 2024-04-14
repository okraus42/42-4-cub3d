/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:04:28 by okraus            #+#    #+#             */
/*   Updated: 2024/04/14 12:31:44 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	ft_freemap(t_map *map)
{
	if (map->mapstr)
		free(map->mapstr);
	map->mapstr = NULL;
	if (map->northtexture)
		free(map->northtexture);
	map->northtexture = NULL;
	if (map->southtexture)
		free(map->southtexture);
	map->southtexture = NULL;
	if (map->westtexture)
		free(map->westtexture);
	map->westtexture = NULL;
	if (map->easttexture)
		free(map->easttexture);
	map->easttexture = NULL;
	// if (map->d)
	// 	free(map->d); //door need better freeing
	// map->d = NULL;
}

void	ft_free(t_max *max)
{
	if (max)
	{
		if (max->menu.custommap.files)
			free (max->menu.custommap.files);
		max->menu.custommap.files = NULL;
		if (max->menu.saves.files)
			free (max->menu.saves.files);
		max->menu.saves.files = NULL;
		ft_freemap(&max->map);
		free(max);
	}
	max = NULL;
}

void	ft_exit(t_max *max, int exitcode)
{
	if (max)
		ft_free(max);
	exit(exitcode);
}
