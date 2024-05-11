/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buttons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 10:42:26 by okraus            #+#    #+#             */
/*   Updated: 2024/05/11 16:18:52 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_initbuttons_global_helper(t_max *max)
{
	ft_initbutton_resume(max);
	ft_initbutton_newgame(max);
	ft_initbutton_savegame(max);
	ft_initbutton_loadgame(max);
	ft_initbutton_settings(max);
	ft_initbutton_halloffame(max);
	ft_initbutton_quitgame(max);
	ft_initbutton_name(max);
	ft_initbutton_coalition(max);
	ft_initbutton_campus(max);
	ft_initbutton_nwconfirm(max);
	ft_initbutton_easylvl(max);
	ft_initbutton_mediumlvl(max);
	ft_initbutton_hardlvl(max);
	ft_initbutton_campaign(max);
	ft_initbutton_timetrial(max);
	ft_initbutton_onemap(max);
	ft_initbutton_custom(max);
	ft_initbutton_random(max);
	ft_initbutton_chooselvl(max);
	ft_initbutton_msplay(max);
	ft_initbutton_rsplay(max);
	ft_initbutton_rsadvanced(max);
}

void	ft_initbuttons(t_max *max)
{
	t_button	button;
	t_text		text;

	button = ft_initbutton_helper(max);
	text = ft_inittext_helper(max);
	ft_initbuttons_global_helper(max);
	button.button = max->menu.buttonplus;
	button.text.height = 40;
	ft_initbutton_rwidth(max, button);
	ft_initbutton_rheight(max, button);
	ft_initbutton_rratiode(max, button);
	ft_initbutton_rratiolo(max, button);
	ft_initbutton_rratioti(max, button);
	ft_initbutton_rratioxi(max, button);
	ft_initbutton_rnorooms(max, button);
	ft_initbutton_rorooms(max, button);
	ft_initbutton_rdoors(max, button);
	ft_initbutton_rdeadends(max, button);
	button.text.height = 60;
	button.button = max->menu.button;
	ft_initbuttons_global_helper_2(max, button);
}

void	ft_choose_in_button_2(t_max *max, int *i)
{
	if (max->keys[MLX_KEY_KP_ADD] || max->keys[MLX_KEY_RIGHT])
	{
		++(*i);
		max->keys[MLX_KEY_KP_ADD] = 0;
		max->keys[MLX_KEY_UP] = 0;
		max->keys[MLX_KEY_RIGHT] = 0;
	}
	if (max->keys[MLX_KEY_KP_SUBTRACT] || max->keys[MLX_KEY_LEFT])
	{
		--(*i);
		max->keys[MLX_KEY_KP_SUBTRACT] = 0;
		max->keys[MLX_KEY_DOWN] = 0;
		max->keys[MLX_KEY_LEFT] = 0;
	}
	if (max->keys[MLX_KEY_KP_MULTIPLY])
	{
		(*i) *= 2;
		max->keys[MLX_KEY_KP_MULTIPLY] = 0;
	}
	if (max->keys[MLX_KEY_KP_DIVIDE])
	{
		(*i) /= 2;
		max->keys[MLX_KEY_KP_DIVIDE] = 0;
	}
}

void	ft_choose_in_button(t_max *max, t_button *button)
{
	int	i;

	i = button->val->value;
	ft_choose_in_button_2(max, &i);
	if (max->keys[MLX_KEY_UP])
	{
		i += 10;
		max->keys[MLX_KEY_UP] = 0;
	}
	if (max->keys[MLX_KEY_DOWN])
	{
		i -= 10;
		max->keys[MLX_KEY_DOWN] = 0;
	}
	if (i < button->val->min)
		i = button->val->min;
	if (i > button->val->max)
		i = button->val->max;
	button->val->value = i;
	ft_snprintf(button->text.str, 19, "%s: %i", button->str,
		button->val->value);
}
