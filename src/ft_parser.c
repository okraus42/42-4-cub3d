/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 15:25:48 by okraus            #+#    #+#             */
/*   Updated: 2024/03/30 14:28:27 by okraus           ###   ########.fr       */
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

void	ft_load_texture(char *path, mlx_texture_t **texture)
{
	if (access(path, R_OK) < 0)
	{
		ft_dprintf(2, "Cannot open north texture\n");
		exit(-3);
	}
	*texture = mlx_load_png(path);
	if (!*texture)
		exit(-4);
}

int	ft_init_textures(t_max *max)
{
	ft_load_texture(max->map->northtexture, &max->t->nwall);
	ft_load_texture(max->map->westtexture, &max->t->wwall);
	ft_load_texture(max->map->southtexture, &max->t->swall);
	ft_load_texture(max->map->easttexture, &max->t->ewall);
	return (1);
}

static void	ft_map_init(t_map *map)
{
	int	i;

	map->mapstr = NULL;
	map->northtexture = NULL;
	map->southtexture = NULL;
	map->westtexture = NULL;
	map->easttexture = NULL;
	//map->d = NULL;
	map->valid = 1;
	map->e = -1;
	map->p.orientation = -1;
	map->p.x = 0;
	map->p.y = 0;
	map->p.speed = 16;
	map->p.turnspeed = 512;
	map->p.xspeed = 0;
	map->p.yspeed = 0;
	map->p.fov = FOV;
	map->p.fov2 = map->p.fov * 65536 / 720;
	map->h = 0;
	map->w = 0;
	map->f.rgba = 0;
	map->c.rgba = 0;
	map->b.rgba = 0xFF;
	i = 0;
	while (i < 65536)
	{
		map->m[i] = 0;
		++i;
	}
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

	if (!s)
		return (0);
	l = ft_strlen(s);
	if (l < 5)
		return (0);
	--l;
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

// need to check for invalid texture paths as well
int	ft_fill_textures(t_map *map)
{
	char	**split;
	int		j;

	split = ft_split(map->mapstr, '\n');
	if (!split)
		return(ft_puterror("Malloc error", 0));
	j = 0;
	while (split[j])
	{
		if (!ft_strncmp(split[j], "NO ", 3))
			map->northtexture = ft_strdup(&split[j][3]);
		if (!ft_strncmp(split[j], "SO ", 3))
			map->southtexture = ft_strdup(&split[j][3]);
		if (!ft_strncmp(split[j], "WE ", 3))
			map->westtexture = ft_strdup(&split[j][3]);
		if (!ft_strncmp(split[j], "EA ", 3))
			map->easttexture = ft_strdup(&split[j][3]);
		++j;
	}
	ft_free_split(&split);
	if (!map->northtexture || !map->southtexture || !map->westtexture
		|| !map->easttexture)
		return(ft_puterror("Missing texture path", 0));
	return (1);
}

int	ft_fill_colour2(char **split, int c, t_map *map)
{
	if (c == 'F')
	{
		map->f.r = ft_atoi(split[0]);
		map->f.g = ft_atoi(split[1]);
		map->f.b = ft_atoi(split[2]);
		map->f.a = 0xFF;
	}
	if (c == 'C')
	{
		map->c.r = ft_atoi(split[0]);
		map->c.g = ft_atoi(split[1]);
		map->c.b = ft_atoi(split[2]);
		map->c.a = 0xFF;
	}
	if (c == 'B')
	{
		map->b.r = ft_atoi(split[0]);
		map->b.g = ft_atoi(split[1]);
		map->b.b = ft_atoi(split[2]);
		map->b.a = 0xFF;
	}
	ft_free_split(&split);
	return (1);
}

int	ft_fill_colour(int c, char *s, t_map *map, int j)
{
	char	**split;
	int		i;

	split = ft_split(s, ',');
	if (!split)
		return(ft_puterror("Malloc error", 0));
	while (j < 3)
	{
		i = 0;
		while (split[j][i])
		{
			if (!ft_isdigit(split[j][i]))
			{
				ft_free_split(&split);
				return(ft_puterror("Invalid character in colour", 0));
			}
			++i;
		}
		if (i > 3 || j > 2 || ft_atoi(split[j]) > 255)
		{
			ft_free_split(&split);
			return(ft_puterror("Colour format is not right", 0));
		}
		++j;
	}
	return (ft_fill_colour2(split, c, map));
}

int	ft_fill_colours(t_map *map)
{
	char	**split;
	int		j;

	split = ft_split(map->mapstr, '\n');
	if (!split)
		return(ft_puterror("Malloc error", 0));
	j = 0;
	while (split[j])
	{
		if (!ft_strncmp(split[j], "F ", 2) || !ft_strncmp(split[j], "C ", 2)
			|| !ft_strncmp(split[j], "B ", 2))
			if (!ft_fill_colour(split[j][0], &split[j][2], map, 0))
			{
				ft_free_split(&split);
				return (0);
			}
		++j;
	}
	ft_free_split(&split);
	if (!map->c.rgba || !map->f.rgba)
		return(ft_puterror("Missing floor or ceiling colour, aborting...", 0));
	return (1);
}

int	ft_check_map(t_map *map, char **split, int j, int a)
{
	int	p;
	int	i;

	p = 0;
	while (split[j])
	{
		i = 0;
		while (split[j][i])
		{
			if (!ft_strchr(" 01NSEW", split[j][i]))
			{
				ft_free_split(&split);
				return(ft_puterror("Invalid character in map", 0));
			}
			if (ft_strchr("NSEW", split[j][i]))
				++p;
			++i;
			map->w = MAX(map->w, i);
		}
		++j;
	}
	map->h = j - a;
	if (p != 1)
	{
		ft_free_split(&split);
		if (!p)
			return(ft_puterror("No player location in the map", 0));
		else
			return(ft_puterror("Too many player locations in map", 0));
	}
	if (map->w < 3 || map->h <3 || map->w > 256 || map->h > 256)
	{
		ft_free_split(&split);
		return(ft_puterror("Wrong map dimensions, minimum size is 3x3", 0));
	}
	map->ww = map->w;
	map->w = 256;
	map->hh = map->h;
	map->h = 256;
	return (1);
}

void	ft_fill_array3(t_map *map, char c, int y, int x)
{
	if (c == '0')
		map->m[y * map->w + x] = FLOOR1;
	else if (c == '1')
		map->m[y * map->w + x] = WALL1;
	else if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		map->m[y * map->w + x] = FLOOR1;
		map->p.mx = x;
		map->p.my = y;
		map->p.sx = 0x7f7f;
		map->p.sy = 0x7f7f;
		map->p.unused_x = 0;
		map->p.unused_y = 0;
		if (c == 'N')
		{
			map->p.orientation = NORTH;
		}
		else if (c == 'W')
		{
			map->p.orientation = WEST;
		}
		else if (c == 'S')
		{
			map->p.orientation = SOUTH;
		}
		else if (c == 'E')
		{
			map->p.orientation = EAST;
		}
	}
}

