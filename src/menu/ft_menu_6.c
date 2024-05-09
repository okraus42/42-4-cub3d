/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu_6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:05:52 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 11:19:25 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_selectbutton_5(t_max *max)
{
	{
		max->menu.newwritingfields[NAME].text.text[max->menu
			.newwritingfields[NAME].text.highlight] = '\0';
		max->menu.newwritingfields[NAME].text.highlight = -1;
	}
	if (max->menu.newwritingfields[COALITION].text.highlight >= 0)
	{
		max->menu.newwritingfields[COALITION].text.text[max->menu
			.newwritingfields[COALITION].text.highlight] = '\0';
		max->menu.newwritingfields[COALITION].text.highlight = -1;
	}
	if (max->menu.newwritingfields[CAMPUS].text.highlight >= 0)
	{
		max->menu.newwritingfields[CAMPUS].text.text[max->menu
			.newwritingfields[CAMPUS].text.highlight] = '\0';
		max->menu.newwritingfields[CAMPUS].text.highlight = -1;
	}
	max->menu.newwriting = -1;
}

void	ft_selectbutton_4(t_max *max)
{
	ft_write_in_textfield(max, &max->menu.newwritingfields[CAMPUS]);
	max->menu.newwriting = CAMPUS;
	if (max->menu.newwritingfields[NAME].text.highlight >= 0)
	{
		max->menu.newwritingfields[NAME].text.text[max->menu
			.newwritingfields[NAME].text.highlight] = '\0';
		max->menu.newwritingfields[NAME].text.highlight = -1;
	}
	if (max->menu.newwritingfields[COALITION].text.highlight >= 0)
	{
		max->menu.newwritingfields[COALITION].text.text[max->menu
			.newwritingfields[COALITION].text.highlight] = '\0';
		max->menu.newwritingfields[COALITION].text.highlight = -1;
	}
}

void	ft_selectbutton_3(t_max *max)
{
	ft_write_in_textfield(max, &max->menu.newwritingfields[COALITION]);
	max->menu.newwriting = COALITION;
	if (max->menu.newwritingfields[NAME].text.highlight >= 0)
	{
		max->menu.newwritingfields[NAME].text.text[max->menu
			.newwritingfields[NAME].text.highlight] = '\0';
		max->menu.newwritingfields[NAME].text.highlight = -1;
	}
	if (max->menu.newwritingfields[CAMPUS].text.highlight >= 0)
	{
		max->menu.newwritingfields[CAMPUS].text.text[max->menu
			.newwritingfields[CAMPUS].text.highlight] = '\0';
		max->menu.newwritingfields[CAMPUS].text.highlight = -1;
	}
}

void	ft_selectbutton_2(t_max *max)
{
	ft_write_in_textfield(max, &max->menu.newwritingfields[NAME]);
	max->menu.newwriting = NAME;
	if (max->menu.newwritingfields[COALITION].text.highlight >= 0)
	{
		max->menu.newwritingfields[COALITION].text.text[max->menu
			.newwritingfields[COALITION].text.highlight] = '\0';
		max->menu.newwritingfields[COALITION].text.highlight = -1;
	}
	if (max->menu.newwritingfields[CAMPUS].text.highlight >= 0)
	{
		max->menu.newwritingfields[CAMPUS].text.text[max->menu
			.newwritingfields[CAMPUS].text.highlight] = '\0';
		max->menu.newwritingfields[CAMPUS].text.highlight = -1;
	}
}

void	ft_selectbutton_helper(t_max *max)
{
	ft_selectnewbutton(max,
		&max->menu.newwritingbuttons[max->menu.current_button[NEWWRITING]]);
	if (max->menu.current_button[NEWWRITING] == NAME)
		ft_selectbutton_2(max);
	else if (max->menu.current_button[NEWWRITING] == COALITION)
		ft_selectbutton_3(max);
	else if (max->menu.current_button[NEWWRITING] == CAMPUS)
		ft_selectbutton_4(max);
	else
		ft_selectbutton_5(max);
}
