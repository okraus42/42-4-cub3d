/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:08:20 by okraus            #+#    #+#             */
/*   Updated: 2024/05/02 15:36:26 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_process_keylocks(t_max *max)
{
	max->kb.caps_lock = max->key.caps_lock;
}

// ft process modifiers? 

void	ft_process_input(t_max *max)
{
	int	c;

	max->kb.character = 0;
	if (max->keys[MLX_KEY_LEFT_SHIFT] | max->keys[MLX_KEY_RIGHT_SHIFT])
		max->kb.shift = 1;
	else
		max->kb.shift = 0;
	//ditto ctrl alt
	c = ' ';
	while (c <= 126 && !(max->kb.character))
	{
		if (max->keys[c])
		{
			max->kb.character = c;
			if (ft_isupper(c))
			{
				if (max->kb.shift)
					max->kb.character = c;
				else
					max->kb.character = 32 | c;
				if (max->kb.caps_lock)
					max->kb.character ^= 32;
			}
			else if (max->kb.shift)
			{
				if (c == MLX_KEY_APOSTROPHE)
					max->kb.character = '"';
				else if (c == MLX_KEY_COMMA)
					max->kb.character = '<';
				else if (c == MLX_KEY_MINUS)
					max->kb.character = '_';
				else if (c == MLX_KEY_PERIOD)
					max->kb.character = '>';
				else if (c == MLX_KEY_SLASH)
					max->kb.character = '?';
				else if (c == MLX_KEY_0)
					max->kb.character = ')';
				else if (c == MLX_KEY_1)
					max->kb.character = '!';
				else if (c == MLX_KEY_2)
					max->kb.character = '@';
				else if (c == MLX_KEY_3)
					max->kb.character = '#';
				else if (c == MLX_KEY_4)
					max->kb.character = '$';
				else if (c == MLX_KEY_5)
					max->kb.character = '%';
				else if (c == MLX_KEY_6)
					max->kb.character = '^';
				else if (c == MLX_KEY_7)
					max->kb.character = '&';
				else if (c == MLX_KEY_8)
					max->kb.character = '*';
				else if (c == MLX_KEY_9)
					max->kb.character = '(';
				else if (c == MLX_KEY_SEMICOLON)
					max->kb.character = ':';
				else if (c == MLX_KEY_EQUAL)
					max->kb.character = '+';
				else if (c == MLX_KEY_LEFT_BRACKET)
					max->kb.character = '{';
				else if (c == MLX_KEY_BACKSLASH)
					max->kb.character = '|';
				else if (c == MLX_KEY_RIGHT_BRACKET)
					max->kb.character = '}';
				else if (c == MLX_KEY_GRAVE_ACCENT)
					max->kb.character = '~';
			}
			max->keys[c] = 0;
		}
		++c;
	}
	if (max->keys[ISO_KEY_BACKSLASH] && !(max->kb.character))
	{
		if (max->kb.shift)
			max->kb.character = '|';
		else
			max->kb.character = '\\';
		max->keys[ISO_KEY_BACKSLASH] = 0;
	}
	c = 320;
	while (c <= 329 && !(max->kb.character) && !(max->kb.character))
	{
		if (max->keys[c])
		{
			max->kb.character = c - 320 + '0';
			max->keys[c] = 0;
		}
		++c;
	}
	if (max->keys[MLX_KEY_KP_DECIMAL] && !(max->kb.character))
	{
		max->kb.character = '.';
		max->keys[MLX_KEY_KP_DECIMAL] = 0;
	}
	if (max->keys[MLX_KEY_KP_DIVIDE] && !(max->kb.character))
	{
		max->kb.character = '/';
		max->keys[MLX_KEY_KP_DIVIDE] = 0;
	}
	if (max->keys[MLX_KEY_KP_MULTIPLY] && !(max->kb.character))
	{
		max->kb.character = '*';
		max->keys[MLX_KEY_KP_MULTIPLY] = 0;
	}
	if (max->keys[MLX_KEY_KP_SUBTRACT] && !(max->kb.character))
	{
		max->kb.character = '-';
		max->keys[MLX_KEY_KP_SUBTRACT] = 0;
	}
	if (max->keys[MLX_KEY_KP_ADD] && !(max->kb.character))
	{
		max->kb.character = '+';
		max->keys[MLX_KEY_KP_ADD] = 0;
	}
	if (max->keys[MLX_KEY_KP_EQUAL] && !(max->kb.character))
	{
		max->kb.character = '=';
		max->keys[MLX_KEY_KP_EQUAL] = 0;
	}
}

void	ft_menuhook(t_max *max)
{
	
	// if (mlx_is_key_down(max->mlx, MLX_KEY_ESCAPE))
	// {
	// 	max->game_mode = GAMEPLAY;
	// 	max->menuscreen->enabled = 0;
	// 	// ft_printf("You have quit the game by pressing ESC.\n");
	// 	// mlx_close_window(max->mlx);
	// }
	ft_process_keylocks(max);
	if (max->menu.current_buttongroup == NEWWRITING)
		ft_process_input(max);
	ft_menu(max);
}

void	ft_gameplayhook(t_max *max)
{
	ft_process_keylocks(max);
	ft_gameplay(max);
}

void	ft_gamestarthook(t_max *max)
{
	ft_gamestart(max);
}

void	ft_gamewonhook(t_max *max)
{
	ft_gamewon(max);
}

void	ft_gamelosthook(t_max *max)
{
	ft_gamelost(max);
}

void	ft_halloffamehook(t_max *max)
{
	ft_halloffame(max);
}

void	ft_hook(void *param)
{
	t_max	*max;

	max = param;
	max->newms = ft_get_time_in_ms();
	max->framems = (unsigned int)(max->newms - max->oldms);
	max->oldms = max->newms;
	//ft_clear_overlay(max);
	if (max->game_mode == MENU)
		ft_menuhook(max);
	else if (max->game_mode == GAMESTART)
		ft_gamestarthook(max);
	else if (max->game_mode == GAMEWON)
		ft_gamewonhook(max);
	else if (max->game_mode == GAMELOST)
		ft_gamelosthook(max);
	else if (max->game_mode == GAMEPLAY)
		ft_gameplayhook(max);
	else if (max->game_mode == HOFLOOP)
		ft_halloffamehook(max);
}