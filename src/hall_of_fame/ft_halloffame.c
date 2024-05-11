/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_halloffame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:32:15 by okraus            #+#    #+#             */
/*   Updated: 2024/05/11 18:17:03 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

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
