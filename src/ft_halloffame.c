/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_halloffame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:32:15 by okraus            #+#    #+#             */
/*   Updated: 2024/04/12 09:18:04 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int	ft_writescore(t_max *max)
{
	int	fd;

	fd = open("./data/halloffame.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_dprintf(2, "Error\nFailed to open halloffame.txt\n");
		ft_dprintf(2, "%s\036%s\036%s\036%i\036%i\036%u\n", max->name, max->coalition, max->campus, max->level, max->score, max->gamems);
		return (1);
	}
	ft_dprintf(fd, "%s\036%s\036%s\036%i\036%i\036%u\n", max->name, max->coalition, max->campus, max->level, max->score, max->gamems);
	close(fd);
	return (0);
}
// typedef struct s_text
// {
// 	mlx_texture_t	*font;
// 	mlx_image_t		*image;
// 	char			*text;
// 	char			str[20];
// 	unsigned int	c;
// 	unsigned int	cb;
// 	int				sx;
// 	int				sy;
// 	int				x;
// 	int				y;
// 	int				i;
// 	int				highlight;
// 	int				offset;
// 	int				height;
// }	t_text;

void	ft_copy_score(t_max *max, t_list *lst)
{
	t_text	text;
	t_hs	*hs;
	int		i;

	// text.text = text.str;
	text.font = max->font.asciitest;
	text.image = max->i.textscreen;
	text.c = 0X00FF00FF;
	text.cb = 0xFF;
	text.sx = 140;
	text.sy = 100;
	text.x = 0;
	text.y = 0;
	text.height = 40;
	text.highlight = -1;
	
	max->menu.topten[0] = text;
	max->menu.topten[0].text = max->menu.topten[0].str;
	ft_sprintf(max->menu.topten[0].str, "                                                                                  \n                                   HALL OF FAME                                   \n                                                                                  \n\n                                                                                  \n Rank |    Name    |  Coalition  |    Campus    | Level |    Score    |   Time    \n                                                                                  \n");
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
		ft_sprintf(max->menu.topten[i].str, " %4i | %10.10s | %11.11s | %12.12s |   %2i  | %10i  | %6i    \n", i, hs->name, hs->coalition, hs->campus, hs->level, hs->score, hs->timems / 1000);
		lst = lst->next;
		++i;
	}
	while (i < 11)
	{
		max->menu.topten[i] = text;
		if (i % 2)
			max->menu.topten[i].cb = 0x333333FF;
		max->menu.topten[i].text = max->menu.topten[i].str;
		text.sy += 40;
		ft_sprintf(max->menu.topten[i].str, " %4i |   -------- |   --------- |   ---------- |  ---  |  ---------  |   ----    \n", i);
		++i;
	}
	text.sy = 860;
	text.height = 40;
	max->menu.topten[i] = text;
	max->menu.topten[i].text = max->menu.topten[i].str;
	ft_sprintf(max->menu.topten[i].str, "                                                                                  \n                       Press BACKSPACE to return to the menu                      \n                                                                                  \n");
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

void	ft_highscore(t_max *max, int fd)
{
	t_hs	*tmp;
	t_list	*head;
	t_list	*leaf;
	char	*str;
	int		i;
	int		j;
	int		zero[6];

	i = 0;

	head = NULL;
	str = get_next_line(fd);
	while (str)
	{
		tmp = ft_calloc(sizeof(t_hs), 1);
		if (!tmp)
			exit(2);
		tmp->index = i;
		j = 0;
		while (j < 6)
		{
			zero[j] = 0;
			if (j)
				zero[j] = zero[j - 1] + 1;
			while(str && str[zero[j]] && str[zero[j]] != 036 && str[zero[j]] != '\n')
				zero[j]++;
			str[zero[j]] = '\0';
			++j;
		}
		// zero[0] = 0;
		// while(str && str[zero[0]] != 036)
		// 	zero[0]++;
		// str[zero[0]] = '\0';
		// zero[1] = zero[0] + 1;
		// while(str && str[zero[1]] != 036)
		// 	zero[1]++;
		// str[zero[1]] = '\0';
		// zero[2] = zero[1] + 1;
		// while(str && str[zero[2]] != 036)
		// 	zero[2]++;
		// str[zero[2]] = '\0';
		// zero[3] = zero[2] + 1;
		// while(str && str[zero[3]] != '\n')
		// 	zero[3]++;
		//str[zero[5]] = '\0';
		tmp->level = ft_atoi(&str[zero[2] + 1]);
		tmp->score = ft_atoi(&str[zero[3] + 1]);
		tmp->timems = ft_atoi(&str[zero[4] + 1]);
		//tmp->name = ft_stringcopy(str);
		ft_sprintf(tmp->name, str);
		ft_sprintf(tmp->coalition, &str[zero[0] + 1]);
		ft_sprintf(tmp->campus, &str[zero[1] + 1]);
		// if (!tmp->name)
		// 	exit(2);
		// tmp->coalition = ft_stringcopy(&str[zero[0] + 1]);
		// if (!tmp->coalition)
		// 	exit(2);
		leaf = ft_lstnew(tmp);
		if (!leaf)
			exit(2); //better exit and free list
		ft_lstadd_back(&head, leaf);
		i++;
		free(str);
		str = NULL;
		str = get_next_line(fd);
	}
	while (ft_sortscore(head))
		continue;
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

// fd = open("score.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
// 		if (fd < 0)
// 			return (1);
// 		ft_dprintf(fd, "%s:%s:%i:%i\n", max.player_name, max.player_coalition, max.score, max.flevel);
// 		free(max.player_name);
// 		free(max.player_coalition);
// 		close(fd);
// 		fd = open("score.txt", O_RDONLY);
// 		if (fd < 0)
// 			return (1);
// 		ft_highscore(fd);
// 		close (fd);

// void	ft_print_score(t_list *lst)
// {
// 	t_hs	*tmp;
// 	int		i;

// 	i = 1;
// 	ft_printf("%1.*^*CPosition   |                Name   |           Coalition   |      Score  |  Level %C\n", 0xFFFFFF, 0x000000);
// 	while (lst && i <= 25)
// 	{
// 		tmp = lst->content;
// 		if (!ft_strncmp(tmp->coalition, NABOO, 10))
// 			ft_printf("%1.*^*C", 0xFFFFFF, 0x678DA4);
// 		else if (!ft_strncmp(tmp->coalition, ALDERAAN, 10))
// 			ft_printf("%1.*^*C", 0xFFFFFF, 0xAD8F65);
// 		else if (!ft_strncmp(tmp->coalition, TATOOINE, 10))
// 			ft_printf("%1.*^*C", 0xFFFFFF, 0xE08F4C);
// 		else if (!ft_strncmp(tmp->coalition, MANDALORE, 10))
// 			ft_printf("%1.*^*C", 0xFFFFFF, 0x9C0505);
// 		else
// 			ft_printf("%1.*^*C", 0xFFFFFF, 0x008822);
// 		// if (!(i % 4))
// 		// 	ft_printf("%1.*^*C", 0xFFFFFF, 0x008080);
// 		// else if (!(i % 4 - 1))
// 		// 	ft_printf("%1.*^*C", 0xFFFFFF, 0x191970);
// 		// else if (!(i % 4 - 2))
// 		// 	ft_printf("%1.*^*C", 0xFFFFFF, 0x2E8B57);
// 		// else if (!(i % 4 - 3))
// 		// 	ft_printf("%1.*^*C", 0xFFFFFF, 0X4B0082);
// 		// else
// 		// 	ft_printf("%1.*^*C", 0xFFFFFF, 0x008822);
// 		ft_printf("     %3i   |", i);
// 		ft_printf("%20s   |", tmp->name);
// 		ft_printf("%20s   |", tmp->coalition);
// 		ft_printf(" %10i  |", tmp->score);
// 		ft_printf("  %5i ", tmp->level);
// 		ft_printf("%C\n");
// 		lst = lst->next;
// 		++i;
// 	}
// }

// int	ft_sortscore(t_list *lst)
// {
// 	t_hs	*now;
// 	t_hs	*next;
// 	int		r;

// 	r = 0;
// 	while (lst && lst->next)
// 	{
// 		now = lst->content;
// 		next = lst->next->content;
// 		if (now->score < next->score)
// 		{
// 			lst->next->content = now;
// 			lst->content = next;
// 			r = 1;
// 		}
// 		lst = lst->next;
// 	}
// 	return (r);
// }

// void	ft_free_hs(void *content)
// {
// 	t_hs	*tmp;

// 	tmp = content;
// 	free(tmp->name);
// 	free(tmp->coalition);
// 	free(tmp);
// }

// void	ft_highscore(int fd)
// {
// 	t_hs	*tmp;
// 	t_list	*head;
// 	t_list	*leaf;
// 	char	*str;
// 	int		i;
// 	int		zero[4];

// 	i = 0;

// 	head = NULL;
// 	str = get_next_line(fd);
// 	while (str)
// 	{
// 		tmp = malloc(sizeof(t_hs));
// 		if (!tmp)
// 			exit(2);
// 		tmp->index = i;
// 		zero[0] = 0;
// 		while(str && str[zero[0]] != ':')
// 			zero[0]++;
// 		str[zero[0]] = '\0';
// 		zero[1] = zero[0] + 1;
// 		while(str && str[zero[1]] != ':')
// 			zero[1]++;
// 		str[zero[1]] = '\0';
// 		zero[2] = zero[1] + 1;
// 		while(str && str[zero[2]] != ':')
// 			zero[2]++;
// 		str[zero[2]] = '\0';
// 		zero[3] = zero[2] + 1;
// 		while(str && str[zero[3]] != '\n')
// 			zero[3]++;
// 		str[zero[3]] = '\0';
// 		tmp->level = ft_atoi(&str[zero[2] + 1]);
// 		tmp->score = ft_atoi(&str[zero[1] + 1]);
// 		tmp->name = ft_stringcopy(str);
// 		if (!tmp->name)
// 			exit(2);
// 		tmp->coalition = ft_stringcopy(&str[zero[0] + 1]);
// 		if (!tmp->coalition)
// 			exit(2);
// 		leaf = ft_lstnew(tmp);
// 		if (!leaf)
// 			exit(2);
// 		ft_lstadd_back(&head, leaf);
// 		i++;
// 		free(str);
// 		str = NULL;
// 		str = get_next_line(fd);
// 	}
// 	while (ft_sortscore(head))
// 		continue;
// 	ft_print_score(head);
// 	ft_lstclear(&head, ft_free_hs);
// }