/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 13:40:49 by okraus            #+#    #+#             */
/*   Updated: 2024/05/07 14:07:34 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_cub3d_2(char *file, t_max *max)
{
	ft_snprintf(max->map.file, 4095, file);
	if (ft_process_file(max))
		ft_amaze_standard(max);
	else
		ft_dprintf(2, "Aborting: invalid map.\n");
}

void	ft_cub3d_init(t_max *max)
{
	max->mlx = NULL;
	max->keys[MLX_KEY_KP_1] = 0;
	max->frame = 0;
	max->ray = 0;
	max->mmode = 0;
	max->game_mode = MENU;
	max->score = 1000000;
	max->oldms = ft_get_time_in_ms();
	max->newms = 0;
}

void	ft_cub3d(char *file)
{
	t_max		*max;
	t_math		*math;

	max = NULL;
	max = ft_calloc(sizeof(t_max), 1);
	if (!max)
		ft_exit(max, 11);
	math = ft_calloc(sizeof(t_math), 1);
	if (!math)
		ft_exit(max, 11);
	max->math = math;
	ft_init_math(max->math);
	ft_cub3d_init(max);
	if (file)
		ft_cub3d_2(file, max);
	else
		ft_amaze_bonus(max);
	ft_free(max);
	free(math);
}

int	main(int ac, char *av[])
{
	if (ac == 1)
	{
		ft_printf("Fun stuff happens here, one day.\n");
		ft_cub3d(av[1]);
	}
	else if (ac == 2)
	{
		ft_printf("Should open map: %s\n", av[1]);
		ft_cub3d(av[1]);
	}
	else
	{
		ft_dprintf(2, "Incorrect number of parameters\n");
	}
	return (0);
}
