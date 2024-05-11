/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listfield.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:00:54 by okraus            #+#    #+#             */
/*   Updated: 2024/05/11 17:18:14 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

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

void	ft_bigreinitlistfield(t_max *max)
{
	ft_bigreinitlistfield_cm(max);
	if (max->menu.saves.files)
		ft_free_split(&max->menu.saves.files);
	max->menu.saves.text[max->menu.saves.highlight].cb = 0;
	max->menu.saves.text[max->menu.saves.highlight].c = 0x00FF00FF;
	max->menu.saves.files = ft_readdir(max->menu.saves.dir, ".ft");
	if (max->menu.saves.files && max->menu.saves.files[0]
		&& max->menu.saves.files[0][0] == 'f')
		ft_split_rm(&max->menu.saves.files, 0);
	if (max->menu.saves.files && max->menu.saves.files[0]
		&& max->menu.saves.files[0][0] == 'q')
		ft_split_rm(&max->menu.saves.files, 0);
	ft_split_add(&max->menu.saves.files, "NEW SAVE",
		ft_splitlen(max->menu.saves.files));
	ft_bigreinitlistfield_saves(max);
	ft_bigreinitlistfield_loads(max);
}

void	ft_reinitlistfield(t_listfield	*listfield)
{
	int	i;

	i = 0;
	while (listfield->files && listfield->files[i + listfield->topfile]
		&& i < 10)
	{
		listfield->text[i].text = listfield->files[i + listfield->topfile];
		++i;
	}
	while (i < 10)
	{
		listfield->text[i].text = " - - - ";
		++i;
	}
}

void	ft_draw_listfield_inner(t_listfield *lf, t_db dl)
{
	dl.i = 0;
	while (dl.i < dl.w)
	{
		dl.a = (dl.j * dl.w * 4) + (dl.i * 4);
		if (dl.i < dl.w && dl.j < dl.h)
			dl.c = (lf->listfield->pixels[dl.a]) << 24
				| (lf->listfield->pixels[dl.a + 1]) << 16
				| (lf->listfield->pixels[dl.a + 2]) << 8
				| (lf->listfield->pixels[dl.a + 3]);
		else
			dl.c = 0xFF00FFFF;
		if (dl.c & 0xFFFFFF00)
			mlx_put_pixel(lf->image, dl.i + lf->x, dl.j + lf->y, 0xFF);
		else if ((dl.c & 0xFF) == 0xFF)
			mlx_put_pixel(lf->image, dl.i + lf->x, dl.j + lf->y, dl.c);
		++dl.i;
	}
}

void	ft_draw_listfield(t_listfield *lf, int state)
{
	t_db	dl;

	lf->state = state;
	dl.w = lf->listfield->width;
	dl.h = lf->listfield->height;
	dl.j = 0;
	ft_reinitlistfield(lf);
	while (dl.j < dl.h)
	{
		ft_draw_listfield_inner(lf, dl);
		++dl.j;
	}
	lf->text[lf->highlight].c = 0xFF;
	lf->text[lf->highlight].cb = 0x00FF00FF;
	dl.i = 0;
	while (dl.i < 10)
	{
		ft_draw_text(&lf->text[dl.i], state);
		++dl.i;
	}
}

//topitemnumber
//total items number

void	ft_choose_in_listfield_keys(t_max *max, int *i)
{
	if (max->keys[MLX_KEY_UP])
	{
		--(*i);
		max->keys[MLX_KEY_UP] = 0;
	}
	if (max->keys[MLX_KEY_DOWN])
	{
		++(*i);
		max->keys[MLX_KEY_DOWN] = 0;
	}
}

void	ft_choose_in_listfield(t_max *max, t_listfield *listfield)
{
	int	i;

	i = listfield->highlight;
	listfield->text[i].cb = 0;
	listfield->text[i].c = 0x00FF00FF;
	ft_choose_in_listfield_keys(max, &i);
	if (i < 0)
	{
		i = 0;
		if (listfield->topfile > 0)
			--listfield->topfile;
	}
	if (i > 9)
	{
		i = 9;
		if (listfield->topfile < listfield->totalfiles - 10)
			++listfield->topfile;
	}
	if (i && i >= listfield->totalfiles - listfield->topfile)
		--i;
	listfield->highlight = i;
}
