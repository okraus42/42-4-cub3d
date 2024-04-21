/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mousehook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:58:09 by okraus            #+#    #+#             */
/*   Updated: 2024/04/21 15:21:14 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	ft_mousehook(void *param)
{
	t_max	*max;

	max = param;
	(void)max;
// 	void mlx_get_mouse_pos(mlx_t* mlx, int32_t* x, int32_t* y);

// /**
//  * Sets the mouse position.
//  * 
//  * @param[in] mlx The MLX instance handle. 
//  * @param[in] pos The position.
//  */
// void mlx_set_mouse_pos(mlx_t* mlx, int32_t x, int32_t y);
}

void	ft_cursorhook(void *param)
{
	t_max	*max;

	max = param;
	(void)max;
}