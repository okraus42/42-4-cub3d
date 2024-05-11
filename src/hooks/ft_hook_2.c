/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:03:18 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 18:04:11 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_process_keylocks(t_max *max)
{
	max->kb.caps_lock = max->key.caps_lock;
}

void	ft_process_input_shift_2(t_max *max, int c)
{
	if (c == MLX_KEY_5)
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

void	ft_process_input_shift(t_max *max, int c)
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
	else
		ft_process_input_shift_2(max, c);
}

void	ft_process_input_numpad_2(t_max *max)
{
	int	c;

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
}

void	ft_process_input_numpad(t_max *max)
{
	ft_process_input_numpad_2(max);
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
