/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window_mgmt2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 10:59:18 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/22 13:02:23 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	create_window_hooks(t_coords **map, int map_dims[2], int w_dims[3])
{
	t_params	params;

	params.mlx = mlx_init();
	if (!params.mlx)
	{
		ft_putstr_fd("Error creating window\n", 2);
		exit(1);
	}
	params.mlx_window = mlx_new_window(params.mlx, w_dims[0], w_dims[1], "fdf");
	if (!params.mlx_window)
	{
		write(1, "Error creating window\n", 22);
		exit(1);
	}
	print_map(map, &params, map_dims[0], map_dims[1]);
	mlx_key_hook(params.mlx_window, window_close_destroy, &params);
	mlx_hook(params.mlx_window, 17, (1L << 17), byebye, &params);
	mlx_loop(params.mlx);
	free_mlx_ptr(params.mlx);
}

int	byebye(void)
{
	exit(0);
	return (1);
}
