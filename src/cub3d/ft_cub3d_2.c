/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:31:14 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/07 14:07:38 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

static void	ft_fill_clog(unsigned char clog[65536])
{
	int	i;
	int	a;
	int	b;

	i = 0;
	while (i < 65536)
	{
		a = (i >> 8) & 0xFF;
		b = i & 0xFF;
		clog[i] = sqrt(((a * a) + (b * b)) / 2);
		++i;
	}
}

static void	ft_fill_clin(unsigned char clin[65536])
{
	int	i;
	int	a;
	int	b;

	i = 0;
	while (i < 65536)
	{
		a = (i >> 8) & 0xFF;
		b = i & 0xFF;
		clin[i] = (a + b) / 2;
		++i;
	}
}

void	ft_init_math(t_math *math)
{
	int		i;

	i = 0;
	ft_fill_clin(math->clin);
	ft_fill_clog(math->clog);
	while (i < MAXDEGREE)
	{
		math->sin[i] = 65536.0 * sin(i * M_PI * 2 / MAXDEGREE);
		math->cos[i] = 65536.0 * cos(i * M_PI * 2 / MAXDEGREE);
		math->atan[i] = 65536.0 / tan(i * M_PI * 2 / MAXDEGREE);
		math->natan[i] = -65536.0 / tan(i * M_PI * 2 / MAXDEGREE);
		math->ntan[i] = (-65536.0 * (tan(i * M_PI * 2 / MAXDEGREE)));
		math->tan[i] = (65536.0 * (tan(i * M_PI * 2 / MAXDEGREE)));
		if (ABS(tan(i * M_PI * 2 / MAXDEGREE)) > 60000)
			ft_printf("WARNING %i \n", i);
		++i;
	}
}
