/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:08:50 by okraus            #+#    #+#             */
/*   Updated: 2023/10/23 16:25:03 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// cc math.c -lm
//do not forget the -lm flag for the math library

#include <math.h>
#include <stdio.h>

#define RAD2DEG 0.0174532925199
#define DEG2RAD 57.2957795131

void	ft_init_sin(int sinArr[360])
{
	int	i;

	while (i < 360)
	{
		sinArr[i] = 65536 * sin(RAD2DEG * i);
		++i;
	}
	sinArr[0] = 0;
	sinArr[90] = 65536 * 1;
	sinArr[180] = 0;
	//sinArr[270] = 65536 * -1;
}

int	main(void)
{
	int	sinArr[360];
	int	i;

	ft_init_sin(sinArr);
	i = 0;
	while (i < 360)
	{
		printf("%i° sin=%f\n", i, sinArr[i] / 65536.0);
		++i;
	}
	return (0);
}