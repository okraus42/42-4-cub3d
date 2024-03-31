/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gameplay.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 10:47:00 by okraus            #+#    #+#             */
/*   Updated: 2024/03/31 11:53:04 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"




// int	ft_is_inside2(t_max *max, unsigned int rad2, int y, int x)
// {
// 	unsigned int	cx;
// 	unsigned int	cy;

// 	cx = x - (int)max->map->p.x + max->math->sin[max->map->p.orientation] / 1024;
// 	cy = y - (int)max->map->p.y + max->math->cos[max->map->p.orientation] / 1024;
// 	if (cx * cx + cy * cy <= rad2)
// 		return (1);
// 	return (0);
// }
void	ft_erase_map(t_max *max)
{
	int	y;
	int	x;

	y = 0;
	while (y < MAPHEIGHT)
	{
		x = 0;
		while (x < MAPWIDTH)
		{
			mlx_put_pixel(max->maximap, x, y, 0x0);
			++x;
		}
		++y;
	}
}

// Weird psychadelich stuff
// unsigned int	ft_get_colour(int x, int xw, int y, int wh, mlx_texture_t *img)
// {
// 	unsigned int	r;
// 	int				h;
// 	int				w;
// 	int				p;

// 	w = img->width;
// 	h = img->height;
// 	p = w * y / wh + 0 * h;
// 	r = (img->pixels[p] << 24) | (img->pixels[p + 1] << 16) | (img->pixels[p + 2] << 8) | 0x0000FF;
// 	(void)x;
// 	(void)xw;
// 	return (r);
// }

// unsigned int	ft_get_colour(t_max *max, int x, long long length, int y, int wh, mlx_texture_t *img)
// {
// 	t_clr			r;
// 	int				h;
// 	int				w;
// 	int				p;
// 	int				xw;

// 	xw = 65536;
// 	w = img->width;
// 	h = img->height;
// 	p = w * 4 * (h * y / wh) + (4 * (w * x / xw));
// 	//ft_printf("%i %i\n",(h * y / wh), (w * x / xw));
// 	r.rgba = (img->pixels[p] << 24) | (img->pixels[p + 1] << 16) | (img->pixels[p + 2] << 8) | 0x0000FF;
// 	if (length > MAXDIST)
// 		length = MAXDIST;
// 	r.r = max->math->brumered[r.r][length * 255LL / MAXDIST];
// 	r.g = max->math->brumegreen[r.g][length * 255LL / MAXDIST];
// 	r.b = max->math->brumeblue[r.b][length * 255LL / MAXDIST];
// 	return (r.rgba);
// }

// unsigned int	ft_get_colour2(t_max *max, unsigned int c, int y, int fake_offset)
// {
// 	t_clr			r;
// 	int				length;
// 	int				start;
// 	int				offset;

// 	r.rgba = c;
// 	offset = HEIGHT / 2 - fake_offset;
// 	start = 2 * offset;
// 	if (y < HEIGHT / 2)
// 		length = PERCENTIL(0, 255, start + y, HEIGHT / 2 + offset);
// 	else
// 		length = PERCENTIL(0, 255, start + (HEIGHT - y), HEIGHT / 2 + offset);
// 	// if (y < HEIGHT / 2)
// 	//  	ft_printf("%i %i %i %i || %i %i\n", start, length, y, offset, start + y, HEIGHT / 2 + offset);
// 	//ft_printf("1 %3i %3i %3i %3i || ", r.r, r.g, r.b, length); 
// 	r.r = max->math->brumered[r.r][length];
// 	r.g = max->math->brumegreen[r.g][length];
// 	r.b = max->math->brumeblue[r.b][length];
// 	//ft_printf("2 %3i %3i %3i %3i\n", r.r, r.g, r.b, length); 
// 	return (r.rgba);
// }

// void	ft_get_colour3(t_max *max, unsigned int c, int y, int fake_offset)
// {
// 	t_clr			r;
// 	int				length;
// 	int				start;
// 	int				offset;

// 	r.rgba = c;
// 	offset = HEIGHT / 2 - fake_offset;
// 	start = 2 * offset;
// 	if (y < HEIGHT / 2)
// 		length = PERCENTIL(0, 255, start + y, HEIGHT / 2 + offset);
// 	else
// 		length = PERCENTIL(0, 255, start + (HEIGHT - y), HEIGHT / 2 + offset);
// 	// if (y < HEIGHT / 2)
// 	//  	ft_printf("%i %i %i %i || %i %i\n", start, length, y, offset, start + y, HEIGHT / 2 + offset);
// 	ft_printf("1 %3i %3i %3i %3i || ", r.r, r.g, r.b, length); 
// 	r.r = max->math->brumered[r.r][length];
// 	r.g = max->math->brumegreen[r.g][length];
// 	r.b = max->math->brumeblue[r.b][length];
// 	ft_printf("2 %3i %3i %3i %3i\n", r.r, r.g, r.b, length); 
// }

// void	ft_draw_screen(t_max *max)
// {
// 	int	y;
// 	int	x;
// 	int	r;
// 	int	wall_height;
// 	int	offset;
// 	int	fake_wall_height;
// 	int	fake_offset;
// 	long long	length;
// 	long long	fake_length;

// 	x = 0;
// 	while (x < SCREENWIDTH)
// 	{
// 		y = 0;
// 		r = x * RAYS / SCREENWIDTH;
// 		//ft_printf("new ray\n");
// 		//ft_printf("%i %i\n", r, x);
// 		length = max->map->p.ray[r].length;
// 		fake_length = MAXDIST;
// 		if (NOFISHEYE)
// 		{
// 			//ft_printf("L1 %Lx\n", max->map->p.ray[r].length);
// 			//ft_printf("ANGLE %i\n", (unsigned short)(max->map->p.orientation - max->map->p.ray[r].ra));
// 			length *= max->math->cos[(unsigned short)(max->map->p.orientation - max->map->p.ray[r].ra)];
// 			fake_length *= max->math->cos[(unsigned short)(max->map->p.orientation - max->map->p.ray[r].ra)];
// 			//ft_printf("L2 %Lx\n", max->map->p.ray[r].length);
// 			length /= 65536;
// 			fake_length /= 65536;
// 			//ft_printf("L3 %Lx\n", max->map->p.ray[r].length);
// 		}
// 		//ft_printf("b\n");
// 		//ft_printf("%i\n", wall_height);
// 		fake_wall_height = 65536 * SCREENHEIGHT / fake_length;
// 		wall_height = 65536 * SCREENHEIGHT / length;
// 		//ft_printf("wall: %i %i\n", wall_height, fake_wall_height);
// 		//ft_printf("c\n");
// 		// if (wall_height > SCREENHEIGHT)
// 		// 	wall_height = SCREENHEIGHT;
// 		if (length > MAXDIST || !max->map->p.ray[r].wall)
// 			wall_height = 0;
// 		offset = SCREENHEIGHT / 2 - wall_height / 2;
// 		fake_offset = SCREENHEIGHT / 2 - fake_wall_height / 2;
// 		//ft_printf("offset: %i %i\n", offset, fake_offset);
// 		while (y < SCREENHEIGHT)
// 		{
// 			if (y < offset && y < fake_offset)
// 			{
// 				//mlx_put_pixel(max->screen, x, y, 0x000000FF);
// 				//mlx_put_pixel(max->screen, x, y, max->map->c.rgba);
// 				// if (x == 512)
// 				// 	ft_get_colour3(max, max->map->c.rgba, y, fake_offset);
// 				mlx_put_pixel(max->screen, x, y, ft_get_colour2(max, max->map->c.rgba, y, fake_offset));
// 			}
// 			else if (y > offset && y < wall_height + offset)
// 			{
// 				//ft_printf("AAAAAA\n");
// 				//mlx_put_pixel(max->screen, x, y, max->map->p.ray[r].c[1]);
// 				if (max->map->p.ray[r].wall & NWALL)
// 				{
// 					//mlx_put_pixel(max->screen, x, y, ft_get_colour(x / 4, 1920 / 4, y - offset, wall_height, max->t->nwall));

// 					mlx_put_pixel(max->screen, x, y, ft_get_colour(max, max->map->p.ray[r].rx % 65536, max->map->p.ray[r].length, y - offset, wall_height, max->t->nwall));
// 				}
// 				else if (max->map->p.ray[r].wall & EWALL)
// 					mlx_put_pixel(max->screen, x, y, ft_get_colour(max, max->map->p.ray[r].ry % 65536, max->map->p.ray[r].length, y - offset, wall_height, max->t->ewall));
// 				else if (max->map->p.ray[r].wall & SWALL)
// 					mlx_put_pixel(max->screen, x, y, ft_get_colour(max, max->map->p.ray[r].rx % 65536, max->map->p.ray[r].length, y - offset, wall_height, max->t->swall));
// 				else if (max->map->p.ray[r].wall & WWALL)
// 					mlx_put_pixel(max->screen, x, y, ft_get_colour(max, max->map->p.ray[r].ry % 65536, max->map->p.ray[r].length, y - offset, wall_height, max->t->wwall));
// 				else
// 					mlx_put_pixel(max->screen, x, y, 0xFF00FFFF);
// 			}
// 			else if (y < fake_wall_height + fake_offset)
// 			{
// 				mlx_put_pixel(max->screen, x, y, max->map->b.rgba);
// 			}
// 			else
// 			{
// 				//mlx_put_pixel(max->screen, x, y, 0x000000FF);
// 				//mlx_put_pixel(max->screen, x, y, max->map->f.rgba);
// 				mlx_put_pixel(max->screen, x, y, ft_get_colour2(max, max->map->f.rgba, y, fake_offset));

// 			}
// 			++y;
// 		}
// 		++x;
// 	}
// }

void	ft_move_player(t_map *map, int y, int x)
{
	//ft_printf ("%x %x %x %x %x\n",y >> 8, x >> 8, map->m[((y >> 8) * map->w + (x >> 8))], WALL);
	//ft_printf("moving player\n");
	if (map->m[((y >> 16) * map->w + (x >> 16))] & WALL)
	{
		//ft_printf("You are in a wall\n");
		return ;
	}
	else
	{
		map->p.y = y;
		map->p.x = x;
		if (map->m[map->p.my * map->w + map->p.mx] & FLOORWN)
		{
			if (y < ((map->p.my << 16) | WALLDISTANCE))
				map->p.sy = WALLDISTANCE;
		}
		if (map->m[map->p.my * map->w + map->p.mx] & FLOORWNW
			&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWN)
			&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWW))
		{
			if (y < ((map->p.my << 16) | WALLDISTANCE)
				&& x < ((map->p.mx << 16) | WALLDISTANCE))
			{
				if ((x & 0xFFFF) <= (y & 0xFFFF))
					map->p.sy = WALLDISTANCE;
				if ((y & 0xFFFF) <= (x & 0xFFFF))
					map->p.sx = WALLDISTANCE;
			}
		}
		if (map->m[map->p.my * map->w + map->p.mx] & FLOORWNE
			&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWN)
			&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWE))
		{
			if (y < ((map->p.my << 16) | WALLDISTANCE)
				&& x > ((map->p.mx << 16) | (SQUARESIZE - WALLDISTANCE)))
			{
				if (((SQUARESIZE - x) & 0xFFFF) <= (y & 0xFFFF))
					map->p.sy = WALLDISTANCE;
				if ((y & 0xFFFF) <= ((SQUARESIZE - x) & 0xFFFF))
					map->p.sx = SQUARESIZE - WALLDISTANCE;
			}
		}
		if (map->m[map->p.my * map->w + map->p.mx] & FLOORWS)
		{
			if (y > ((map->p.my << 16) | (SQUARESIZE - WALLDISTANCE)))
				map->p.sy = SQUARESIZE - WALLDISTANCE;
		}
		if (map->m[map->p.my * map->w + map->p.mx] & FLOORWSW
			&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWS)
			&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWW))
		{
			if (y > ((map->p.my << 16) | (SQUARESIZE - WALLDISTANCE))
				&& x < ((map->p.mx << 16) | WALLDISTANCE))
			{
				if ((x & 0xFFFF) <= ((SQUARESIZE - y) & 0xFFFF))
					map->p.sy = SQUARESIZE - WALLDISTANCE;
				if (((SQUARESIZE - y) & 0xFFFF) <= (x & 0xFFFF))
					map->p.sx = WALLDISTANCE;
			}
		}
		if (map->m[map->p.my * map->w + map->p.mx] & FLOORWSE
			&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWS)
			&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWE))
		{
			if (y > ((map->p.my << 16) | (SQUARESIZE - WALLDISTANCE))
				&& x > ((map->p.mx << 16) | (SQUARESIZE - WALLDISTANCE)))
			{
				if (((SQUARESIZE - x) & 0xFFFF) <= ((SQUARESIZE - y) & 0xFFFF))
					map->p.sy = SQUARESIZE - WALLDISTANCE;
				if (((SQUARESIZE - y) & 0xFFFF) <= ((SQUARESIZE - x) & 0xFFFF))
					map->p.sx = SQUARESIZE - WALLDISTANCE;
			}
		}
		if (map->m[map->p.my * map->w + map->p.mx] & FLOORWW)
		{
			if (x < ((map->p.mx << 16) | WALLDISTANCE))
				map->p.sx = WALLDISTANCE;
		}
		if (map->m[map->p.my * map->w + map->p.mx] & FLOORWE)
		{
			if (x > ((map->p.mx << 16) | (SQUARESIZE - WALLDISTANCE)))
				map->p.sx = SQUARESIZE - WALLDISTANCE;
		}
		//ft_printf("moved player\n");
	}
}

//makes map less visible
void	ft_revisit_map(t_map *map)
{
	int	y;

	map->m[map->p.my * map->w + map->p.mx] |= VISITED;
	y = 0;
	while (y < map->hh * map->w)
	{
		if (map->m[y] & VISITED)
		{
			//ft_printf("old%Lx\n", map->m[y]);
			map->m[y] -= (VISIT);
			//ft_printf("new%Lx\n", map->m[y]);
		}
		++y;
	}
}

//hook for moving player on the map
//create hook for moving map instead of player

void	ft_draw_strings(t_max *max)
{
	if (DEBUGGING)
	{
		if (max->key.two)
		{
			++max->ray;
			max->key.two = 0;
		}
		if (max->key.three)
		{
			--max->ray;
			max->key.three = 0;
		}
		if (max->ray == RAYS)
			max->ray = 0;
		if (max->ray < 0)
			max->ray = RAYS - 1;
		if (max->key.one)
			ft_snprintf(max->s[0], 255, "FPS: %3i  Pos [%6x] [%6x]   Orientation [%5i]",
				1000 / max->framems, max->map->p.x, max->map->p.y,
				max->map->p.orientation);
		else
			ft_snprintf(max->s[0], 255, "Ray [%4i] ra [%5i] c0[%8x] c1[%8x] length[%Li]", max->ray,
				max->map->p.oray[max->ray].ra, max->map->p.oray[max->ray].c[0],
				max->map->p.oray[max->ray].c[1], max->map->p.oray[max->ray].length);
		mlx_delete_image(max->mlx, max->str[0]);
		//mlx_delete_image(max->mlx, max->str[1]);
		
		max->str[0] = mlx_put_string(max->mlx, max->s[0], 10, 5);
		//max->str[1] = mlx_put_string(max->mlx, max->s[1], 10, 35);
	}
	else
	{
		ft_snprintf(max->s[0], 255, "FPS: %3i   Pos [%6x] [%6x]   Orientation [%3i]",
			1000 / max->framems, max->map->p.x, max->map->p.y,
			max->map->p.orientation * 360 / MAXDEGREE);
		mlx_delete_image(max->mlx, max->str[0]);
		max->str[0] = mlx_put_string(max->mlx, max->s[0], 10, 5);
	}
}

// void	ft_debug(t_max *max)
// {
// 	if (max->key.five)
// 	{
// 		max->map->p.x = 0x214d9c;
// 		max->map->p.y = 0x29d6a8;
// 		max->map->p.orientation = 15568;
// 		max->ray = 547;
// 		max->key.five = 0;
// 	}
// 	if (max->key.six)
// 	{
// 		max->map->p.x = 0x45f0c;
// 		max->map->p.y = 0x10ec2c;
// 		max->map->p.orientation = 8486;
// 		max->ray = 282;
// 		max->key.six = 0;
// 	}
// 	if (max->key.seven)
// 	{
// 		max->map->p.x = 0x564a5;
// 		max->map->p.y = 0x326b45;
// 		max->map->p.orientation = 7774;
// 		max->ray = 126;
// 		max->key.seven = 0;
// 	}
// 	if (max->key.eight)
// 	{
// 		max->map->p.x = 0x5fdb1;
// 		max->map->p.y = 0x361ed9;
// 		max->map->p.orientation = 7774;
// 		max->ray = 584;
// 		max->key.eight = 0;
// 	}
// }

void	ft_gameplay(t_max *max)
{
// max->newms = ft_get_time_in_ms();
	// max->framems = (unsigned int)(max->newms - max->oldms);
	//ft_printf("framems: %u\n", max->framems);
	// Add some max speed to prevent running through walls.
	max->map->p.turnspeed = max->framems * 8;
	max->map->p.speed = MIN(4 * 8 * 128, 128 * 8 * max->framems);
	max->map->p.xspeed = (max->map->p.speed * max->math->cos[max->map->p.orientation]) / 65536;
	max->map->p.yspeed = -(max->map->p.speed * max->math->sin[max->map->p.orientation]) / 65536;
	++max->frame;
	// max->oldms = max->newms;
	max->map->p.dx = -max->math->sin[max->map->p.orientation];
	max->map->p.dy = -max->math->cos[max->map->p.orientation];
	// size based on fov... maybe tangens? fov cannot be more than 180
	max->map->p.cx = max->math->cos[max->map->p.orientation];
	max->map->p.cy = max->math->sin[max->map->p.orientation];
	ft_draw_strings(max);
	//ft_debug(max);
	//ft_printf("test\n");
	// if (mlx_is_key_down(max->mlx, MLX_KEY_ESCAPE))
	// {
	// 	max->game_mode = MENU;
	// 	max->menuscreen->enabled = 1;
	// 	// ft_printf("You have quit the game by pressing ESC.\n");
	// 	// mlx_close_window(max->mlx);
	// }
	if (max->keys[MLX_KEY_SPACE])	//sprinting, faster but slower turns LIMIT STAMINA
	{
		//ft_printf("You have pressed space.\n");
		max->map->p.xspeed *= 2;
		max->map->p.yspeed *= 2;
		max->map->p.turnspeed /= 2;
	}
	if (max->keys[MLX_KEY_LEFT_SHIFT])	//sprinting, faster but slower turns LIMIT STAMINA
	{
		//ft_printf("You have pressed space.\n");
		max->map->p.xspeed *= 2;
		max->map->p.yspeed *= 2;
		max->map->p.turnspeed /= 2;
	}
	if (max->keys[MLX_KEY_1])	//key1
	{
		if (max->key.one)
			max->key.one = 0;
		else
			max->key.one = 1;
		max->keys[MLX_KEY_1] = 0;
	}
	if (max->keys[MLX_KEY_2])
	{
		if (max->key.two)
			max->key.two = 0;
		else
			max->key.two = 1;
		max->keys[MLX_KEY_2] = 0;
	}
	if (max->keys[MLX_KEY_3])
	{
		if (max->key.three)
			max->key.three = 0;
		else
			max->key.three = 1;
		max->keys[MLX_KEY_3] = 0;
	}
	if (max->keys[MLX_KEY_4])
	{
		if (max->key.four)
			max->key.four = 0;
		else
			max->key.four = 1;
	}
	if (max->keys[MLX_KEY_5])
	{
		if (max->key.five)
			max->key.five = 0;
		else
			max->key.five = 1;
	}
	if (max->keys[MLX_KEY_6])
	{
		if (max->key.six)
			max->key.six = 0;
		else
			max->key.six = 1;
	}
	if (max->keys[MLX_KEY_7])
	{
		if (max->key.seven)
			max->key.seven = 0;
		else
			max->key.seven = 1;
	}
	if (max->keys[MLX_KEY_8])
	{
		if (max->key.eight)
			max->key.eight = 0;
		else
			max->key.eight = 1;
	}
	if (max->keys[MLX_KEY_9])
	{
		if (max->key.nine)
			max->key.nine = 0;
		else
			max->key.nine = 1;
	}
	if (max->keys[MLX_KEY_0])
	{
		if (max->key.zero)
			max->key.zero = 0;
		else
			max->key.zero = 1;
	}
	if (max->keys[MLX_KEY_UP] || max->keys[MLX_KEY_W])
	{
		//ft_printf("You have pressed up arrow.\n");
		//ft_printf("xspeed %i | yspeed %i | orientation %i.\n", max->map->p.xspeed, max->map->p.yspeed, max->map->p.orientation);
		ft_move_player(max->map, max->map->p.y - max->map->p.xspeed, max->map->p.x - max->map->p.yspeed);
	}
	if (max->keys[MLX_KEY_DOWN] || max->keys[MLX_KEY_S])
	{
		//ft_printf("You have pressed down arrow.\n");
		ft_move_player(max->map, max->map->p.y + max->map->p.xspeed, max->map->p.x + max->map->p.yspeed);
	}
	if (max->keys[MLX_KEY_A])
	{
		//ft_printf("You have pressed A.\n");
		ft_move_player(max->map, max->map->p.y + max->map->p.yspeed, max->map->p.x - max->map->p.xspeed);
	}
	if (max->keys[MLX_KEY_D])
	{
		//ft_printf("You have pressed D.\n");
		ft_move_player(max->map, max->map->p.y - max->map->p.yspeed, max->map->p.x + max->map->p.xspeed);
	}
	if (max->keys[MLX_KEY_LEFT] || max->keys[MLX_KEY_Q])
	{
		//ft_printf("You have pressed left arrow.\n");
		//ft_printf("xspeed %i | yspeed %i | orientation %i.\n", max->map->p.xspeed, max->map->p.yspeed, max->map->p.orientation);
		max->map->p.orientation -= max->map->p.turnspeed;
		if (max->map->p.orientation < 0)
			max->map->p.orientation += MAXDEGREE;
	}
	if (max->keys[MLX_KEY_RIGHT] || max->keys[MLX_KEY_E])
	{
		//ft_printf("You have pressed right arrow.\n");
		max->map->p.orientation += max->map->p.turnspeed;
		if (max->map->p.orientation >= MAXDEGREE)
			max->map->p.orientation -= MAXDEGREE;
	}
	// if (mlx_is_key_down(max->mlx, MLX_KEY_M))
	// {
	// 	if (max->mmode < -32)
	// 		max->mmode = 1;
	// 	if (max->mmode > 32)
	// 		max->mmode = 0;
	// }
	//ft_printf("test0\n");
	if (max->difficulty == MEDIUM)
	{
		if (!(max->frame % TICK))
			ft_revisit_map(max->map);
	}
	else if (max->difficulty == HARD)
	{
		if (!(max->frame % 2))
			ft_revisit_map(max->map);
	}
	ft_init_orays(max);
	ft_draw_map(max);
	ft_draw_minimap(max);
	ft_draw_screen3d(max);
}