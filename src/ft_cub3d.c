/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 13:40:49 by okraus            #+#    #+#             */
/*   Updated: 2023/12/31 17:21:02 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	ft_init_math(t_math *math)
{
	int		i;
	double	step;

	step = 6.28318531 / 65536;
	i = 0;
	while (i < 65536)
	{
		math->sin[i] = 65536 * sin(step * i);
		math->cos[i] = 65536 * cos(step * i);
	++i;
	}
	ft_printf("SIN 0 %i 90 %i  180 %i 270 %i\n", math->sin[NORTH], math->sin[EAST], math->sin[SOUTH], math->sin[WEST]);
	ft_printf("COS 0 %i 90 %i  180 %i 270 %i\n", math->cos[NORTH], math->cos[EAST], math->cos[SOUTH], math->cos[WEST]);
}

void	ft_cub3d(char *file)
{
	t_map		map;
	t_max		max;
	t_math		math;

	max.math = &math;
	ft_init_math(max.math);
	max.map = &map;
	max.mlx = NULL;
	max.frame = 0;
	max.oldms = ft_get_time_in_ms();
	max.newms = 0;
	if (file)
	{
		map.file = file;
		if (ft_process_file(&max))
		{
			ft_amaze_standard(&max);
		}
		else
		{
			ft_dprintf(2, "Aborting: invalid map.\n");
		}
	}
	else
	{
		ft_printf("Fun stuff happens here, one day.\n");
	}
}

int	main(int ac, char *av[])
{
	if (ac == 1)
	{
		//bonus (real game)
		ft_printf("Fun stuff happens here, one day.\n");
		ft_cub3d(av[1]);
	}
	else if (ac == 2)
	{
		//mandatory (open specific map)
		ft_printf("Should open map: %s\n", av[1]);
		ft_cub3d(av[1]);
	}
	else
	{
		// error
		ft_dprintf(2, "Incorrect number of parameters\n");
	}
	return (0);
}