/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_halloffame_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:15:23 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 18:15:56 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

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
