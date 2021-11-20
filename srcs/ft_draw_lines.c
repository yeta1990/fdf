/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:19:47 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/21 00:47:15 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_coords start, t_coords end, t_params *params)
//void	draw_line(int x0, int y0, int x1, int y1, t_params *params)
{
	int	dx;
	int	dy;
	int	stepx;
	int	stepy;
	int	fraction;
	t_coords initial;
	int	color;

	color = 0;
	initial = start;
	initial.x = start.x;

	dx = end.x - start.x;
	dy = end.y - start.y;
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
	if ((0 <= start.x) && (start.x < 1200) && (0 <= start.y) && (start.y < 1200))
		mlx_pixel_put(params->mlx, params->mlx_window, start.x, start.y, start.colors.rgb);
	if (dx > dy)
	{
		fraction = dy - (dx / 2);
		while (start.x != end.x)
		{
			start.x += stepx;
			if (fraction >= 0)
			{
				start.y += stepy;
				fraction -= dx;
			}
			fraction += dy;
			if ((0 <= start.x) && (start.x < 1200) && (0 <= start.y) && (start.y < 1200))
			{
				color = calculate_point_color(initial, end, start.x, 1);
				mlx_pixel_put(params->mlx, params->mlx_window, start.x, start.y, color);
			}
		}
	}
	else
	{
		fraction = dx - (dy / 2);
		while (start.y != end.y)
		{
			if (fraction >= 0)
			{
				start.x += stepx;
				fraction -= dy;
			}
			start.y += stepy;
			fraction += dx;
			if ((0 <= start.x) && (start.x < 1200) && (0 <= start.y) && (start.y < 1200))
			{
				printf("initial: %i, end: %i, current: %i\n", initial.y, end.y, start.y);
				color = calculate_point_color(initial, end, start.y, 2);
				mlx_pixel_put(params->mlx, params->mlx_window, start.x, start.y, color);
			}
		}
	}
}