// FLOORWN = 0x10,
// FLOORWE = 0x20,
// FLOORWS = 0x40,
// FLOORWW = 0x80,

void	ft_flood_check(t_map *map, int pos)
{
	if (map->m[pos] & FLOOD1)
		return ;
	if ((map->m[pos] & WALL))
		return ;
	if (!(map->m[pos]))
	{
		map->valid = 0;
		return ;
	}
	map->m[pos] |= FLOOD1;
	if (map->m[pos + 1] & WALL)
		map->m[pos] |= FLOORWE;
	if (map->m[pos - 1] & WALL)
		map->m[pos] |= FLOORWW;
	if (map->m[pos + map->w] & WALL)
		map->m[pos] |= FLOORWS;
	if (map->m[pos - map->w] & WALL)
		map->m[pos] |= FLOORWN;
	if (map->m[pos + map->w + 1] & WALL)
		map->m[pos] |= FLOORWSE;
	if (map->m[pos + map->w - 1] & WALL)
		map->m[pos] |= FLOORWSW;
	if (map->m[pos - map->w + 1] & WALL)
		map->m[pos] |= FLOORWNE;
	if (map->m[pos - map->w - 1] & WALL)
		map->m[pos] |= FLOORWNW;
	if (pos < map->w || pos > (map->h - 1) * map->w || !(pos % map->w)
		|| pos % map->w == map->w - 1)
	{
		map->valid = 0;
		return ;
	}
	ft_flood_check(map, pos + 1);
	ft_flood_check(map, pos - 1);
	ft_flood_check(map, pos + map->w);
	ft_flood_check(map, pos - map->w);
}

