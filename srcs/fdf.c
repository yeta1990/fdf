/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+ */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:22:44 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/23 16:01:11 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	int			map_dims[2];
	t_coords	**map;
	int			win_dims[3];

	if (argc != 2 && argc != 4)
		throw_argc_error(argv[0]);
	map = 0;
	map_dims[0] = get_map_cols(argv[1]);
	map_dims[1] = get_map_rows(argv[1]);
	if (map_dims[0] == 0 && map_dims[1] == 0)
		throw_parse_error(3);
	map = assign_memory(map_dims);
	set_window_dimensions(&win_dims, map_dims);
	if (argc == 4 && ft_atoi(argv[3]) != 0)
	{
		if (ft_atoi(argv[2]) > 0)
			win_dims[2] = ft_atoi(argv[2]);
		fill_rows(map, argv[1], win_dims[2], ft_atoi(argv[3]));
	}
	else
		fill_rows(map, argv[1], win_dims[2], 0);
	center_map(map, map_dims[1], map_dims[0], win_dims);
	create_window_hooks(map, map_dims, win_dims);
}

void	throw_argc_error(char *name)
{
	ft_putstr_fd("Usage : ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(" [map.fdf] <filename> [ case_size z_size ]\n", 2);
	exit(1);
}

void	print_map(t_coords **map, t_params *params, int cols, int rows)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (i < rows - 1 && j < cols - 1)
			{
				draw_line(map[i][j], map[i][j + 1], params);
				draw_line(map[i][j], map[i + 1][j], params);
			}
			else if (i == rows - 1 && j + 1 < cols)
				draw_line(map[i][j], map[i][j + 1], params);
			else if (j == cols - 1 && i + 1 < rows)
				draw_line(map[i][j], map[i + 1][j], params);
			if (i > 0 && j < cols - 1)
				draw_line(map[i][j], map[i - 1][j + 1], params);
			j++;
		}
		i++;
	}
}
