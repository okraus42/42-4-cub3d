/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_saveload.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:32:52 by okraus            #+#    #+#             */
/*   Updated: 2024/04/12 15:35:24 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"


int	ft_savegame(t_max *max)
{
	int		fd;

	fd = open("./saves/fakequicksave.ft", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_dprintf(2, "Error\nFailed to open fakequicksave\n");
		return (1);
	}
	if (write(fd, &max->map.p, sizeof(max->map.p)) < 0)
	{
		ft_dprintf(2, "Error\nFailed to write fakequicksave\n");
		return (1);
	}
	close(fd);
	return (0);
}

int	ft_loadgame(t_max *max)
{
	int		fd;

	fd = open("./saves/fakequicksave.ft", O_RDONLY);
	if (fd < 0)
	{
		ft_dprintf(2, "Error\nFailed to open fakequicksave\n");
		return (1);
	}
	if (read(fd, &max->map.p, sizeof(max->map.p)) < 0)
	{
		ft_dprintf(2, "Error\nFailed to read fakequicksave\n");
		return (1);
	}
	close(fd);
	return (0);
}


int	ft_quicksave(t_max *max)
{
	int		fd;

	fd = open("./saves/quicksave.ft", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_dprintf(2, "Error\nFailed to open quicksave\n");
		return (1);
	}
	if (write(fd, max, sizeof(*max)) < 0)
	{
		ft_dprintf(2, "Error\nFailed to write quicksave\n");
		return (1);
	}
	close(fd);
	return (0);
}

void	ft_reinitmax(t_max *newmax, t_max *oldmax)
{
	newmax->math = oldmax->math;
	newmax->mlx = oldmax->mlx;
	newmax->i = oldmax->i;
	newmax->t = oldmax->t;
	newmax->menu = oldmax->menu;
	newmax->kb = oldmax->kb;
	newmax->gamestart = oldmax->gamestart;
	newmax->gamewon = oldmax->gamewon;
	newmax->gamelost = oldmax->gamelost;
	newmax->font = oldmax->font;
	newmax->key = oldmax->key;
}

int	ft_quickload(t_max *max)
{
	int		fd;
	t_max	current_max;

	fd = open("./saves/quicksave.ft", O_RDONLY);
	if (fd < 0)
	{
		ft_dprintf(2, "Error\nFailed to open quicksave\n");
		return (1);
	}
	current_max = *max;
	if (read(fd, max, sizeof(*max)) < 0)
	{
		ft_dprintf(2, "Error\nFailed to read quicksave\n");
		return (1);
	}
	ft_clear_keys(max);
	ft_reinitmax(max, &current_max);
	max->oldms = ft_get_time_in_ms();
	close(fd);
	return (0);
}


