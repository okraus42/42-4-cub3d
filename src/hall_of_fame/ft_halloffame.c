/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_halloffame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:32:15 by okraus            #+#    #+#             */
/*   Updated: 2024/05/11 13:54:03 by okraus           ###   ########.fr       */
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

int	ft_sortscore(t_list *lst)
{
	t_hs	*now;
	t_hs	*next;
	int		r;

	r = 0;
	while (lst && lst->next)
	{
		now = lst->content;
		next = lst->next->content;
		if (now->score < next->score)
		{
			lst->next->content = now;
			lst->content = next;
			r = 1;
		}
		lst = lst->next;
	}
	return (r);
}

void	ft_free_hs(void *content)
{
	t_hs	*tmp;

	tmp = content;
	free(tmp);
}

void	ft_highscore_sort_loop_2(char *str, t_hs *tmp)
{
	int	j;
	int	zero[6];

	j = 0;
	while (j < 6)
	{
		zero[j] = 0;
		if (j)
			zero[j] = zero[j - 1] + 1;
		while (str && str[zero[j]] && str[zero[j]] != 036
			&& str[zero[j]] != '\n')
			zero[j]++;
		str[zero[j]] = '\0';
		++j;
	}
	tmp->level = ft_atoi(&str[zero[2] + 1]);
	tmp->score = ft_atoi(&str[zero[3] + 1]);
	tmp->timems = ft_atoi(&str[zero[4] + 1]);
	ft_sprintf(tmp->name, str);
	ft_sprintf(tmp->coalition, &str[zero[0] + 1]);
	ft_sprintf(tmp->campus, &str[zero[1] + 1]);
}

void	ft_highscore_sort_loop(t_max *max, int fd, char *str, t_list **head)
{
	int		i;
	t_hs	*tmp;
	t_list	*leaf;

	i = 0;
	while (str)
	{
		tmp = ft_calloc(sizeof(t_hs), 1);
		if (!tmp)
			ft_exit(max, 2);
		tmp->index = i;
		ft_highscore_sort_loop_2(str, tmp);
		leaf = ft_lstnew(tmp);
		if (!leaf)
			ft_exit(max, 2);
		ft_lstadd_back(head, leaf);
		i++;
		free(str);
		str = NULL;
		str = get_next_line(fd);
	}
}

void	ft_highscore(t_max *max, int fd)
{
	t_list	*head;
	char	*str;

	head = NULL;
	str = get_next_line(fd);
	ft_highscore_sort_loop(max, fd, str, &head);
	while (ft_sortscore(head))
		continue ;
	ft_copy_score(max, head);
	ft_lstclear(&head, ft_free_hs);
}

int	ft_readscore(t_max *max)
{
	int	fd;

	fd = open("./data/halloffame.txt", O_RDONLY);
	if (fd < 0)
	{
		ft_dprintf(2, "Error\nFailed to open halloffame.txt\n");
		return (1);
	}
	ft_highscore(max, fd);
	close (fd);
	return (0);
}

void	ft_halloffame(t_max *max)
{
	int	i;

	i = 0;
	ft_draw_background(max);
	while (i < 12)
	{
		ft_draw_text(&max->menu.topten[i], 0);
		++i;
	}
	if (max->keys[MLX_KEY_BACKSPACE])
	{
		max->keys[MLX_KEY_BACKSPACE] = 0;
		max->game_mode = MENU;
		max->menu.current_buttongroup = MAINBUTTONS;
		max->i.textscreen->enabled = 0;
	}
}
