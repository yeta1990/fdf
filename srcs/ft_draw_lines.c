/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:19:47 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/21 23:55:08 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_coords start, t_coords end, t_params *params)
{
	int	dx;
	int	dy;
	int	stepx;
	int	stepy;
	int	fraction;
	t_coords initial;

	initial = start;
	initial.x = start.x;
	initial.y = start.y;
	dx = end.x - start.x;
	dy = end.y - start.y;
	slope_calc(&dx, &dy, &stepx, &stepy);
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
			draw_horiz(params, start, end, initial);
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
			draw_vert(params, start, end, initial);
		}
	}
}

void	draw_horiz(t_params *p, t_coords start, t_coords end, t_coords ini)
{
	int	color;

	if ((0 <= start.x) && (start.x < 1200) && (0 <= start.y) && (start.y < 1200))
	{
		color = calc_point_color(ini, end, start.x, 1);
		mlx_pixel_put(p->mlx, p->mlx_window, start.x, start.y, color);
	}
}

void	draw_vert(t_params *p, t_coords start, t_coords end, t_coords ini)
{
	int	color;

	if ((0 <= start.x) && (start.x < 1200) && (0 <= start.y) && (start.y < 1200))
	{
		color = calc_point_color(ini, end, start.y, 2);
		mlx_pixel_put(p->mlx, p->mlx_window, start.x, start.y, color);
	}
}

void		slope_calc(int *dx, int *dy, int *stepx, int *stepy)
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
