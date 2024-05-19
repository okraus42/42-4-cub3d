/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu_10.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:38:42 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 11:43:53 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

int	ft_draw_newrandomadvancedbuttons_3(t_max *max)
{
	int	r;

	r = 1;
	if (max->menu.current_button[NEWRANDOMADVANCED] == RRATIODE)
	{
		if (max->menu.random_state[RRATIODE])
			ft_draw_button(&max->menu
				.randomadvancedbuttons[RRATIODE], ACTIVATED);
		else
			ft_draw_button(&max->menu
				.randomadvancedbuttons[RRATIODE], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOMADVANCED] == RRATIOLO)
	{
		if (max->menu.random_state[RRATIOLO])
			ft_draw_button(&max->menu
				.randomadvancedbuttons[RRATIOLO], ACTIVATED);
		else
			ft_draw_button(&max->menu
				.randomadvancedbuttons[RRATIOLO], SELECTED);
	}
	else
		r = 0;
	return (r);
}

int	ft_draw_newrandomadvancedbuttons_4(t_max *max)
{
	int	r;

	r = 1;
	if (max->menu.current_button[NEWRANDOMADVANCED] == RRATIOTI)
	{
		if (max->menu.random_state[RRATIOTI])
			ft_draw_button(&max->menu
				.randomadvancedbuttons[RRATIOTI], ACTIVATED);
		else
			ft_draw_button(&max->menu
				.randomadvancedbuttons[RRATIOTI], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOMADVANCED] == RRATIOXI)
	{
		if (max->menu.random_state[RRATIOXI])
			ft_draw_button(&max->menu
				.randomadvancedbuttons[RRATIOXI], ACTIVATED);
		else
			ft_draw_button(&max->menu
				.randomadvancedbuttons[RRATIOXI], SELECTED);
	}
	else
		r = 0;
	return (r);
}

int	ft_draw_newrandomadvancedbuttons_5(t_max *max)
{
	int	r;

	r = 1;
	if (max->menu.current_button[NEWRANDOMADVANCED] == RNOROOMS)
	{
		if (max->menu.random_state[RNOROOMS])
			ft_draw_button(&max->menu
				.randomadvancedbuttons[RNOROOMS], ACTIVATED);
		else
			ft_draw_button(&max->menu
				.randomadvancedbuttons[RNOROOMS], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOMADVANCED] == ROROOMS)
	{
		if (max->menu.random_state[ROROOMS])
			ft_draw_button(&max->menu
				.randomadvancedbuttons[ROROOMS], ACTIVATED);
		else
			ft_draw_button(&max->menu
				.randomadvancedbuttons[ROROOMS], SELECTED);
	}
	else
		r = 0;
	return (r);
}

int	ft_draw_newrandomadvancedbuttons_6(t_max *max)
{
	int	r;

	r = 1;
	if (max->menu.current_button[NEWRANDOMADVANCED] == RDOORS)
	{
		if (max->menu.random_state[RDOORS])
			ft_draw_button(&max->menu.randomadvancedbuttons[RDOORS], ACTIVATED);
		else
			ft_draw_button(&max->menu.randomadvancedbuttons[RDOORS], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOMADVANCED] == RDEADENDS)
	{
		if (max->menu.random_state[RDEADENDS])
			ft_draw_button(&max->menu
				.randomadvancedbuttons[RDEADENDS], ACTIVATED);
		else
			ft_draw_button(&max->menu
				.randomadvancedbuttons[RDEADENDS], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOMADVANCED] == RRANDOMIZE)
		ft_draw_button(&max->menu.randomadvancedbuttons[RRANDOMIZE], SELECTED);
	else
		r = 0;
	return (r);
}

void	ft_draw_newrandomadvancedbuttons(t_max *max)
{
	ft_updatenewrandomadvancedbuttons(max);
	if (ft_draw_newrandomadvancedbuttons_2(max))
	{
	}
	else if (ft_draw_newrandomadvancedbuttons_3(max))
	{
	}
	else if (ft_draw_newrandomadvancedbuttons_4(max))
	{
	}
	else if (ft_draw_newrandomadvancedbuttons_5(max))
	{
	}
	else if (ft_draw_newrandomadvancedbuttons_6(max))
	{
	}
	else if (max->menu.current_button[NEWRANDOMADVANCED] == RPLAY)
	{
		ft_draw_button(&max->menu.randomadvancedbuttons[RPLAY], SELECTED);
	}
}
