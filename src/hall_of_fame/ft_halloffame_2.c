/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_halloffame_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:11:47 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 18:12:27 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

int	ft_writescore(t_max *max)
{
	int	fd;

	fd = open("./data/halloffame.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_dprintf(2, "Error\nFailed to open halloffame.txt\n");
		ft_dprintf(2, "%s\036%s\036%s\036%i\036%i\036%u\n", max->name,
			max->coalition, max->campus, max->level, max->score, max->gamems);
		return (1);
	}
	ft_dprintf(fd, "%s\036%s\036%s\036%i\036%i\036%u\n", max->name,
		max->coalition, max->campus, max->level, max->score, max->gamems);
	close(fd);
	return (0);
}

void	ft_copy_score_top(t_max *max, t_text *text)
{
	text->font = max->font.asciitest;
	text->image = max->i.textscreen;
	text->c = 0X00FF00FF;
	text->cb = 0xFF;
	text->sx = 140;
	text->sy = 100;
	text->x = 0;
	text->y = 0;
	text->height = 40;
	text->highlight = -1;
	max->menu.topten[0] = *text;
	max->menu.topten[0].text = max->menu.topten[0].str;
	ft_sprintf(max->menu.topten[0].str, "                                      \
                                            \n                             \
      HALL OF FAME                                   \n                    \
                                                              \n\n   \
                                                                        \
       \n Rank |    Name    |  Coalition  |    Campus    | Level |    Score\
    |   Time    \n                                                      \
                            \n");
}

void	ft_copy_score_filler(t_max *max, t_text *text, int i)
{
	while (i < 11)
	{
		max->menu.topten[i] = *text;
		if (i % 2)
			max->menu.topten[i].cb = 0x333333FF;
		max->menu.topten[i].text = max->menu.topten[i].str;
		text->sy += 40;
		ft_sprintf(max->menu.topten[i].str, " %4i |   -------- |   --------- | \
  ---------- |  ---  |  ---------  |   ----    \n", i);
		++i;
	}
}

void	ft_copy_score_bottom(t_max *max, t_text *text)
{
	text->sy = 860;
	text->height = 40;
	max->menu.topten[11] = *text;
	max->menu.topten[11].text = max->menu.topten[11].str;
	ft_sprintf(max->menu.topten[11].str, "                                      \
                                            \n                       Press \
BACKSPACE to return to the menu                      \n                    \
                                                              \n");
}

void	ft_copy_score(t_max *max, t_list *lst)
{
	t_text	text;
	t_hs	*hs;
	int		i;

	ft_copy_score_top(max, &text);
	i = 1;
	text.sy = 380;
	while (lst && i < 11)
	{
		max->menu.topten[i] = text;
		if (i % 2)
			max->menu.topten[i].cb = 0x333333FF;
		max->menu.topten[i].text = max->menu.topten[i].str;
		text.sy += 40;
		hs = lst->content;
		ft_sprintf(max->menu.topten[i].str,
			" %4i | %10.10s | %11.11s | %12.12s |   %2i  | %10i  | %6i    \n",
			i, hs->name, hs->coalition, hs->campus, hs->level,
			hs->score, hs->timems / 1000);
		lst = lst->next;
		++i;
	}
	ft_copy_score_filler(max, &text, i);
	ft_copy_score_bottom(max, &text);
}
