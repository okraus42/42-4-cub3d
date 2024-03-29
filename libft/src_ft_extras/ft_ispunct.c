/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ispunct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:39:15 by okraus            #+#    #+#             */
/*   Updated: 2023/12/30 15:43:36 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

int	ft_ispunct(int c)
{
	static int	index[256] = {0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3,
		0x2003, 0x2003, 0x2003, 0x2003, 0x2003, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3,
		0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x6001,
		0xc005, 0xc005, 0xc005, 0xc005, 0xc005, 0xc005, 0xc005, 0xc005, 0xc005,
		0xc005, 0xc005, 0xc005, 0xc005, 0xc005, 0xc005, 0xd809, 0xd809, 0xd809,
		0xd809, 0xd809, 0xd809, 0xd809, 0xd809, 0xd809, 0xd809, 0xc005, 0xc005,
		0xc005, 0xc005, 0xc005, 0xc005, 0xc005, 0xd509, 0xd509, 0xd509, 0xd509,
		0xd509, 0xd509, 0xc509, 0xc509, 0xc509, 0xc509, 0xc509, 0xc509, 0xc509,
		0xc509, 0xc509, 0xc509, 0xc509, 0xc509, 0xc509, 0xc509, 0xc509, 0xc509,
		0xc509, 0xc509, 0xc509, 0xc509, 0xc005, 0xc005, 0xc005, 0xc005, 0xc005,
		0xc005, 0xd609, 0xd609, 0xd609, 0xd609, 0xd609, 0xd609, 0xc609, 0xc609,
		0xc609, 0xc609, 0xc609, 0xc609, 0xc609, 0xc609, 0xc609, 0xc609, 0xc609,
		0xc609, 0xc609, 0xc609, 0xc609, 0xc609, 0xc609, 0xc609, 0xc609, 0xc609,
		0xc005, 0xc005, 0xc005, 0xc005, 0x3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	if (c & 0xFFFFFF00)
		return (0);
	return (index[c] & 0x4);
}
