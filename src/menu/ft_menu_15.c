/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu_15.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:39:26 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 12:03:25 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_menu_helper_4_1(t_max *max)
{
	max->game_type = CAMPAIGN;
	max->level = 1;
	max->gamems = 0;
	ft_sprintf(max->campaignmap,
		"./campaign/map%i.cub", max->level);
	ft_snprintf(max->map.file, 4095, max->campaignmap);
	if (ft_process_file(max))
	{
		printf("gamestart loop starting...\n");
		ft_newgame(max);
	}
	else
		ft_dprintf(2, "Invalid map\n");
}

void	ft_menu_helper_4_2(t_max *max)
{
	max->game_type = TIMETRIAL;
	max->level = 1;
	max->gamems = 0;
	max->timetriallimitms = 120000;
	ft_inittimetrialmap(&max->menu.rm, max->level);
	ft_snprintf(max->map.file, 4095, "RANDOM");
	if (ft_process_random(max))
	{
		printf("gamestart loop starting...\n");
		ft_newgame(max);
	}
	else
		ft_dprintf(2, "Invalid map\n");
}

void	ft_menu_helper_6_1(t_max *max)
{
	if (max->menu.lf_state)
	{
		max->menu.lf_state = 0;
		max->menu.current_button[NEWMAP] = MSPLAY;
	}
	else
		max->menu.lf_state = 1;
}

void	ft_menu_helper_6_2(t_max *max)
{
	ft_snprintf(max->map.file, 4095, "%s%s", max->menu
		.custommap.dir, max->menu.custommap.text[max->menu
		.custommap.highlight].text);
	if (ft_process_file(max))
	{
		printf("gamestart loop starting...\n");
		ft_newgame(max);
	}
	else
	{
		max->menu.current_button[NEWMAP] = CUSTOM;
		max->menu.lf_state = 1;
		ft_dprintf(2, "Invalid map %s\n", max->map.file);
	}
}

int	ft_menu_helper_15(t_max *max)
{
	int	r;

	r = 1;
	if (max->menu.current_buttongroup == NEWSELECTION)
	{
		if (max->menu.current_button[NEWSELECTION] == CAMPAIGN)
			ft_menu_helper_4_1(max);
		else if (max->menu.current_button[NEWSELECTION] == TIMETRIAL)
			ft_menu_helper_4_2(max);
		else if (max->menu.current_button[NEWSELECTION] == ONEMAP)
		{
			max->game_type = ONEMAP;
			max->menu.current_buttongroup = NEWLEVEL;
		}
	}
	else if (max->menu.current_buttongroup == NEWMAP)
	{
		if (max->menu.current_button[NEWMAP] == CUSTOM)
			ft_menu_helper_6_1(max);
		else if (max->menu.current_button[NEWMAP] == MSPLAY)
			ft_menu_helper_6_2(max);
	}
	else
		r = 0;
	return (r);
}
