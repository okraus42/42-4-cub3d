/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percentil.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:42:56 by okraus            #+#    #+#             */
/*   Updated: 2024/05/10 16:36:02 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

long long	ft_percentil(long long a, long long b, long long c, long long d)
{
	return (((a) + ((b) - (a)) * (c) / (d)));
}
