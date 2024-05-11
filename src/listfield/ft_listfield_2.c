/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listfield_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:53:50 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 18:54:50 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_initlistfields_init_text(t_max *max, t_text *text)
{
	text->font = max->font.asciitest;
	text->image = max->i.menuscreen;
	text->text = "";
	text->c = 0X00FF00FF;
	text->cb = 0xFF;
	text->sx = 0;
	text->sy = 0;
	text->x = 0;
	text->y = 0;
	text->height = 40;
	text->highlight = -1;
	text->i = 0;
	text->offset = 0;
}

void	ft_initlistfields_init_lf(t_max *max, t_listfield *listfield)
{
	listfield->listfield = max->menu.listfield;
	listfield->image = max->i.menuscreen;
	listfield->c = C_INACTIVE;
	listfield->x = 200;
	listfield->y = 0;
	listfield->w = 350;
	listfield->h = 150;
	listfield->highlight = 0;
	listfield->state = INACTIVE;
	listfield->topfile = 0;
	max->menu.custommap = *listfield;
	max->menu.custommap.state = ACTIVE;
	max->menu.custommap.x = 600;
	max->menu.custommap.y = 160;
	ft_sprintf(max->menu.custommap.dir, "./maps/");
	max->menu.custommap.files = ft_readdir(max->menu.custommap.dir, ".cub");
	max->menu.custommap.totalfiles = ft_splitlen(max->menu.custommap.files);
}

void	ft_initlistfields_init_cm(t_max *max, t_text text)
{
	int	i;

	i = 0;
	while (max->menu.custommap.files && max->menu.custommap.files[i] && i < 10)
	{
		max->menu.custommap.text[i] = text;
		max->menu.custommap.text[i].text = max->menu.custommap.files[i];
		max->menu.custommap.text[i].sx = max->menu.custommap.x + 120;
		max->menu.custommap.text[i].sy = max->menu.custommap.y + 120 + (40 * i);
		++i;
	}
	while (i < 10)
	{
		max->menu.custommap.text[i] = text;
		max->menu.custommap.text[i].text = " - - - ";
		max->menu.custommap.text[i].sx = max->menu.custommap.x + 120;
		max->menu.custommap.text[i].sy = max->menu.custommap.y + 120 + (40 * i);
		++i;
	}
}

void	ft_initlistfields_init_saves1(t_max *max, t_listfield listfield)
{
	max->menu.saves = listfield;
	max->menu.saves.state = ACTIVE;
	max->menu.saves.x = 600;
	max->menu.saves.y = 160;
	ft_sprintf(max->menu.saves.dir, "./saves/");
	max->menu.saves.files = ft_readdir(max->menu.saves.dir, ".ft");
	if (max->menu.saves.files && max->menu.saves.files[0]
		&& max->menu.saves.files[0][0] == 'f')
		ft_split_rm(&max->menu.saves.files, 0);
	if (max->menu.saves.files && max->menu.saves.files[0]
		&& max->menu.saves.files[0][0] == 'q')
		ft_split_rm(&max->menu.saves.files, 0);
	ft_split_add(&max->menu.saves.files, "NEW SAVE",
		ft_splitlen(max->menu.saves.files));
	max->menu.saves.totalfiles = ft_splitlen(max->menu.saves.files);
}

void	ft_initlistfields_init_saves2(t_max *max, t_text text)
{
	int	i;

	i = 0;
	while (max->menu.saves.files && max->menu.saves.files[i] && i < 10)
	{
		max->menu.saves.text[i] = text;
		max->menu.saves.text[i].text = max->menu.saves.files[i];
		max->menu.saves.text[i].sx = max->menu.saves.x + 120;
		max->menu.saves.text[i].sy = max->menu.saves.y + 120 + (40 * i);
		++i;
	}
	while (i < 10)
	{
		max->menu.saves.text[i] = text;
		max->menu.saves.text[i].text = " - - - ";
		max->menu.saves.text[i].sx = max->menu.saves.x + 120;
		max->menu.saves.text[i].sy = max->menu.saves.y + 120 + (40 * i);
		++i;
	}
}
