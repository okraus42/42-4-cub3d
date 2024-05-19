/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listfield_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:00:40 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 19:01:30 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

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
