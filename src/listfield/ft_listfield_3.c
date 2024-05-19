/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listfield_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:57:51 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 18:58:34 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_initlistfields_init_loads(t_max *max, t_text text)
{
	int	i;

	i = 0;
	while (max->menu.loads.files && max->menu.loads.files[i] && i < 10)
	{
		max->menu.loads.text[i] = text;
		max->menu.loads.text[i].text = max->menu.loads.files[i];
		max->menu.loads.text[i].sx = max->menu.loads.x + 120;
		max->menu.loads.text[i].sy = max->menu.loads.y + 120 + (40 * i);
		++i;
	}
	while (i < 10)
	{
		max->menu.loads.text[i] = text;
		max->menu.loads.text[i].text = " - - - ";
		max->menu.loads.text[i].sx = max->menu.loads.x + 120;
		max->menu.loads.text[i].sy = max->menu.loads.y + 120 + (40 * i);
		++i;
	}
}

void	ft_initlistfields(t_max *max)
{
	t_listfield	listfield;
	t_text		text;

	ft_initlistfields_init_text(max, &text);
	ft_initlistfields_init_lf(max, &listfield);
	ft_initlistfields_init_cm(max, text);
	ft_initlistfields_init_saves1(max, listfield);
	ft_initlistfields_init_saves2(max, text);
	max->menu.loads = listfield;
	max->menu.loads.state = ACTIVE;
	max->menu.loads.x = 600;
	max->menu.loads.y = 160;
	ft_sprintf(max->menu.loads.dir, "./saves/");
	max->menu.loads.files = ft_readdir(max->menu.loads.dir, ".ft");
	max->menu.loads.totalfiles = ft_splitlen(max->menu.loads.files);
	ft_initlistfields_init_loads(max, text);
}

void	ft_bigreinitlistfield_cm(t_max *max)
{
	int	i;

	max->menu.custommap.text[max->menu.custommap.highlight].cb = 0;
	max->menu.custommap.text[max->menu.custommap.highlight].c = 0x00FF00FF;
	if (max->menu.custommap.files)
		ft_free_split(&max->menu.custommap.files);
	max->menu.custommap.files = ft_readdir(max->menu.custommap.dir, ".cub");
	max->menu.custommap.highlight = 0;
	max->menu.custommap.topfile = 0;
	max->menu.custommap.totalfiles = ft_splitlen(max->menu.custommap.files);
	i = 0;
	while (max->menu.custommap.files && max->menu.custommap.files[i] && i < 10)
	{
		max->menu.custommap.text[i].text = max->menu.custommap.files[i];
		++i;
	}
	while (i < 10)
	{
		max->menu.custommap.text[i].text = " - - - ";
		++i;
	}
}

void	ft_bigreinitlistfield_saves(t_max *max)
{
	int	i;

	max->menu.saves.highlight = 0;
	max->menu.saves.topfile = 0;
	max->menu.saves.totalfiles = ft_splitlen(max->menu.saves.files);
	i = 0;
	while (max->menu.saves.files && max->menu.saves.files[i] && i < 10)
	{
		max->menu.saves.text[i].text = max->menu.saves.files[i];
		++i;
	}
	while (i < 10)
	{
		max->menu.saves.text[i].text = " - - - ";
		++i;
	}
}

void	ft_bigreinitlistfield_loads(t_max *max)
{
	int	i;

	if (max->menu.loads.files)
		ft_free_split(&max->menu.loads.files);
	max->menu.loads.text[max->menu.loads.highlight].cb = 0;
	max->menu.loads.text[max->menu.loads.highlight].c = 0x00FF00FF;
	max->menu.loads.files = ft_readdir(max->menu.loads.dir, ".ft");
	max->menu.loads.highlight = 0;
	max->menu.loads.topfile = 0;
	max->menu.loads.totalfiles = ft_splitlen(max->menu.loads.files);
	i = 0;
	while (max->menu.loads.files && max->menu.loads.files[i] && i < 10)
	{
		max->menu.loads.text[i].text = max->menu.loads.files[i];
		++i;
	}
	while (i < 10)
	{
		max->menu.loads.text[i].text = " - - - ";
		++i;
	}
}
