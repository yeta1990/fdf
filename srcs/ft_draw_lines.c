/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:19:47 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/15 12:22:14 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(int x0, int y0, int x1, int y1, t_params *params)
{
	int	dx;
	int	dy;
	int	stepx;
	int	stepy;
	int	fraction;

	dx = x1 - x0;
	dy = y1 - y0;
	if (dy < 0)
	{
		dy = dy * -1;
		stepy = -1;
	}
	else
		stepy = 1;
	if (dx < 0)
	{
		dx = dx * -1;
		stepx = -1;
	}
	else
		stepx = 1;
	dy = dy * 2;
	dx = dx * 2;
	if ((0 <= x0) && (x0 < 1200) && (0 <= y0) && (y0 < 1200))
		mlx_pixel_put(params->mlx, params->mlx_window, x0, y0, 0xffffff);
	if (dx > dy)
	{
		fraction = dy - (dx / 2);
		while (x0 != x1)
		{
			x0 += stepx;
			if (fraction >= 0)
			{
				y0 += stepy;
				fraction -= dx;
			}
			fraction += dy;
			if ((0 <= x0) && (x0 < 1200) && (0 <= y0) && (y0 < 1200))
				mlx_pixel_put(params->mlx, params->mlx_window, x0, y0, 0xffffff);
		}
	}
	else
	{
		fraction = dx - (dy / 2);
		while (y0 != y1)
		{
			if (fraction >= 0)
			{
				x0 += stepx;
				fraction -= dy;
			}
			y0 += stepy;
			fraction += dx;
			if ((0 <= x0) && (x0 < 1200) && (0 <= y0) && (y0 < 1200))
				mlx_pixel_put(params->mlx, params->mlx_window, x0, y0, 0xffffff);
		}
	}
}

