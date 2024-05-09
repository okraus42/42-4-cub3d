/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu_14.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:39:19 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 12:01:01 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

int	ft_menu_helper_1(t_max *max)
{
	int	r;

	r = 1;
	if (max->menu.current_button[NEWWRITING] == COALITION)
	{
		if (max->menu.newwriting == COALITION)
		{
			max->menu.newwriting = CAMPUS;
			max->menu.newwritingfields[COALITION].text
				.text[max->menu.newwritingfields[COALITION]
				.text.highlight] = '\0';
			max->menu.newwritingfields[COALITION]
				.text.highlight = -1;
			max->menu.current_button[NEWWRITING] = CAMPUS;
		}
		else
			max->menu.newwriting = COALITION;
	}
	else
		r = 0;
	return (r);
}

int	ft_menu_helper(t_max *max)
{
	int	r;

	r = 1;
	if (max->menu.current_button[NEWWRITING] == NAME)
	{
		if (max->menu.newwriting == NAME)
		{
			max->menu.newwriting = COALITION;
			max->menu.newwritingfields[NAME].text.text[max->menu
				.newwritingfields[NAME].text.highlight] = '\0';
			max->menu.newwritingfields[NAME].text.highlight = -1;
			max->menu.current_button[NEWWRITING] = COALITION;
		}
		else
			max->menu.newwriting = NAME;
	}
	else if (ft_menu_helper_1(max))
	{
	}
	else
		r = 0;
	return (r);
}

int	ft_menu_helper_2(t_max *max)
{
	int	r;

	r = 1;
	if (max->menu.current_button[NEWWRITING] == CAMPUS)
	{
		if (max->menu.newwriting == CAMPUS)
		{
			max->menu.newwriting = -1;
			max->menu.newwritingfields[CAMPUS].text.text[max->menu
				.newwritingfields[CAMPUS].text.highlight] = '\0';
			max->menu.newwritingfields[CAMPUS].text.highlight = -1;
			max->menu.current_button[NEWWRITING] = NWCONFIRM;
		}
		else
			max->menu.newwriting = CAMPUS;
	}
	else
		r = 0;
	return (r);
}

void	ft_menu_helper_3(t_max *max)
{
	if (max->menu.current_button[NEWDIFFICULTY] == EASY)
	{
		max->difficulty = EASY;
		max->menu.current_buttongroup = NEWSELECTION;
	}
	else if (max->menu.current_button[NEWDIFFICULTY] == MEDIUM)
	{
		max->difficulty = MEDIUM;
		max->menu.current_buttongroup = NEWSELECTION;
	}
	else if (max->menu.current_button[NEWDIFFICULTY] == HARD)
	{
		max->difficulty = HARD;
		max->menu.current_buttongroup = NEWSELECTION;
	}
}

int	ft_menu_helper_14(t_max *max)
{
	int	r;

	r = 1;
	if (max->menu.current_buttongroup == MAINBUTTONS)
		max->menu.current_buttongroup = NEWWRITING;
	else if (max->menu.current_buttongroup == NEWWRITING)
	{
		if (ft_menu_helper(max))
		{
		}
		else if (ft_menu_helper_2(max))
		{
		}
		else if (max->menu.current_button[NEWWRITING] == NWCONFIRM)
		{
			max->menu.current_buttongroup = NEWDIFFICULTY;
			printf("%s\n%s\n%s\n", max->name,
				max->coalition, max->campus);
		}
	}
	else if (max->menu.current_buttongroup == NEWDIFFICULTY)
		ft_menu_helper_3(max);
	else
		r = 0;
	return (r);
}
