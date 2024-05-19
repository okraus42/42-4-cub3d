/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:04:28 by okraus            #+#    #+#             */
/*   Updated: 2024/05/11 13:06:05 by okraus           ###   ########.fr       */
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
}

void	ft_delete_textures(t_max *max)
{
	mlx_delete_texture(max->t.supermapwall);
	mlx_delete_texture(max->t.supermapfloor);
	mlx_delete_texture(max->t.menubg);
	mlx_delete_texture(max->t.button);
	mlx_delete_texture(max->t.buttonplus);
	mlx_delete_texture(max->t.textfield);
	mlx_delete_texture(max->t.listfield);
	mlx_delete_texture(max->t.font);
	mlx_delete_texture(max->t.textbg);
	mlx_delete_texture(max->t.sprites[EXIT_GLOW]);
	mlx_delete_texture(max->t.sprites[FLAMINGO_TEXTURE]);
	mlx_delete_texture(max->t.sprites[FLAMINGO_GLOW]);
	mlx_delete_texture(max->t.door);
	mlx_delete_texture(max->t.nwall);
	mlx_delete_texture(max->t.wwall);
	mlx_delete_texture(max->t.swall);
	mlx_delete_texture(max->t.ewall);
	mlx_delete_texture(max->t.pool);
}

void	ft_free(t_max *max)
{
	if (max)
	{
		ft_delete_textures(max);
		if (max->menu.custommap.files)
			ft_free_split(&max->menu.custommap.files);
		max->menu.custommap.files = NULL;
		if (max->menu.saves.files)
			ft_free_split(&max->menu.saves.files);
		if (max->menu.saves.files)
			ft_free_split(&max->menu.loads.files);
		max->menu.saves.files = NULL;
		ft_freemap(&max->map);
		mlx_terminate(max->mlx);
		if (max->math)
			free(max->math);
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
