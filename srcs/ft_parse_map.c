/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 12:30:15 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/21 12:37:24 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	parse_and_fill(int map_dims[2], t_coords **map, int sq_size, char *file)
{
	int	i;

	i = 0;
	while (i < map_dims[1])
	{
		map[i] = malloc(sizeof(t_coords) * (map_dims[0] + 1));
		i++;
	}
	map[i] = 0;
	fill_rows(map, file, map_dims[0], sq_size);
}

void	fill_rows(t_coords **map, char *file, int cols, int square_size)
{
	int		fd;
	char	*row;
	char	*aux;
	int		space;
	int		i;
	int		j;

	space = 1;
	i = 0;
	fd = open(file, O_RDONLY);
	row = get_next_line(fd);
	while (row)
	{
		aux = row;
		j = 0;
		while (*aux)
		{
			if ((ft_is_space(*aux) == 0 && space == 1) || j == 0)
			{
				space = 0;
				map[i][j] = create_coords(i, j, ft_atoi(aux), square_size);
				j++;
			}
			else if (ft_memcmp(aux, ",0x", 3) == 0 && j > 0)
				map[i][j - 1].colors = hex_to_int(aux + 3);
			else if (ft_is_space(*aux))
				space = 1;
			aux++;
		}
		free(row);
		row = get_next_line(fd);
		i++;
	}
	free(row);
	close(fd);
}

t_coords	create_coords(int i, int j, int z, int square_size)
{
	t_coords	co;

	co.x = (i * square_size + j * square_size);
	co.z = z * square_size;
	co.y = ((i * square_size - j * square_size) / 2) - co.z;
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

int	ft_is_space(char c)
{
	if (c == ' ' || c == 9 || c == 10 || c == 11 || c == 12 || c == 13)
		return (1);
	return (0);
}