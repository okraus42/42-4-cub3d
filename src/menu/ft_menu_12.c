/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu_12.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:39:08 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 11:50:16 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_draw_savelistfields(t_max *max)
{
	if (max->menu.lf_state)
		ft_draw_listfield(&max->menu.saves, ACTIVATED);
	else
		ft_draw_listfield(&max->menu.saves, SELECTED);
}

void	ft_draw_loadbuttons(t_max *max)
{
	if (max->menu.current_button[LOADGROUP] == CHOOSELOAD)
	{
		if (max->menu.lf_state)
			ft_draw_button(&max->menu.loadgamebuttons[CHOOSELOAD], ACTIVATED);
		else
			ft_draw_button(&max->menu.loadgamebuttons[CHOOSELOAD], SELECTED);
	}
	else if (max->menu.current_button[LOADGROUP] == DELETE)
	{
		ft_draw_button(&max->menu.loadgamebuttons[DELETE], SELECTED);
	}
	else if (max->menu.current_button[LOADGROUP] == LOAD)
	{
		ft_draw_button(&max->menu.loadgamebuttons[LOAD], SELECTED);
	}
}

void	ft_draw_loadlistfields(t_max *max)
{
	if (max->menu.lf_state)
		ft_draw_listfield(&max->menu.loads, ACTIVATED);
	else
		ft_draw_listfield(&max->menu.loads, SELECTED);
}

void	ft_draw_halloffamebuttons(t_max *max)
{
	if (max->menu.current_button[HALLOFFAMEGROUP] == HOFBACK)
	{
		ft_draw_button(&max->menu.halloffamebuttons[HOFBACK], SELECTED);
	}
}
