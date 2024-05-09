/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu_13.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:39:15 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 11:54:51 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_menu_helper_7_1(t_max *max)
{
	if (max->menu.current_button[NEWRANDOM] == RSPLAY)
	{
		ft_snprintf(max->map.file, 4095, "RANDOM");
		ft_initrandommapvalues(&max->menu.rm);
		if (ft_process_random(max))
		{
			printf("gamestart loop starting...\n");
			ft_newgame(max);
		}
		else
			ft_dprintf(2, "Invalid map\n");
	}
	else if (max->menu.current_button[NEWRANDOM] == RSADVANCED)
	{
		max->menu.current_buttongroup = NEWRANDOMADVANCED;
	}
}

int	ft_menu_helper_8_1(t_max *max)
{
	int	r;

	r = 1;
	if (max->menu.current_button[NEWRANDOMADVANCED] == RWIDTH)
		max->menu.random_state[RWIDTH] ^= 1;
	else if (max->menu.current_button[NEWRANDOMADVANCED] == RHEIGHT)
		max->menu.random_state[RHEIGHT] ^= 1;
	else if (max->menu
		.current_button[NEWRANDOMADVANCED] == RRATIODE)
		max->menu.random_state[RRATIODE] ^= 1;
	else if (max->menu
		.current_button[NEWRANDOMADVANCED] == RRATIOLO)
		max->menu.random_state[RRATIOLO] ^= 1;
	else if (max->menu
		.current_button[NEWRANDOMADVANCED] == RRATIOTI)
		max->menu.random_state[RRATIOTI] ^= 1;
	else if (max->menu
		.current_button[NEWRANDOMADVANCED] == RRATIOXI)
		max->menu.random_state[RRATIOXI] ^= 1;
	else if (max->menu
		.current_button[NEWRANDOMADVANCED] == RNOROOMS)
		max->menu.random_state[RNOROOMS] ^= 1;
	else
		r = 0;
	return (r);
}

int	ft_menu_helper_8_2(t_max *max)
{
	int	r;

	r = 1;
	if (max->menu.current_button[NEWRANDOMADVANCED] == RDOORS)
		max->menu.random_state[RDOORS] ^= 1;
	else if (max->menu
		.current_button[NEWRANDOMADVANCED] == RDEADENDS)
		max->menu.random_state[RDEADENDS] ^= 1;
	else if (max->menu
		.current_button[NEWRANDOMADVANCED] == RRANDOMIZE)
		ft_initrandommapvalues(&max->menu.rm);
	else if (max->menu.current_button[NEWRANDOMADVANCED] == RPLAY)
	{
		ft_snprintf(max->map.file, 4095, "RANDOM");
		if (ft_process_random(max))
		{
			printf("gamestart loop starting...\n");
			ft_newgame(max);
		}
		else
			ft_dprintf(2, "Invalid map\n");
	}
	else
		r = 0;
	return (r);
}

int	ft_menu_helper_16(t_max *max)
{
	int	r;

	r = 1;
	if (max->menu.current_buttongroup == NEWRANDOM)
		ft_menu_helper_7_1(max);
	else if (max->menu.current_buttongroup == NEWRANDOMADVANCED)
	{
		if (ft_menu_helper_8_1(max))
		{
		}
		else if (max->menu.current_button[NEWRANDOMADVANCED] == ROROOMS)
			max->menu.random_state[ROROOMS] ^= 1;
		else if (ft_menu_helper_8_2(max))
		{
		}
	}
	else
		r = 0;
	return (r);
}
