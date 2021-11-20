/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_interpolation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 22:46:26 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/21 00:47:01 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	get_relative_position(int start, int end, int pos)
{
	double	a;
	double	b;
	double	result;

	if (end - start == 0)
		return (1);
	a = pos - start;
	b = end - start;
	result = a / b;
	return (result);
}

int	calc_saturation(int	start_color, int end_color, double relation)
{
	return ((int)((1 - relation) * start_color + relation * end_color));
}

int	calculate_point_color(t_coords start, t_coords end, int pos, int comb)
{
    int     red;
    int     green;
    int     blue;
	double	relation;

    if (start.colors.rgb == end.colors.rgb)
        return (start.colors.rgb);
	if (comb == 1)
		relation = get_relative_position(start.x, end.x, pos);
	else
		relation = get_relative_position(start.y, end.y, pos);
	red = calc_saturation(start.colors.r & 0xFF, end.colors.r & 0xFF, relation);
    green = calc_saturation(start.colors.g & 0xFF, end.colors.g & 0xFF, relation);
    blue = calc_saturation(start.colors.b & 0xFF, end.colors.b & 0xFF, relation);
	return ((red << 16) | (green << 8) | blue);	
}
