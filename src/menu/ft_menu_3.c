/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:05:20 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 11:16:59 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_draw_menu_2(t_max *max)
{
	t_dm	dm;

	dm.w = max->menu.background->width;
	dm.h = max->menu.background->height;
	dm.y = 0;
	while (dm.y < dm.h)
	{
		dm.x = 0;
		while (dm.x < dm.w)
		{
			dm.a = (dm.y * dm.w * 4) + (dm.x * 4);
			if (dm.x < dm.w && dm.y < dm.h)
			{
				dm.c = (max->menu.background->pixels[dm.a]) << 24
					| (max->menu.background->pixels[dm.a + 1]) << 16
					| (max->menu.background->pixels[dm.a + 2]) << 8 | 0xFF;
			}
			else
				dm.c = 0xFF00FFFF;
			mlx_put_pixel(max->i.menuscreen, dm.x, dm.y, dm.c);
			++dm.x;
		}
		++dm.y;
	}
}

void	ft_draw_menu_3(t_max *max)
{
	if (max->game_in_progress)
		ft_draw_button(&max->menu.mainbuttons[RESUME], ACTIVE);
	else
		ft_draw_button(&max->menu.mainbuttons[RESUME], INACTIVE);
	ft_draw_button(&max->menu.mainbuttons[NEWGAME], ACTIVE);
	if (max->game_in_progress)
		ft_draw_button(&max->menu.mainbuttons[SAVEGAME], ACTIVE);
	else
		ft_draw_button(&max->menu.mainbuttons[SAVEGAME], INACTIVE);
	if (max->menu.loads.files[0])
		ft_draw_button(&max->menu.mainbuttons[LOADGAME], ACTIVE);
	else
		ft_draw_button(&max->menu.mainbuttons[LOADGAME], INACTIVE);
	ft_draw_button(&max->menu.mainbuttons[SETTINGS], INACTIVE);
	ft_draw_button(&max->menu.mainbuttons[HALLOFFAME], ACTIVE);
	ft_draw_button(&max->menu.mainbuttons[QUITGAME], ACTIVE);
}

void	ft_draw_menu_4(t_max *max)
{
	if (max->menu.current_buttongroup == NEWWRITING)
	{
		if (max->menu.newwriting == NAME)
			ft_draw_button(&max->menu.newwritingbuttons[NAME], ACTIVATED);
		else
			ft_draw_button(&max->menu.newwritingbuttons[NAME], ACTIVE);
		if (max->menu.newwriting == COALITION)
			ft_draw_button(&max->menu.newwritingbuttons[COALITION], ACTIVATED);
		else
			ft_draw_button(&max->menu.newwritingbuttons[COALITION], ACTIVE);
		if (max->menu.newwriting == CAMPUS)
			ft_draw_button(&max->menu.newwritingbuttons[CAMPUS], ACTIVATED);
		else
			ft_draw_button(&max->menu.newwritingbuttons[CAMPUS], ACTIVE);
		ft_draw_button(&max->menu.newwritingbuttons[NWCONFIRM], ACTIVE);
	}
}

void	ft_draw_menu_5(t_max *max)
{
	if (max->menu.current_buttongroup == NEWWRITING)
	{
		if (max->menu.newwriting == NAME)
			ft_draw_textfield(&max->menu.newwritingfields[NAME], ACTIVATED);
		else
			ft_draw_textfield(&max->menu.newwritingfields[NAME], ACTIVE);
		if (max->menu.newwriting == COALITION)
			ft_draw_textfield(&max->menu.newwritingfields[COALITION],
				ACTIVATED);
		else
			ft_draw_textfield(&max->menu.newwritingfields[COALITION], ACTIVE);
		if (max->menu.newwriting == CAMPUS)
			ft_draw_textfield(&max->menu.newwritingfields[CAMPUS], ACTIVATED);
		else
			ft_draw_textfield(&max->menu.newwritingfields[CAMPUS], ACTIVE);
	}
}

void	ft_draw_menu(t_max *max)
{
	ft_draw_menu_2(max);
	ft_draw_menu_3(max);
	ft_draw_menu_4(max);
	ft_draw_menu_5(max);
	ft_draw_menu_6(max);
	ft_draw_menu_7(max);
	ft_draw_menu_8(max);
	if (max->menu.current_buttongroup == SAVEGROUP)
		ft_draw_listfield(&max->menu.saves, ACTIVE);
	if (max->menu.current_buttongroup == LOADGROUP)
	{
		ft_draw_button(&max->menu.loadgamebuttons[CHOOSELOAD], ACTIVE);
		ft_draw_button(&max->menu.loadgamebuttons[DELETE], ACTIVE);
		ft_draw_button(&max->menu.loadgamebuttons[LOAD], ACTIVE);
	}
	if (max->menu.current_buttongroup == LOADGROUP)
		ft_draw_listfield(&max->menu.loads, ACTIVE);
	if (max->menu.current_buttongroup == HALLOFFAMEGROUP)
		ft_draw_button(&max->menu.halloffamebuttons[HOFBACK], ACTIVE);
}
