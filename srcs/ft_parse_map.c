/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 12:30:15 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/23 13:45:46 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coords	**assign_memory(int map_dims[2])
{
	int			i;
	t_coords	**map;

	i = 0;
	map = malloc(sizeof(t_coords *) * (map_dims[1] + 1));
	map[map_dims[1]] = 0;
	while (i < map_dims[1])
	{
		map[i] = malloc(sizeof(t_coords) * (map_dims[0] + 1));
		i++;
	}
	map[i] = 0;
	return (map);
}

void	fill_rows(t_coords **map, char *file, int square_size, int z_len)
{
	int		fd;
	char	*row;
	int		i;
	char	*aux_row;

	i = 0;
	fd = open(file, O_RDONLY);
	row = get_next_line(fd);
	while (row)
	{
		aux_row = row;
		parse_one_row(aux_row, &map, square_size, z_len);
		free(row);
		row = get_next_line(fd);
		i++;
	}
	free(row);
	close(fd);
}

void	parse_one_row(char *row, t_coords ***map, int s, int z_l)
{
	int			j;
	int			space;
	static int	i;

	space = 1;
	j = 0;
	while (*row)
	{
		if ((ft_is_space(*row) == 0 && space == 1) || j == 0)
		{
			space = 0;
			if (z_l != 0)
				(*map)[i][j] = create_coords(i * s, j * s, ft_atoi(row) * z_l);
			else
				(*map)[i][j] = create_coords(i * s, j * s, ft_atoi(row) * s);
			j++;
		}
		else if (ft_memcmp(row, ",0x", 3) == 0 && j > 0)
			(*map)[i][j - 1].colors = hex_to_int(row + 3);
		else if (ft_is_space(*row))
			space = 1;
		row++;
	}
	i++;
}

t_coords	create_coords(int i, int j, int z)
{
	t_coords	co;

	co.x = (i + j);
	co.z = z;
	co.y = ((i - j) / 2) - co.z;
	co.colors = hex_to_int("FFFFFF");
	return (co);
}

void	center_map(t_coords **map, int rows, int cols, int win_dims[2])
{
	int	i;
	int	j;
	int	initial_x;
	int	initial_y;

	i = 0;
	initial_x = set_initial_x(map, rows, cols, win_dims);
	initial_y = set_initial_y(map, rows, win_dims);
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			map[i][j].x += initial_x;
			map[i][j].y += initial_y;
			j++;
		}
		i++;
	}
}
