/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu_7.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:05:58 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 11:31:36 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

int	ft_selectbutton_helper_2(t_max *max)
{
	int	r;

	r = 1;
	if (max->menu.current_buttongroup == MAINBUTTONS)
		ft_selectnewbutton(max,
			&max->menu.mainbuttons[max->menu.current_button[MAINBUTTONS]]);
	else if (max->menu.current_buttongroup == NEWWRITING)
		ft_selectbutton_helper(max);
	else if (max->menu.current_buttongroup == NEWDIFFICULTY)
		ft_selectnewbutton(max, &max->menu
			.gamedifficultybuttons[max->menu.current_button[NEWDIFFICULTY]]);
	else if (max->menu.current_buttongroup == NEWSELECTION)
		ft_selectnewbutton(max, &max->menu
			.gametypebuttons[max->menu.current_button[NEWSELECTION]]);
	else if (max->menu.current_buttongroup == NEWLEVEL)
		ft_selectnewbutton(max, &max->menu
			.maptypebuttons[max->menu.current_button[NEWLEVEL]]);
	else
		r = 0;
	return (r);
}

int	ft_selectbutton_helper_4(t_max *max)
{
	int	r;

	r = 1;
	if (max->menu.current_buttongroup == NEWMAP)
	{
		if (max->menu.lf_state)
		{
			ft_choose_in_listfield(max, &max->menu.custommap);
			return (r);
		}
		ft_selectnewbutton(max, &max->menu
			.mapselectionbuttons[max->menu.current_button[NEWMAP]]);
	}
	else if (max->menu.current_buttongroup == NEWRANDOM)
	{
		ft_selectnewbutton(max, &max->menu
			.randomselectionbuttons[max->menu.current_button[NEWRANDOM]]);
	}
	else
		r = 0;
	return (r);
}

int	ft_selectbutton_helper_3_1(t_max *max)
{
	int	r;

	r = 1;
	if (max->menu.random_state[RWIDTH])
		ft_choose_in_button(max, &max->menu.randomadvancedbuttons[RWIDTH]);
	else if (max->menu.random_state[RHEIGHT])
		ft_choose_in_button(max, &max->menu.randomadvancedbuttons[RHEIGHT]);
	else if (max->menu.random_state[RRATIODE])
		ft_choose_in_button(max, &max->menu
			.randomadvancedbuttons[RRATIODE]);
	else if (max->menu.random_state[RRATIOLO])
		ft_choose_in_button(max, &max->menu
			.randomadvancedbuttons[RRATIOLO]);
	else if (max->menu.random_state[RRATIOTI])
		ft_choose_in_button(max, &max->menu
			.randomadvancedbuttons[RRATIOTI]);
	else if (max->menu.random_state[RRATIOXI])
		ft_choose_in_button(max, &max->menu
			.randomadvancedbuttons[RRATIOXI]);
	else
		r = 0;
	return (r);
}

int	ft_selectbutton_helper_3(t_max *max)
{
	int	r;

	r = 1;
	if (ft_selectbutton_helper_3_1(max))
	{
	}
	else if (max->menu.random_state[RNOROOMS])
		ft_choose_in_button(max, &max->menu
			.randomadvancedbuttons[RNOROOMS]);
	else if (max->menu.random_state[ROROOMS])
		ft_choose_in_button(max, &max->menu
			.randomadvancedbuttons[ROROOMS]);
	else if (max->menu.random_state[RDOORS])
		ft_choose_in_button(max, &max->menu
			.randomadvancedbuttons[RDOORS]);
	else if (max->menu.random_state[RDEADENDS])
		ft_choose_in_button(max, &max->menu
			.randomadvancedbuttons[RDEADENDS]);
	else
		r = 0;
	return (r);
}

void	ft_selectbutton(t_max *max)
{
	if (ft_selectbutton_helper_2(max))
	{
	}
	else if (ft_selectbutton_helper_4(max))
	{
	}
	else if (max->menu.current_buttongroup == NEWRANDOMADVANCED)
	{
		if (ft_selectbutton_helper_3(max))
			return ;
		ft_selectnewbutton(max, &max->menu.randomadvancedbuttons[max->menu
			.current_button[NEWRANDOMADVANCED]]);
	}
	else if (ft_selectbutton_helper_5(max))
	{
	}
	else if (max->menu.current_buttongroup == HALLOFFAMEGROUP)
	{
		ft_selectnewbutton(max, &max->menu
			.halloffamebuttons[max->menu.current_button[HALLOFFAME]]);
	}
}