int	ft_fill_array2(t_map *map, char **split, int j, int a)
{
	int	i;

	while (split[j])
	{
		i = 0;
		while (split[j][i])
		{
			ft_fill_array3(map, split[j][i], j - a, i);
			++i;
		}
		++j;
	}
	ft_flood_check(map, map->p.mx + map->p.my * map->w);
	if (!map->valid)
	{
		ft_free_split(&split);
		return(ft_puterror("Invalid map border or player position", 0));
	}
	return (1);
}

int	ft_fill_array(t_map *map)
{
	char	**split;
	int		j;
	int		a;

	split = ft_split(map->mapstr, '\n');
	if (!split)
		return(ft_puterror("Malloc error", 0));
	j = 0;
	while (split[j])
	{
		if (ft_strchr(" 01", split[j][0]))
			break;
		++j;
	}
	if (!split[j])
	{
		ft_free_split(&split);
		return(ft_puterror("Map not found", 0));
	}
	a = j;
	if (!ft_check_map(map, split, j, a))
		return (0);
	if (!ft_fill_array2(map, split, j, a))
		return (0);
	ft_free_split(&split);
	return (1);
}

void	ft_fill_colours_to_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->h * map->w)
	{
		if (map->m[i] & FLOOR)
		{
			map->m[i] &= 0x00000000FFFFFFFF;
			map->m[i] |= ((unsigned long long)(map->f.rgba) << 32);
		}
		else if (map->m[i] & WALL)
		{
			map->m[i] &= 0x00000000FFFFFFFF;
			map->m[i] |= 0x000000FFFFFFFFFF;
		}
		else
			map->m[i] &= 0x00000000FFFFFFFF;
		++i;
	}
}

int	ft_fill_map(t_map *map)
{
	//fill paths to textures
	if (!ft_fill_textures(map))
		return (0);
	if (!ft_fill_colours(map))
		return (0);
	if (!ft_fill_array(map))
		return (0);
	//fill colours in map
	ft_fill_colours_to_map(map);
	//fill actual map (get width and height first)
	return (1);
}

	// unsigned int	m[65536];		//1d array of map representation
	// char			*file;			//original mapfile string
	// char			*mapstr;		//actual content of the file
	// char			*northtexture;	//path to the north texture
	// char			*southtexture;
	// char			*westtexture;
	// char			*easttexture;
	// t_clr			f;			//floor colour
	// t_clr			c;			//ceiling colour
	// int				valid;		//1 if valid map
	// int				w;			//width of map
	// int				h;			//height of map
	// t_player		p;			//player pos and orientation
	// unsigned int	e;			//position of exit on map, future stuff
	// t_door			**d;		//doors for bonus, NULL terminated array

