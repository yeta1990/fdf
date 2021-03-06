/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:09:43 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/24 12:53:30 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <stdio.h>
# include "get_next_line.h"
# include <mlx.h>
# include "errno.h"
# include "math.h"

typedef struct s_colors{
	int				r;
	int				g;
	int				b;
	unsigned int	rgb;
}				t_colors;

typedef struct s_coords{
	int			x;
	int			y;
	int			z;
	t_colors	colors;
}				t_coords;

typedef struct s_params{
	void		*mlx;
	void		*mlx_window;
	int			width;
	int			height;
	t_coords	***map;
	int			map_x;
	int			map_y;
}				t_params;

typedef struct s_line{
	t_coords	*point;
	t_coords	*end;
	t_coords	origin;
	int			dx;
	int			dy;
	int			stepx;
	int			stepy;
	int			fraction;
}				t_line;

int			ft_atoi(const char *str);
void		print_map(t_coords **map, t_params *params, int cols, int rows);
void		draw_line(t_coords start, t_coords end, t_params *params);
int			mouse_win3(int x, int y, void *p);
int			window_close_destroy(int keycode, t_params *params);
void		set_window_dimensions(int (*win_dims)[3], int map_dims[2]);
void		set_window_dimensions_2(int diagonal, int (*win_dims)[3]);
int			set_initial_x(t_coords **map, int rows, int cols, int win_dims[3]);
int			set_initial_y(t_coords **map, int rows, int win_dims[3]);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
t_colors	hex_to_int(char *str);
int			char_in_hex(char c);
void		ft_putstr_fd(char *str, int fd);
void		ft_putchar_fd(char c, int fd);
int			ft_toupper(int c);
int			char_pos(char *s, int c);
int			hex_decimal_converter(char a, char b);
void		fill_rows(t_coords **map, char *file, int square_size, int z_len);
t_coords	create_coords(int i, int j, int z);
int			ft_is_space(char c);
void		center_map(t_coords **map, int rows, int cols, int win_dims[2]);
double		get_relative_position(int start, int end, int pos);
int			calc_saturation(int start_color, int end_color, double relation);
int			calc_point_color(t_coords start, t_coords end, int pos, int comb);
void		create_window_hooks(t_coords **map, int map_dims[2], int w_dims[3]);
int			byebye(void);
void		draw_horizontal(t_params *p, t_line *l);
void		draw_vertical(t_params *p, t_line *l);
void		slope_calc(int *dx, int *dy, int *stepx, int *stepy);
int			hex_map_checker(char *str);
t_coords	**assign_memory(int map_dims[2]);
int			get_map_cols(char *file, int *rows);
int			get_map_rows(char *file);
void		parse_one_row(char *row, t_coords ***map, int sq_size, int z_l);
t_line		set_line_params(t_coords *start, t_coords *end);
void		draw_horizontal(t_params *p, t_line *l);
int			pixel_into_scope(t_coords *point, t_params *p);
int			cols_counter(char *row);
void		throw_argc_error(char *name);
void		throw_parse_error(int n);

#endif
