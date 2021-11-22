/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+ */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:22:44 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/22 19:51:19 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "fdf.h"

int	main(int argc, char **argv)
{
	int			map_dims[2];
	t_coords	**map;
	int			win_dims[3];

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./fdf [map.fdf]\n", 2);
		exit(1);
	}
	map = 0;
	map_dims[0] = 0;
	map_dims[1] = get_map_rows(argv[1]);
	get_map_cols(&map_dims[0], argv[1]);
	set_window_dimensions(&win_dims, map_dims);
	map = assign_memory(map_dims);
	fill_rows(map, argv[1], win_dims[2]);
	center_map(map, map_dims[1], map_dims[0], win_dims);
	create_window_hooks(map, map_dims, win_dims);
	exit(0);
}

void	get_map_cols(int *cols, char *file)
{
	int		num;
	int		fd;
	char	*row;
	char	*aux;

	num = 0;
	fd = open(file, O_RDONLY);
	row = get_next_line(fd);
	aux = row;
	close(fd);
	while (row && *row)
	{
		if (ft_is_space(*row) == 0)
		{
			if (num == 0)
			{
				num = 1;
				(*cols)++;
			}
		}
		else
			num = 0;
		row++;
	}
	free(aux);
}

int	get_map_rows(char *file)
{
	int		rows;
	int		fd;
	char	*row;

	rows = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("fdf");
		exit(errno);
	}
	row = get_next_line(fd);
	while (row)
	{
		free(row);
		row = get_next_line(fd);
		rows++;
	}
	close(fd);
	return (rows);
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
