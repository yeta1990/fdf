/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:40:34 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/22 16:40:51 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	pixel_into_scope(t_coords *point)
{
	if (point->x < 0 || point->y < 0)
		return (0);
	else if (point->x > 1200 || point->y > 1200)
		return (0);
	return (1);
}

void	slope_calc(int *dx, int *dy, int *stepx, int *stepy)
{
	if (*dy < 0)
	{
		*dy = *dy * -1;
		*stepy = -1;
	}
	else
		*stepy = 1;
	if (*dx < 0)
	{
		*dx = *dx * -1;
		*stepx = -1;
	}
	else
		*stepx = 1;
	*dy = *dy * 2;
	*dx = *dx * 2;
}
