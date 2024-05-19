/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buttons_10.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:01:16 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 17:01:55 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_initbutton_chooseload(t_max *max, t_button button)
{
	max->menu.loadgamebuttons[CHOOSELOAD] = button;
	max->menu.loadgamebuttons[CHOOSELOAD].id = CHOOSELOAD;
	max->menu.loadgamebuttons[CHOOSELOAD].group = LOADGROUP;
	max->menu.loadgamebuttons[CHOOSELOAD].down = &max->menu
		.loadgamebuttons[LOAD];
	max->menu.loadgamebuttons[CHOOSELOAD].state = ACTIVE;
	max->menu.loadgamebuttons[CHOOSELOAD].x = 800;
	max->menu.loadgamebuttons[CHOOSELOAD].y = 20;
	max->menu.loadgamebuttons[CHOOSELOAD].text.text = S_CHOOSELOAD;
	max->menu.loadgamebuttons[CHOOSELOAD].text.height = 40;
	max->menu.loadgamebuttons[CHOOSELOAD].text.sx = max->menu
		.loadgamebuttons[CHOOSELOAD].x + 40;
	max->menu.loadgamebuttons[CHOOSELOAD].text.sy = max->menu
		.loadgamebuttons[CHOOSELOAD].y + 40;
}

void	ft_initbutton_deleteload(t_max *max, t_button button)
{
	max->menu.loadgamebuttons[DELETE] = button;
	max->menu.loadgamebuttons[DELETE].id = DELETE;
	max->menu.loadgamebuttons[DELETE].group = LOADGROUP;
	max->menu.loadgamebuttons[DELETE].up = &max->menu
		.loadgamebuttons[CHOOSELEVEL];
	max->menu.loadgamebuttons[DELETE].right = &max->menu.loadgamebuttons[LOAD];
	max->menu.loadgamebuttons[DELETE].state = ACTIVE;
	max->menu.loadgamebuttons[DELETE].x = 800;
	max->menu.loadgamebuttons[DELETE].y = 860;
	max->menu.loadgamebuttons[DELETE].text.text = S_DELETE;
	max->menu.loadgamebuttons[DELETE].text.sx = max->menu
		.loadgamebuttons[DELETE].x + 40;
	max->menu.loadgamebuttons[DELETE].text.sy = max->menu
		.loadgamebuttons[DELETE].y + 40;
}

void	ft_initbutton_load(t_max *max, t_button button)
{
	max->menu.loadgamebuttons[LOAD] = button;
	max->menu.loadgamebuttons[LOAD].id = LOAD;
	max->menu.loadgamebuttons[LOAD].group = LOADGROUP;
	max->menu.loadgamebuttons[LOAD].up = &max->menu
		.loadgamebuttons[CHOOSELEVEL];
	max->menu.loadgamebuttons[LOAD].left = &max->menu.loadgamebuttons[DELETE];
	max->menu.loadgamebuttons[LOAD].state = ACTIVE;
	max->menu.loadgamebuttons[LOAD].x = 1200;
	max->menu.loadgamebuttons[LOAD].y = 860;
	max->menu.loadgamebuttons[LOAD].text.text = S_LOAD;
	max->menu.loadgamebuttons[LOAD].text.sx = max->menu
		.loadgamebuttons[LOAD].x + 40;
	max->menu.loadgamebuttons[LOAD].text.sy = max->menu
		.loadgamebuttons[LOAD].y + 40;
}

void	ft_initbutton_hofback(t_max *max, t_button button)
{
	max->menu.halloffamebuttons[HOFBACK] = button;
	max->menu.halloffamebuttons[HOFBACK].id = HOFBACK;
	max->menu.halloffamebuttons[HOFBACK].group = HALLOFFAMEGROUP;
	max->menu.halloffamebuttons[HOFBACK].state = ACTIVE;
	max->menu.halloffamebuttons[HOFBACK].x = 1250;
	max->menu.halloffamebuttons[HOFBACK].y = 860;
	max->menu.halloffamebuttons[HOFBACK].text.text = S_BACK;
	max->menu.halloffamebuttons[HOFBACK].text.sx = max->menu
		.halloffamebuttons[HOFBACK].x + 40;
	max->menu.halloffamebuttons[HOFBACK].text.sy = max->menu
		.halloffamebuttons[HOFBACK].y + 40;
}

void	ft_initbuttons_global_helper_2(t_max *max, t_button button)
{
	ft_initbutton_rrandomize(max, button);
	ft_initbutton_rplay(max, button);
	ft_initbutton_choosesave(max, button);
	ft_initbutton_delete(max, button);
	ft_initbutton_save(max, button);
	ft_initbutton_chooseload(max, button);
	ft_initbutton_deleteload(max, button);
	ft_initbutton_load(max, button);
	ft_initbutton_hofback(max, button);
}
