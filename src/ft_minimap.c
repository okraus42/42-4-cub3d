/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:53:41 by okraus            #+#    #+#             */
/*   Updated: 2024/02/13 15:59:05 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

static int	ft_is_inside(t_map *map, long long rad2, int y, int x)
{
	long long	cx;
	long long	cy;

	cx = x - (int)map->p.x;
	cy = y - (int)map->p.y;
	if (cx * cx + cy * cy <= rad2)
	{
		return (1);
	}
	return (0);
}


void	ft_draw_minimap(t_max *max)
{
	int	y;
	int	x;
	int	ny;
	int	nx;
	int	s; //scaling factor
	int	r;

	s = 8;
	y = 0;
	// while (y < MINIHEIGHT)
	// {
	// 	x = 0;
	// 	while (x < MINIWIDTH)
	// 	{
	// 		ny = y + ((int)max->map->p.y * s / 256) - MINIHEIGHT / 2;
	// 		nx = x + ((int)max->map->p.x * s / 256) - MINIWIDTH / 2;
	// 		if (ny > 0 && nx > 0 && ny < max->map->h * s && nx < max->map->w * s)
	// 		{
	// 			if (ft_is_inside(max->map, 4096, (ny << 8) / s, (nx << 8) / s))
	// 			{
	// 				//ft_printf("y= %i, x= %i\n", y, x);
	// 				mlx_put_pixel(max->maximap, x, y, max->map->c.rgba & TMASK);	//player has ceiling colour
	// 			}
	// 			// else if (ft_is_inside2(max, 1024, (y << 8) / s, (x << 8) / s))
	// 			// {
	// 			// 	mlx_put_pixel(max->map, x, y, 0x00ff00ff & TMASK);	//green circle for the direction visualisation
	// 			// }
	// 			else if (max->map->m[(ny / s) * max->map->w + (nx / s)] & WALL)
	// 			{
	// 				if (max->map->m[(ny / s) * max->map->w + (nx / s)] & VISITED)
	// 					mlx_put_pixel(max->maximap, x, y, 0x000000ff & TMASK); //Visited wall shine white
	// 				else
	// 					mlx_put_pixel(max->maximap, x, y, UNDISCOVERDWALL & TMASK); //black for unvisited area
	// 			}
	// 			else if (max->map->m[(ny / s) * max->map->w + (nx / s)] & FLOOR)
	// 			{
	// 				if (max->map->m[(ny / s) * max->map->w + (nx / s)] & VISITED)
	// 					mlx_put_pixel(max->maximap, x, y, max->map->f.rgba & TMASK); //floor is the proper colour
	// 				else
	// 					mlx_put_pixel(max->maximap, x, y, UNDISCOVERDFLOOR & TMASK); //black for unvisited area
	// 			}
	// 			else
	// 				mlx_put_pixel(max->maximap, x, y, 0x404040FF & TMASK);
	// 		}
	// 		else
	// 			mlx_put_pixel(max->maximap, x, y, 0x808080FF & TMASK);
	// 		++x;
	// 	}
	// 	++y;
	// }
	while (y < MINIHEIGHT)
	{
		x = 0;
		while (x < MINIWIDTH)
		{
			ny = y + ((int)max->map->p.y * s / 256) - MINIHEIGHT / 2;
			nx = x + ((int)max->map->p.x * s / 256) - MINIWIDTH / 2;
			if (ny > 0 && nx > 0 && ny < max->map->h * s && nx < max->map->w * s)
			{
				if (ft_is_inside(max->map, 4096, (ny << 8) / s, (nx << 8) / s))
				{
					//ft_printf("y= %i, x= %i\n", y, x);
					mlx_put_pixel(max->minimap, x, y, max->map->c.rgba & TMASK);	//player has ceiling colour
				}
				// else if (ft_is_inside2(max, 1024, (y << 8) / s, (x << 8) / s))
				// {
				// 	mlx_put_pixel(max->map, x, y, 0x00ff00ff & TMASK);	//green circle for the direction visualisation
				// }
				else if (max->map->m[(ny / s) * max->map->w + (nx / s)] & WALL)
				{
					//mlx_put_pixel(max->minimap, x, y, 0x000000FF & TMASK); //walls are black for now
					if (max->map->m[(ny / s) * max->map->w + (nx / s)] & VISITED)
						mlx_put_pixel(max->minimap, x, y, 0x000000ff & TMASK); //Visited wall shine white
					else
						mlx_put_pixel(max->minimap, x, y, UNDISCOVERDWALL & TMASK); //black for unvisited area
				}
				else if (max->map->m[(ny / s) * max->map->w + (nx / s)] & FLOOR)
				{
					// mlx_put_pixel(max->minimap, x, y, max->map->f.rgba & TMASK); //floor is the proper colour
					if (max->map->m[(ny / s) * max->map->w + (nx / s)] & VISITED)
						mlx_put_pixel(max->minimap, x, y, max->map->f.rgba & TMASK); //floor is the proper colour
					else
						mlx_put_pixel(max->minimap, x, y, UNDISCOVERDFLOOR & TMASK); //black for unvisited area
				}
				else
					mlx_put_pixel(max->minimap, x, y, 0x404040FF & TMASK);
			}
			else
				mlx_put_pixel(max->minimap, x, y, 0x808080FF & TMASK);
			++x;
		}
		++y;
	}

	r = 0;
	
	while (r < RAYS)
	{
		max->map->p.miniray[r].x[0] = MINIWIDTH / 2;
		max->map->p.miniray[r].y[0] = MINIHEIGHT / 2;
		max->map->p.miniray[r].x[1] = MINIWIDTH / 2 + ((((max->map->p.oray[r].rx - max->map->p.oray[r].xs)) * s) >> 16);
		max->map->p.miniray[r].y[1] = MINIHEIGHT / 2 + ((((max->map->p.oray[r].ry - max->map->p.oray[r].ys)) * s) >> 16);
		max->map->p.miniray[r].maxheight = MINIHEIGHT;
		max->map->p.miniray[r].maxwidth = MINIWIDTH;
		max->map->p.miniray[r].c[0] = max->map->p.oray[r].c[0];
		max->map->p.miniray[r].c[1] = max->map->p.oray[r].c[1];
		ft_place_line(max->minimap, max->map->p.miniray[r]);
		++r;
	}
	r = 0;
	
	// while (r < RAYS)
	// {	
	// 	max->map->p.miniray[r].x[0] = MINIWIDTH / 2;
	// 	max->map->p.miniray[r].y[0] = MINIHEIGHT / 2;
	// 	max->map->p.miniray[r].ra = max->map->p.orientation - max->map->p.fov2 + r * max->map->p.fov * 65536LL / (RAYS - 1) / 360;
	// 	max->map->p.miniray[r].x[1] = MINIWIDTH / 2 - (((max->math->sin[max->map->p.miniray[r].ra]) * s) / 8192);
	// 	max->map->p.miniray[r].y[1] = MINIHEIGHT / 2 - (((max->math->cos[max->map->p.miniray[r].ra]) * s) / 8192);
	// 	max->map->p.miniray[r].c[0] = 0xffff00ff;
	// 	max->map->p.miniray[r].c[1] = max->map->f.rgba;
	// 	max->map->p.miniray[r].maxheight = MINIHEIGHT;
	// 	max->map->p.miniray[r].maxwidth = MINIWIDTH;
	// 	ft_place_line(max->minimap, max->map->p.miniray[r]);
	// 	++r;
	// }
	// max->map->p.xl[0] = MINIWIDTH / 2;
	// max->map->p.yl[0] = MINIHEIGHT / 2;
	// max->map->p.xl[1] = MINIWIDTH / 2 - max->math->sin[(unsigned short)(max->map->p.orientation + max->map->p.fov2)] * s / 16384;
	// max->map->p.yl[1] = MINIHEIGHT / 2 - max->math->cos[(unsigned short)(max->map->p.orientation + max->map->p.fov2)] * s / 16384;
	// max->map->p.xr[0] = MINIWIDTH / 2;
	// max->map->p.yr[0] = MINIHEIGHT / 2;
	// max->map->p.xr[1] = MINIWIDTH / 2  - max->math->sin[(unsigned short)(max->map->p.orientation - max->map->p.fov2)] * s / 16384;
	// max->map->p.yr[1] = MINIHEIGHT / 2 - max->math->cos[(unsigned short)(max->map->p.orientation - max->map->p.fov2)] * s / 16384;
	// ft_place_line(max->minimap, max->map->p.xx, max->map->p.yy, 0xff0000ff);
	// ft_place_line(max->minimap, max->map->p.xl, max->map->p.yl, 0xffff00ff);
	// ft_place_line(max->minimap, max->map->p.xr, max->map->p.yr, 0xffff00ff);
	// max->map->p.xd[0] = MINIWIDTH / 2;;
	// max->map->p.yd[0] = MINIHEIGHT / 2;
	// max->map->p.xd[1] = max->map->p.xd[0] + max->map->p.dx * s / 16384;
	// max->map->p.yd[1] = max->map->p.yd[0] + max->map->p.dy * s / 16384;
	// ft_place_line(max->minimap, max->map->p.xd, max->map->p.yd, 0x0000ffff);
	// max->map->p.xc[0] = max->map->p.xd[1];
	// max->map->p.yc[0] = max->map->p.yd[1];
	// max->map->p.xc[1] = max->map->p.xc[0] + max->map->p.cx * s / 16384;
	// max->map->p.yc[1] = max->map->p.yc[0] + max->map->p.cy * s / 16384;
	// ft_place_line(max->minimap, max->map->p.xc, max->map->p.yc, 0xff00ffff);
	// max->map->p.xn[0] = max->map->p.xd[1];
	// max->map->p.yn[0] = max->map->p.yd[1];
	// max->map->p.xn[1] = max->map->p.xn[0] - max->map->p.cx * s / 16384;
	// max->map->p.yn[1] = max->map->p.yn[0] - max->map->p.cy * s / 16384;
	// ft_place_line(max->minimap, max->map->p.xn, max->map->p.yn, 0xffa0ffff);
}

