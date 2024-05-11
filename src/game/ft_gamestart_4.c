/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gamestart_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:31:43 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 14:33:38 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_gamewon_timetrial(t_max *max)
{
	++max->level;
	ft_inittimetrialmap(&max->menu.rm, max->level);
	ft_snprintf(max->map.file, 4095, "RANDOM");
	if (ft_process_random(max))
	{
		printf("gamestart loop starting...\n");
		max->game_mode = GAMESTART;
		max->menu.current_button[MAINBUTTONS] = RESUME;
		max->menu.current_buttongroup = MAINBUTTONS;
		max->game_in_progress = 0;
		max->i.menuscreen->enabled = 0;
		max->i.textscreen->enabled = 1;
	}
	else
		ft_dprintf(2, "Invalid map\n");
}
