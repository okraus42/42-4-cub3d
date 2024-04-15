/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_settings.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:50:50 by okraus            #+#    #+#             */
/*   Updated: 2024/04/15 11:37:25 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	ft_print_settings(t_max *max)
{
	ft_printf("%p\n", max->settings);
	ft_printf("fov %i | dof %i | tick %i\n",
		max->settings.fov, max->settings.dof, max->settings.tick);
	ft_printf("debugging %i | fisheyecorrection %i\n",
		max->settings.debugging, max->settings.fisheyecorrection);
}

void	ft_init_settings(t_max *max)
{
	t_settings	default_settings;

	default_settings.fov = 80;
	default_settings.debugging = 0;
	default_settings.fisheyecorrection = 1;
	default_settings.dof = 8;
	if (default_settings.dof > MAXDOF)
		default_settings.dof = MAXDOF;
	default_settings.maxdist = 65536LL * default_settings.dof;
	default_settings.tick = 8;
	max->settings = default_settings;
	ft_print_settings(max);
}