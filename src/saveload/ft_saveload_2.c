/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_saveload_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:57:59 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 17:58:44 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

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
