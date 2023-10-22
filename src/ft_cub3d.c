/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 13:40:49 by okraus            #+#    #+#             */
/*   Updated: 2023/10/22 13:46:47 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int	main(int ac, char *av[])
{
	if (ac == 1)
	{
		//bonus (real game)
		ft_printf("Fun stuff happens here, one day.\n");
	}
	else if (ac == 2)
	{
		//mandatory (open specific map)
		ft_printf("Should open map: %s\n", av[1]);
	}
	else
	{
		// error
		ft_dprintf(2, "Incorrect number of parameters\n");
	}
	return (0);
}