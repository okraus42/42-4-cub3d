/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:31:12 by okraus            #+#    #+#             */
/*   Updated: 2024/04/26 13:10:13 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"


void	ft_interact_door2(t_max *max, unsigned short mp)
{
	if (max->map.doors[mp])
	{
		printf("doors found\n");
		max->map.doors[mp] ^= 0x80;
		// if (max->map.doors[mp] & 0x80)
		// {
		// 	printf("doors closed, opening...\n");
		// 	max->map.doors[mp] &= 0xFFFFFF7F;
		// }
		// else
		// {
		// 	printf("doors opened, closing...\n");
		// 	max->map.doors[mp] |= 0x80;
		// }
	}
}

void	ft_interact_door(t_max *max)
{
	unsigned short	mp;

	mp = (max->map.p.y >> 16) * max->map.w + (max->map.p.x >> 16);
	ft_interact_door2(max, mp + 1);
	ft_interact_door2(max, mp - 1);
	ft_interact_door2(max, mp + max->map.w);
	ft_interact_door2(max, mp - max->map.w);
}


void	ft_check_doors(t_max *max)
{
	int	d;
	int	c;

	d = 0;
	while (++d & 0xFFFF)
	{
		if (max->map.doors[d])
		{
			c = max->map.doors[d] & 0x7F;
			if (max->map.doors[d] & 0x80)
			{
				++c;
				c += max->framems >> 4;
				if (c > 0x7F)
					c = 0x7F;
			}
			else
			{
				--c;
				c -= max->framems >> 4;
				if (c < 0)
					c = 0;
			}
			max->map.doors[d] &= 0xFFFFFF80;
			max->map.doors[d] |= c;
		}
	}
}
// {
// 	int			r;
// 	t_sprite	*door;
	
// 		// printf("%i\n", i);
// 	door = &max->map.sprites[i];

// 	door->spx_left = max->map.sprites[i].x_left - (int)max->map.p.x;
// 	door->spy_left = max->map.sprites[i].y_left - (int)max->map.p.y;
// 	door->spx_right = max->map.sprites[i].x_right - (int)max->map.p.x;
// 	door->spy_right = max->map.sprites[i].y_right - (int)max->map.p.y;
// 	door->direction_left = atan2(door->spx_left, -door->spy_left) * (MAXDEGREE / 2 / M_PI);
// 	door->direction_right = atan2(door->spx_right, -door->spy_right) * (MAXDEGREE / 2 / M_PI);
// 	//printf("%f\n", atan2(-spx, spy));
// 	if (door->direction_left > MAXDEGREE)
// 		door->direction_left -= MAXDEGREE;
// 	else if (door->direction_left < 0)
// 		door->direction_left += MAXDEGREE;
// 	if (door->direction_right > MAXDEGREE)
// 		door->direction_right -= MAXDEGREE;
// 	else if (door->direction_right < 0)
// 		door->direction_right += MAXDEGREE;
// 	door->distance_left = sqrt((double)door->spx_left * (double)door->spx_left + (double)door->spy_left * (double)door->spy_left);
// 	if (!door->distance_left)
// 		door->distance_left = 1.;
// 	door->distance_right = sqrt((double)door->spx_right * (double)door->spx_right + (double)door->spy_right * (double)door->spy_right);
// 	if (!door->distance_right)
// 		door->distance_right = 1.;
// 	// door->relativedirection_left = max->map.p.orientation - door->direction_left;
// 	// if (door->relativedirection_left < 0 - MAXDEGREE / 2)
// 	// 	door->relativedirection_left += MAXDEGREE;
// 	// if (door->relativedirection_left > MAXDEGREE / 2)
// 	// 	door->relativedirection_left -= MAXDEGREE;
// 	// door->relativedirection_right = max->map.p.orientation - door->direction_right;
// 	// if (door->relativedirection_right < 0 - MAXDEGREE / 2)
// 	// 	door->relativedirection_right += MAXDEGREE;
// 	// if (door->relativedirection_right > MAXDEGREE / 2)
// 	// 	door->relativedirection_right -= MAXDEGREE;
// 	// door->sda = fullangle * door->relativedirection / MAXDEGREE;
// 	r = 0;
// 	door->xstart = 0;
// 	door->xmiddle = 0;
// 	door->xend = 0;
// 	while (r < RAYS)
// 	{
// 		if (max->map.p.oray[r].ra > door->direction_left && !door->xstart)
// 			door->xstart = r * SCREENWIDTH / RAYS;
// 		if (max->map.p.oray[r].ra > door->direction && !door->xmiddle)
// 			door->xmiddle = r * SCREENWIDTH / RAYS;
// 		if (max->map.p.oray[r].ra > door->direction_right && !door->xend)
// 			door->xend = r * SCREENWIDTH / RAYS;
// 		++r;
// 	}
// }