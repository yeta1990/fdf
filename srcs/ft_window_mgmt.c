/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window_mgmt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:29:37 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/24 12:50:32 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	window_close_destroy(int keycode, t_params *params)
{
	if (keycode == 53)
	{
		mlx_clear_window(params->mlx, params->mlx_window);
		mlx_destroy_window(params->mlx, params->mlx_window);
		exit(0);
	}
	return (1);
}

//add z dimension to map_dims. if the map is taller than wide, 
//the result window has to be consistent with that
void	set_window_dimensions(int (*win_dims)[3], int map_dims[2])
{
	int	diagonal;

	diagonal = map_dims[0] * map_dims[1];
	if (diagonal > 10000)
	{
		(*win_dims)[0] = 1800;
		(*win_dims)[1] = 1200;
		(*win_dims)[2] = 3;
	}
	else if (diagonal > 2500)
	{
		(*win_dims)[0] = 1000;
		(*win_dims)[1] = 800;
		(*win_dims)[2] = 5;
	}
	else if (diagonal > 1200)
	{
		(*win_dims)[0] = 800;
		(*win_dims)[1] = 800;
		(*win_dims)[2] = 8;
	}
	else
		set_window_dimensions_2(diagonal, win_dims);
}

void	set_window_dimensions_2(int diagonal, int (*win_dims)[3])
{
	if (diagonal > 500)
	{
		(*win_dims)[0] = 800;
		(*win_dims)[1] = 600;
		(*win_dims)[2] = 13;
	}
	else
	{
		(*win_dims)[0] = 530;
		(*win_dims)[1] = 410;
		(*win_dims)[2] = 15;
	}
}

int	set_initial_x(t_coords **map, int rows, int cols, int win_dims[2])
{
	int	max_width;
	int	initial_x;

	max_width = map[rows - 1][cols - 1].x - map[0][0].x;
	initial_x = win_dims[0] / 2 - max_width / 2;
	return (initial_x);
}

int	set_initial_y(t_coords **map, int rows, int win_dims[2])
{
	int	initial_y;

	initial_y = win_dims[1] - map[rows - 1][0].y - 10;
	return (initial_y);
}
