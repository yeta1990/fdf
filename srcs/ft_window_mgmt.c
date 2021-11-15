/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window_mgmt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:29:37 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/15 17:36:52 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouse_win3(int x, int y, void *p)
{
	printf("Mouse moving in Win3, at %dx%d.%p\n", x, y, p);
	return (1);
}

int	window_close_destroy(int keycode, t_params *params)
{
	if (keycode == 53)
	{
		mlx_destroy_window(params->mlx, params->mlx_window);
	//	mlx_destroy_window(params.mlx, params.mlx_window);
		free_mlx_ptr(params->mlx);
		exit(0);
	}
	return (1);
}

void	set_window_dimensions(int (*win_dims)[2], int map_dims[2])
{
	int	diagonal = map_dims[0] * map_dims[1];

	if (diagonal > 10000)
	{
		(*win_dims)[0] = 1000;
		(*win_dims)[1] = 800;
	}
	else if (diagonal > 2500)
	{
		(*win_dims)[0] = 1000;
		(*win_dims)[1] = 600;
	}
	else
	{
		(*win_dims)[0] = 530;
		(*win_dims)[1] = 410;
	}
}

int	set_initial_x(t_coords **map, int rows, int cols, int win_dims[2])
{
	int	max_width;
	int	initial_x;

	rows += 0;
	max_width = map[rows - 1][cols - 1].x - map[0][0].x;
//	printf("corner1: %i, corner0: %i\n", map[rows - 1][cols].x, map[0][0].x);
	initial_x = win_dims[0] / 2 - max_width / 2;
//	printf("max_width: %i, initial_x: %i\n", max_width, initial_x);
	return (initial_x);
}
