/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_overlay.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:11:48 by okraus            #+#    #+#             */
/*   Updated: 2024/04/12 15:40:36 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	ft_init_overlay(t_max *max)
{
	t_text	text;

	text.font = max->t.font;
	text.image = max->i.overlay;
	text.c = 0XFFFFFFFF;
	text.cb = 0x7F;
	text.sx = 10;
	text.sy = 10;
	text.x = 0;
	text.y = 0;
	text.height = 30;
	text.highlight = -1;
	max->overlay.basicinfo = text;
	max->overlay.basicinfo.text = max->overlay.basicinfo.str;
	text.sy = 50;
	max->overlay.rayinfo = text;
	max->overlay.rayinfo.text = max->overlay.rayinfo.str;
}

void	ft_clear_overlay(t_max *max)
{
	ft_bzero(max->i.overlay->pixels, max->i.overlay->width * max->i.overlay->height * 4);
}