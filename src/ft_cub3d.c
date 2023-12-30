/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 13:40:49 by okraus            #+#    #+#             */
/*   Updated: 2023/12/30 16:13:11 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	ft_cub3d(char *file)
{
	t_map		map;
	t_max		max;

	max.map = &map;
	max.mlx = NULL;
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