/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu_11.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:39:01 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 11:49:13 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_draw_newmaplistfields(t_max *max)
{
	if (max->menu.lf_state)
		ft_draw_listfield(&max->menu.custommap, ACTIVATED);
	else
		ft_draw_listfield(&max->menu.custommap, SELECTED);
}

void	ft_draw_newrandombuttons(t_max *max)
{
	if (max->menu.current_button[NEWRANDOM] == RSPLAY)
	{
		ft_draw_button(&max->menu.randomselectionbuttons[RSPLAY], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOM] == RSADVANCED)
	{
		ft_draw_button(&max->menu.randomselectionbuttons[RSADVANCED], SELECTED);
	}
}

void	ft_updatenewrandomadvancedbuttons(t_max	*max)
{
	t_button	*but;

	but = &max->menu.randomadvancedbuttons[RWIDTH];
	ft_snprintf(but->text.str, 19, "%s: %i", but->str, but->val->value);
	but = &max->menu.randomadvancedbuttons[RHEIGHT];
	ft_snprintf(but->text.str, 19, "%s: %i", but->str, but->val->value);
	but = &max->menu.randomadvancedbuttons[RRATIODE];
	ft_snprintf(but->text.str, 19, "%s: %i", but->str, but->val->value);
	but = &max->menu.randomadvancedbuttons[RRATIOLO];
	ft_snprintf(but->text.str, 19, "%s: %i", but->str, but->val->value);
	but = &max->menu.randomadvancedbuttons[RRATIOTI];
	ft_snprintf(but->text.str, 19, "%s: %i", but->str, but->val->value);
	but = &max->menu.randomadvancedbuttons[RRATIOXI];
	ft_snprintf(but->text.str, 19, "%s: %i", but->str, but->val->value);
	but = &max->menu.randomadvancedbuttons[RNOROOMS];
	ft_snprintf(but->text.str, 19, "%s: %i", but->str, but->val->value);
	but = &max->menu.randomadvancedbuttons[ROROOMS];
	ft_snprintf(but->text.str, 19, "%s: %i", but->str, but->val->value);
	but = &max->menu.randomadvancedbuttons[RDOORS];
	ft_snprintf(but->text.str, 19, "%s: %i", but->str, but->val->value);
	but = &max->menu.randomadvancedbuttons[RDEADENDS];
	ft_snprintf(but->text.str, 19, "%s: %i", but->str, but->val->value);
}

int	ft_draw_newrandomadvancedbuttons_2(t_max *max)
{
	int	r;

	r = 1;
	if (max->menu.current_button[NEWRANDOMADVANCED] == RWIDTH)
	{
		if (max->menu.random_state[RWIDTH])
			ft_draw_button(&max->menu.randomadvancedbuttons[RWIDTH], ACTIVATED);
		else
			ft_draw_button(&max->menu.randomadvancedbuttons[RWIDTH], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOMADVANCED] == RHEIGHT)
	{
		if (max->menu.random_state[RHEIGHT])
		{
			ft_draw_button(&max->menu
				.randomadvancedbuttons[RHEIGHT], ACTIVATED);
		}
		else
			ft_draw_button(&max->menu.randomadvancedbuttons[RHEIGHT], SELECTED);
	}
	else
		r = 0;
	return (r);
}

void	ft_draw_savebuttons(t_max *max)
{
	if (max->menu.current_button[SAVEGROUP] == CHOOSESAVE)
	{
		if (max->menu.lf_state)
			ft_draw_button(&max->menu.savegamebuttons[CHOOSESAVE], ACTIVATED);
		else
			ft_draw_button(&max->menu.savegamebuttons[CHOOSESAVE], SELECTED);
	}
	else if (max->menu.current_button[SAVEGROUP] == DELETE)
	{
		ft_draw_button(&max->menu.savegamebuttons[DELETE], SELECTED);
	}
	else if (max->menu.current_button[SAVEGROUP] == SAVE)
	{
		ft_draw_button(&max->menu.savegamebuttons[SAVE], SELECTED);
	}
}
