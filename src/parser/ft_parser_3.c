/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:16:47 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 20:19:36 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_load_texture(char *path, mlx_texture_t **texture)
{
	if (access(path, R_OK) < 0)
	{
		ft_dprintf(2, "Cannot open texture\n");
		exit(-3);
	}
	*texture = mlx_load_png(path);
	if (!*texture)
		exit(-4);
}

int	ft_puterror(char *err, int r)
{
	ft_dprintf(2, "Error\n");
	if (err)
		ft_dprintf(2, "%s\n", err);
	return (r);
}

int	ft_checkfileextension(char *s)
{
	int	l;

	ft_printf("map->file2:%s\n", s);
	if (!s)
		return (0);
	l = ft_strlen(s);
	if (l < 5)
		return (0);
	--l;
	ft_printf("%s - %c\n", s, s[l]);
	if (s[l] != 'b' || s[l - 1] != 'u' || s[l - 2] != 'c' || s[l - 3] != '.')
		return (0);
	return (1);
}

int	ft_read_map(t_map *map)
{
	int	fd;
	int	r;

	if (!ft_checkfileextension(map->file))
		return (ft_puterror("Invalid file name", 0));
	fd = open(map->file, O_RDONLY);
	if (fd < 0)
		return (ft_puterror("Could not open the file", 0));
	map->mapstr = ft_calloc(69632 + 1, sizeof(char));
	if (!map->mapstr)
		return (ft_puterror("Malloc failure", 0));
	r = read(fd, map->mapstr, 69632);
	if (r <= 0)
		return (ft_puterror("Reading error", 0));
	if (r == 69632)
		return (ft_puterror("File too big", 0));
	r = close(fd);
	if (r < 0)
		return (ft_puterror("Unexpected error closing the file", 0));
	return (1);
}

int	ft_fill_textures(t_map *map)
{
	char	**split;
	int		j;

	split = ft_split(map->mapstr, '\n');
	if (!split)
		return (ft_puterror("Malloc error", 0));
	j = 0;
	while (split[j])
	{
		if (!ft_strncmp(split[j], "NO ", 3))
			map->northtexture = ft_strdup2(&split[j][3], ' ');
		if (!ft_strncmp(split[j], "SO ", 3))
			map->southtexture = ft_strdup2(&split[j][3], ' ');
		if (!ft_strncmp(split[j], "WE ", 3))
			map->westtexture = ft_strdup2(&split[j][3], ' ');
		if (!ft_strncmp(split[j], "EA ", 3))
			map->easttexture = ft_strdup2(&split[j][3], ' ');
		++j;
	}
	ft_free_split(&split);
	if (!map->northtexture || !map->southtexture || !map->westtexture
		|| !map->easttexture)
		return (ft_puterror("Missing texture path", 0));
	return (1);
}
