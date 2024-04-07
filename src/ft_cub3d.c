/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 13:40:49 by okraus            #+#    #+#             */
/*   Updated: 2024/04/07 15:39:29 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

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
	//double	step;

	//step = 6.28318531 / MAXDEGREE;
	//step = 0.0003834951969714103;
	i = 0;
	ft_fill_clin(math->clin);
	ft_fill_clog(math->clog);
	while (i < MAXDEGREE)
	{
		// not sure if everything needs .9999, but it helps the tan functions
		math->sin[i] = 65536.9999 * sin(i * M_PI * 2 / MAXDEGREE);
		math->cos[i] = 65536.9999 * cos(i * M_PI * 2 / MAXDEGREE);
		math->atan[i] = 65536.9999 / tan(i * M_PI * 2 / MAXDEGREE);
		math->natan[i] = -65536.9999 / tan(i * M_PI * 2 / MAXDEGREE);
		math->ntan[i] = (-65536.9999 * (tan(i * M_PI * 2 / MAXDEGREE)));
		math->tan[i] = (65536.9999 * (tan(i * M_PI * 2 / MAXDEGREE)));
		if (ABS(tan(i * M_PI * 2 / MAXDEGREE)) > 60000)
			ft_printf("WARNING %i \n", i);
	++i;
	}
	ft_printf("SIN 0 %i 90 %i  180 %i 270 %i\n", math->sin[NORTH], math->sin[EAST], math->sin[SOUTH], math->sin[WEST]);
	ft_printf("COS 0 %i 90 %i  180 %i 270 %i\n", math->cos[NORTH], math->cos[EAST], math->cos[SOUTH], math->cos[WEST]);
	ft_printf("ATAN 0 %i 90 %i  180 %i 270 %i\n", math->atan[NORTH], math->atan[EAST], math->atan[SOUTH], math->atan[WEST]);
	ft_printf("NTAN 0 %Li 90 %Li  180 %Li 270 %Li\n", math->ntan[NORTH], math->ntan[EAST], math->ntan[SOUTH], math->ntan[WEST]);
	ft_printf("NTAN 0 %Li 90 %Li  180 %Li 270 %Li\n", math->ntan[NORTH + 1], math->ntan[EAST + 1], math->ntan[SOUTH + 1], math->ntan[WEST + 1]);
	ft_printf("NTAN 0 %Li 90 %Li  180 %Li 270 %Li\n", math->ntan[NORTH + 2], math->ntan[EAST - 2], math->ntan[SOUTH - 2], math->ntan[WEST - 2]);
}

//maybe allocate only max
void	ft_cub3d(char *file)
{
	t_map		*map;
	t_max		*max;
	t_math		*math;

	max = NULL;
	max = ft_calloc(sizeof(t_max), 1);
	if (!max)
		ft_exit(max, 11);
	map = ft_calloc(sizeof(t_map), 1);
	if (!map)
		ft_exit(max, 11);
	math = ft_calloc(sizeof(t_math), 1);
	if (!math)
		ft_exit(max, 11);
	max->math = math;
	ft_init_math(max->math);
	max->map = map;
	max->mlx = NULL;
	max->keys[MLX_KEY_KP_1] = 0;
	max->frame = 0;
	max->ray = 0;
	max->mmode = 0;
	max->game_mode = MENU;
	max->oldms = ft_get_time_in_ms();
	max->newms = 0;
	if (file)
	{
		map->file = file;
		if (ft_process_file(max))
		{
			ft_amaze_standard(max);
		}
		else
		{
			ft_dprintf(2, "Aborting: invalid map.\n");
		}
	}
	else
	{
		ft_amaze_bonus(max);;
	}
	free(max);
	free(math);
	free(map);
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