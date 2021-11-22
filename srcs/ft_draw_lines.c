/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:19:47 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/22 16:43:08 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// 	Creates t_line struct with all needed parameters to draw a line:
// 	- Point: coords of the pixel to be printed, change through drawing iteration
// 	- Origin: copy of start, mainly needed to calculate color gradient point to
// point
//	- End: needed to stop drawing and to calculate color of the "Point"
//	- Dx, dy, stepx, stepy: other params to take into account before
//	drawing a pixel, mainly to determine line orientation and slope.
t_line	set_line_params(t_coords *start, t_coords *end)
{
	t_line	line;

	line.point = start;
	line.end = end;
	line.origin.x = start->x;
	line.origin.y = start->y;
	line.origin.colors = start->colors;
	line.dx = end->x - start->x;
	line.dy = end->y - start->y;
	slope_calc(&(line.dx), &(line.dy), &(line.stepx), &(line.stepy));
	return (line);
}

void	draw_pixel(t_params *p, t_coords *po, int color)
{
	mlx_pixel_put(p->mlx, p->mlx_window, po->x, po->y, color);
}

void	draw_line(t_coords start, t_coords end, t_params *params)
{
	t_line	line;

	line = set_line_params(&start, &end);
	if (pixel_into_scope(line.point))
		draw_pixel(params, line.point, line.point->colors.rgb);
	if (line.dx > line.dy)
		draw_horizontal(params, &line);
	else
		draw_vertical(params, &line);
}

void	draw_horizontal(t_params *p, t_line *l)
{
	int	color;

	l->fraction = l->dy - (l->dx / 2);
	while (l->point->x != l->end->x)
	{
		l->point->x += l->stepx;
		if (l->fraction >= 0)
		{
			l->point->y += l->stepy;
			l->fraction -= l->dx;
		}
		l->fraction += l->dy;
		if (pixel_into_scope(l->point))
		{
			color = calc_point_color(l->origin, *(l->end), l->point->x, 1);
			draw_pixel(p, l->point, color);
		}
	}
}

void	draw_vertical(t_params *p, t_line *l)
{
	int	color;

	l->fraction = l->dx - (l->dy / 2);
	while (l->point->y != l->end->y)
	{
		if (l->fraction >= 0)
		{
			l->point->x += l->stepx;
			l->fraction -= l->dy;
		}
		l->point->y += l->stepy;
		l->fraction += l->dx;
		if (pixel_into_scope(l->point))
		{
			color = calc_point_color(l->origin, *(l->end), l->point->y, 2);
			draw_pixel(p, l->point, color);
		}
	}
}
/*
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
}*/
