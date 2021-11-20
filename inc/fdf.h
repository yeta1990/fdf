/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:09:43 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/20 20:38:58 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

typedef struct	s_colors{
	int				r;
	int				g;
	int				b;
	unsigned int	rgb;
}				t_colors;

typedef struct	s_coords{
	int			x;
	int			y;
	int			z;
	t_colors	colors;
}				t_coords;

typedef struct	s_params{
	void	*mlx;
	void	*mlx_window;
}				t_params;

# include <fcntl.h>
# include <stdio.h>
# include "get_next_line.h"
# include "mlx.h"
# include "errno.h"
# include "math.h"

int			ft_atoi(const char *str);
void		print_map(t_coords **map, t_params *params, int cols, int rows);
void		draw_line(int x0, int y0, int x1, int y1, t_params *params);
int			mouse_win3(int x, int y, void *p);
int			window_close_destroy(int keycode, t_params *params);
void		free_mlx_ptr(void *mlx);
void		set_window_dimensions(int (*win_dims)[3], int map_dims[2]);
int			set_initial_x(t_coords **map, int rows, int cols, int win_dims[3]);
int			set_initial_y(t_coords **map, int rows, int win_dims[3]);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
t_colors	hex_to_int(char *str);
int			char_in_hex(char c);
void		ft_putstr_fd(char *, int fd);
void		ft_putchar_fd(char c, int fd);
int			ft_toupper(int c);
int			char_position(char *s, int c);
int			hex_decimal_converter(char a, char b);
void		parse_and_fill(int cols, int rows, t_coords **map, int square_size);
void		fill_rows(t_coords **map, char *file, int cols, int square_size);
t_coords	create_coords(int i, int j, int z, int square_size);
int			ft_is_space(char c);
void		center_map(t_coords **map, int rows, int cols, int win_dims[2]);

#endif
