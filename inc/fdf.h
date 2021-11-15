/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:09:43 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/15 17:28:55 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

typedef struct	s_coords{
	int	x;
	int	y;
	int	z;
	int	color;
}				t_coords;

typedef struct	s_params{
	void	*mlx;
	void	*mlx_window;
}				t_params;

# include <fcntl.h>
# include <stdio.h>
# include "get_next_line.h"
# include "mlx.h"

int		ft_atoi(const char *str);
void	print_map(t_coords **map, t_params *params, int cols, int rows, int initial_x);
void	draw_line(int x0, int y0, int x1, int y1, t_params *params);
int		mouse_win3(int x, int y, void *p);
int		window_close_destroy(int keycode, t_params *params);
void	free_mlx_ptr(void *mlx);
void	set_window_dimensions(int (*win_dims)[2], int map_dims[2]);
int		set_initial_x(t_coords **map, int rows, int cols, int win_dims[2]);

#endif
