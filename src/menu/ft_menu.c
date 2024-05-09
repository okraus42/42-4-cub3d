/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:34:14 by okraus            #+#    #+#             */
/*   Updated: 2024/05/09 12:10:13 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_menu_helper_10(t_max *max)
{
	ft_snprintf(max->map.file, 4095, "%s%s", max->menu.loads
		.dir, max->menu.loads.text[max->menu.loads
		.highlight].text);
	if (ft_load(max, max->map.file))
	{
		ft_dprintf(2, "Unable to load the game, \
			make sure the safe file exists\n");
		max->menu.current_buttongroup = MAINBUTTONS;
	}
	else
	{
		max->menu.current_buttongroup = MAINBUTTONS;
		max->game_in_progress = 1;
		max->i.menuscreen->enabled = 0;
		max->i.textscreen->enabled = 0;
		max->game_mode = GAMEPLAY;
		max->i.overlay->enabled = 1;
		max->game_in_progress = 1;
		max->oldms = ft_get_time_in_ms();
	}
}

void	ft_menu_helper_11(t_max *max)
{
	if (max->menu.current_button[LOADGROUP] == CHOOSELOAD)
	{
		if (max->menu.lf_state)
		{
			max->menu.lf_state = 0;
			max->menu.current_button[LOADGROUP] = LOAD;
		}
		else
		{
			max->menu.lf_state = 1;
		}
	}
	else if (max->menu.current_button[LOADGROUP] == LOAD)
		ft_menu_helper_10(max);
	else if (max->menu.current_button[LOADGROUP] == DELETE)
		ft_dprintf(2, "Functionality not implemented\n");
}

void	ft_menu_helper_12(t_max *max)
{
	if (max->menu.current_button[MAINBUTTONS] == SAVEGAME)
	{
		if (max->menu.current_buttongroup == MAINBUTTONS)
		{
			max->menu.current_buttongroup = SAVEGROUP;
			ft_bigreinitlistfield(max);
			max->menu.lf_state = 1;
			max->menu.current_button[SAVEGROUP] = CHOOSESAVE;
		}
		else if (max->menu.current_buttongroup == SAVEGROUP)
			ft_menu_helper_9(max);
	}
	if (max->menu.current_button[MAINBUTTONS] == LOADGAME)
	{
		if (max->menu.current_buttongroup == MAINBUTTONS)
		{
			max->menu.current_buttongroup = LOADGROUP;
			ft_bigreinitlistfield(max);
			max->menu.lf_state = 1;
			max->menu.current_button[LOADGROUP] = CHOOSELOAD;
		}
		else if (max->menu.current_buttongroup == LOADGROUP)
			ft_menu_helper_11(max);
	}
}

void	ft_menu_helper_13(t_max *max)
{
	ft_menu_helper_12(max);
	if (max->menu.current_button[MAINBUTTONS] == HALLOFFAME)
	{
		if (!ft_readscore(max))
		{
			max->game_mode = HOFLOOP;
			max->i.textscreen->enabled = 1;
		}
		else
			ft_dprintf(2, "Error\nFailed to open halloffame.txt\n");
	}
	if (max->menu.current_button[MAINBUTTONS] == QUITGAME)
		mlx_close_window(max->mlx);
}

void	ft_menu(t_max *max)
{
	ft_menu_2(max);
	ft_menu_3(max);
	if (max->keys[MLX_KEY_ENTER])
	{
		max->keys[MLX_KEY_ENTER] = 0;
		if (max->menu.current_button[MAINBUTTONS] == RESUME)
			ft_resume(max);
		if (max->menu.current_button[MAINBUTTONS] == NEWGAME)
		{
			if (ft_menu_helper_14(max))
			{
			}
			else if (max->menu.current_buttongroup == NEWLEVEL)
				ft_menu_helper_5_1(max);
			else if (ft_menu_helper_15(max))
			{
			}
			else if (ft_menu_helper_16(max))
			{
			}
		}
		ft_menu_helper_13(max);
	}
}
