/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:31:12 by okraus            #+#    #+#             */
/*   Updated: 2024/05/10 15:44:32 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_interact_door2(t_max *max, unsigned short mp)
{
	if (max->map.doors[mp])
	{
		printf("doors found\n");
		max->map.doors[mp] ^= 0x80;
	}
}

void	ft_interact_door(t_max *max)
{
	unsigned short	mp;

	mp = (max->map.p.y >> 16) * max->map.w + (max->map.p.x >> 16);
	printf("oray.wall = %x\n", max->map.p.oray[RAYS / 2].wall);
	printf("oray.length = %Li\n", max->map.p.oray[RAYS / 2].length);
	printf("oray.mpos = %x\n", max->map.p.oray[RAYS / 2].mpos);
	if (max->map.p.oray[RAYS / 2].wall & DOOR && max->map.p.oray[RAYS / 2]
		.length < 0x20000)
		ft_interact_door2(max, max->map.p.oray[RAYS / 2].mpos);
	else
	{
		ft_interact_door2(max, mp);
		if (max->map.p.orientation >= 2048 && max->map.p.orientation < 6144)
			ft_interact_door2(max, mp + 1);
		if (max->map.p.orientation >= 10240 && max->map.p.orientation < 14336)
			ft_interact_door2(max, mp - 1);
		if (max->map.p.orientation >= 6144 && max->map.p.orientation < 10240)
			ft_interact_door2(max, mp + max->map.w);
		if (max->map.p.orientation >= 14336 || max->map.p.orientation < 2048)
			ft_interact_door2(max, mp - max->map.w);
	}
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
				c = (c > 0x7F) * 0x7F + (c <= 0x7F) * c;
			}
			else
			{
				--c;
				c -= max->framems >> 4;
				c = (c > 0) * c;
			}
			max->map.doors[d] &= 0xFFFFFF80;
			max->map.doors[d] |= c;
		}
	}
}
