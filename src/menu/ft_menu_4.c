/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:05:31 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 11:16:57 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_selectnewbutton_4(t_max *max, t_button *button)
{
	if (max->keys[MLX_KEY_LEFT])
	{
		while (button->left)
		{
			button = button->left;
			if (button->state & (ACTIVE | ACTIVATED))
			{
				max->menu.current_button[button->group] = button->id;
				break ;
			}
		}
		max->keys[MLX_KEY_LEFT] = 0;
	}
}

void	ft_selectnewbutton_3(t_max *max, t_button *button)
{
	if (max->keys[MLX_KEY_DOWN])
	{
		while (button->down)
		{
			button = button->down;
			if (button->state & (ACTIVE | ACTIVATED))
			{
				max->menu.current_button[button->group] = button->id;
				break ;
			}
		}
		max->keys[MLX_KEY_DOWN] = 0;
	}
}

void	ft_selectnewbutton_2(t_max *max, t_button *button)
{
	if (max->keys[MLX_KEY_UP])
	{
		while (button->up)
		{
			button = button->up;
			if (button->state & (ACTIVE | ACTIVATED))
			{
				max->menu.current_button[button->group] = button->id;
				break ;
			}
		}
		max->keys[MLX_KEY_UP] = 0;
	}
}

void	ft_selectnewbutton(t_max *max, t_button *button)
{
	ft_selectnewbutton_2(max, button);
	ft_selectnewbutton_3(max, button);
	ft_selectnewbutton_4(max, button);
	if (max->keys[MLX_KEY_RIGHT])
	{
		while (button->right)
		{
			button = button->right;
			if (button->state & (ACTIVE | ACTIVATED))
			{
				max->menu.current_button[button->group] = button->id;
				break ;
			}
		}
		max->keys[MLX_KEY_RIGHT] = 0;
	}
}