void	ft_print_map(t_map *map)
{
	int	i;
	int	c;
	ft_printf("FILE: %s\n", map->file);
	ft_printf("%s\n", map->mapstr);
	ft_printf("N: <%s>\n", map->northtexture);
	ft_printf("S: <%s>\n", map->southtexture);
	ft_printf("W: <%s>\n", map->westtexture);
	ft_printf("E: <%s>\n", map->easttexture);
	ft_printf("f: %#8x, c: %#8x b: %#8x\n", map->f.rgba, map->c.rgba, map->b.rgba);
	ft_printf("valid %i, width %4i, height %4i\n", map->valid, map->w, map->h);
	ft_printf("Player posx %#8x, posy %#8x, ori: %5i\n", map->p.x, map->p.y, map->p.orientation);
	ft_printf("Player py %4x, px %4x \n", map->p.y, map->p.x);
	ft_printf("Player my %2x, sy %2x, mx %2x, sx %2x \n", map->p.my, map->p.sy, map->p.mx, map->p.sx);
	i = 0;
	while (i < map->h * map->w)
	{
		if (i == (map->p.mx + map->p.my * map->w))
		{
			if (map->p.orientation == NORTH)
				ft_printf("%^*C^^%C", map->c.rgba >> 8);
			else if (map->p.orientation == WEST)
				ft_printf("%^*C<<%C", map->c.rgba >> 8);
			else if (map->p.orientation == SOUTH)
				ft_printf("%^*Cvv%C", map->c.rgba >> 8);
			else if (map->p.orientation == EAST)
				ft_printf("%^*C>>%C", map->c.rgba >> 8);
			else
				ft_printf("%^*C??%C", map->c.rgba >> 8);
		}
		else if (map->m[i] & WALL)
			ft_printf("%^*C  %C", 0x333333);
		else if (map->m[i] & FLOOR)
			ft_printf("%^*C  %C", map->f.rgba >> 8);
		else if ((i & 0xff) < map->ww && ((i & 0xff00) >> 8) < map->hh)
			ft_printf("  ");
		++i;
		if (!(i % map->w) && ((i & 0xff00) >> 8) < map->hh)
			ft_printf("\n");
	}
	ft_printf("Indexing floor near walls\n");
	i = 0;
	while (i < map->h * map->w)
	{
		c = 0xffffff;
		if (map->m[i] & FLOORWN)
			c &= 0xFF80FF;
		if (map->m[i] & FLOORWS)
			c &= 0x80FFFF;
		if (map->m[i] & FLOORWW)
			c &= 0xFFFF80;
		if (map->m[i] & FLOORWE)
			c &= 0x40A040;
		if (i == (map->p.mx + map->p.my * map->w))
		{
			if (map->p.orientation == NORTH)
				ft_printf("%^*C^^%C", map->c.rgba >> 8);
			else if (map->p.orientation == WEST)
				ft_printf("%^*C<<%C", map->c.rgba >> 8);
			else if (map->p.orientation == SOUTH)
				ft_printf("%^*Cvv%C", map->c.rgba >> 8);
			else if (map->p.orientation == EAST)
				ft_printf("%^*C>>%C", map->c.rgba >> 8);
			else
				ft_printf("%^*C??%C", map->c.rgba >> 8);
		}
		else if (map->m[i] & WALL)
			ft_printf("%^*C  %C", 0x333333);
		else if (map->m[i] & FLOORW)
			ft_printf("%^*C  %C", c);
		else if (map->m[i] & FLOOR)
			ft_printf("%^*C  %C", map->f.rgba >> 8);
		else if ((i & 0xff) < map->ww && ((i & 0xff00) >> 8) < map->hh)
			ft_printf("  ");
		++i;
		if (!(i % map->w) && ((i & 0xff00) >> 8) < map->hh)
			ft_printf("\n");
	}
}

void	ft_init_brume(t_max *max)
{
	int	c;
	int	d;

	c = 0;
	while (c < 256)
	{
		d = 0;
		while (d < 256)
		{
			max->math->brumered[c][d] = PERCENTIL(c, max->map->b.r, d, 255);
			max->math->brumegreen[c][d] = PERCENTIL(c, max->map->b.g, d, 255);
			max->math->brumeblue[c][d] = PERCENTIL(c, max->map->b.b, d, 255);
			++d;
		}
		++c;
	}
}

int	ft_process_file(t_max *max)
{
	t_map	*map;

	map = max->map;
	ft_map_init(map);
	if (!ft_read_map(map))
	{
		ft_freemap(map);
		return (0);
	}
	if (!ft_fill_map(map))
	{
		ft_freemap(map);
		return (0);
	}
	if (!ft_init_textures(max))
	{
		ft_freemap(map);
		return (0);
	}
	ft_init_brume(max);
	// int i;

	// i = 0;
	// while (i < 256)
	// {
	// 	ft_printf("%i %i", max->math->brumered[255][i], max->map->b.r);
	// 	ft_printf(" %i %i ", max->math->brumegreen[0][i], max->map->b.g);
	// 	ft_printf("%i %i\n", max->math->brumeblue[128][i], max->map->b.b);
	// 	++i;
	// }
	//for debugging
	ft_print_map(map);
	ft_freemap(map);
	return (1);
}