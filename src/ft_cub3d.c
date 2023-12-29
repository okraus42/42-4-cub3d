/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 13:40:49 by okraus            #+#    #+#             */
/*   Updated: 2023/12/29 13:14:29 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int	ft_process_file(char *file, unsigned int map[65536])
{
	//check file extension
	//count new lines
	//get max line size
	//get map width and height
	//fill map
	//check edges
	//check exit
}

void	ft_cub3d(char *file)
{
	unsigned int	map[65536];

	if (file)
	{
		if (ft_process_file(file, map))
		{
			
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