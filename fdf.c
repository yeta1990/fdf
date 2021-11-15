/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:22:44 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/15 17:59:26 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//docs
//https://github.com/qst0/ft_libgfx#ft_wireframe
//https://github.com/qst0/ft_wireframe
//https://harm-smits.github.io/42docs/libs/minilibx/events.html
//https://github.com/42Paris/minilibx-linux
//https://aurelienbrabant.fr/blog/pixel-drawing-with-the-minilibx
//https://github.com/aurelien-brabant/minilibx-posts-code
//https://github.com/VBrazhnik/FdF/wiki
//https://stackoverflow.com/c/42network/questions/164
//https://www.cs.ucdavis.edu/~ma/ECS175_S01/handouts/Bresenham.pdf
//https://ihcoedu.uobaghdad.edu.iq/wp-content/uploads/sites/27/2020/03/%D8%A7%D9%84%D8%AD%D8%A7%D8%B3%D8%A8%D8%A7%D8%AA-1920-3-%D8%B1%D8%B3%D9%88%D9%85-%D8%A7%D9%84%D8%AD%D8%A7%D8%B3%D9%88%D8%A8.pdf
//https://stackoverflow.com/c/42network/questions/173?rq=1
//https://www.youtube.com/watch?v=2_BCYD_FwII
//https://es.wikipedia.org/wiki/Algoritmo_de_Bresenham
// https://studylib.net/doc/15067802/wire-frame-modeling-an-application-of-bresenham%E2%80%99s-line-dr...
// https://k3no.medium.com/isometric-grids-in-python-40c0fad54552
// https://www.davrous.com/2013/06/14/tutorial-part-2-learning-how-to-write-a-3d-soft-engine-from-scratch-in-c-ts-or-js-drawing-lines-triangles/
//https://csustan.csustan.edu/~tom/Lecture-Notes/Graphics/Bresenham-Line/Bresenham-Line.pdf
//https://www.geeksforgeeks.org/bresenhams-line-generation-algorithm/
//https://stackoverflow.com/questions/28242415/c-bit-wise-operations-with-hex-numbers
//https://stackoverflow.com/questions/3723846/convert-from-hex-color-to-rgb-struct-in-c/40493179
//https://web.archive.org/web/20160311235624/http://freespace.virgin.net/hugo.elias/graphics/x_lines.htm

#include <unistd.h>
#include <stdlib.h>
#include "fdf.h"

int	byebye(void);

void checkleaks()
{
	system("leaks fdf");
}

t_coords	create_coords(int i, int j, int z)
{
	t_coords	co;

	co.x = (i * 15 + j * 15);
	co.z = z * 15;
	co.y = ((i * 15 - j * 15) / 2) + 325 - co.z;
	return (co);
}

static int	ft_is_space(char c)
{
	if (c == ' ' || c == 9 || c == 10 || c == 11 || c == 12 || c == 13)
		return (1);
	return (0);
}

void	get_map_cols(int *cols)
{
	int		num;
	int		fd;
	char	*row;
	char	*aux;

	num = 0;
	fd = open("test_maps/42.fdf", O_RDONLY);
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

int	get_map_rows(void)
{
	int		rows;
	int		fd;
	char	*row;

	rows = 0;
	fd = open("test_maps/42.fdf", O_RDONLY);
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

void	fill_rows(t_coords **map, char *file)
{
	int		fd;
	char	*row;
	char	*aux;
	int		space;
	int		i;
	int		j;


	space = 0;
	i = 0;
	fd = open(file, O_RDONLY);
	row = get_next_line(fd);
	while (row)
	{
		aux = row;
		j = 0;
		while (aux && *aux)
		{
			if (j == 0 || (ft_is_space(*aux) && space == 0))
			{
				space = 1;
				map[i][j] = create_coords(i, j, ft_atoi(aux));
				j++;
			}
			else
				space = 0;
			aux++;
		}
		free(row);
		row = get_next_line(fd);
		i++;
	}
	free(row);
	close(fd);

	
}

void	parse_and_fill(int cols, int rows, t_coords **map)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		map[i] = malloc(sizeof(t_coords) * (cols + 1));
		i++;
	}
	map[i] = 0;
	fill_rows(map, "test_maps/42.fdf");
}

void	print_map(t_coords **map, t_params *params, int cols, int rows, int initial_x)
{
	int	i;
	int	j;

	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j].x)
		{
			printf("(%i, %i, %i),", map[i][j].x, map[i][j].y, map[i][j].z);
			if (i + 1 < rows && j + 1 < cols)
			{
				draw_line(map[i][j].x + initial_x, map[i][j].y, map[i][j + 1].x + initial_x, map[i][j + 1].y, params);
				draw_line(map[i][j].x + initial_x, map[i][j].y, map[i + 1][j].x + initial_x, map[i + 1][j].y, params);
			}
			else if (i == rows - 1 && j + 1 < cols)
				draw_line(map[i][j].x + initial_x, map[i][j].y, map[i][j + 1].x + initial_x, map[i][j + 1].y, params);
			else if (j == cols - 1 && i + 1 < rows)
				draw_line(map[i][j].x + initial_x, map[i][j].y, map[i + 1][j].x + initial_x, map[i + 1][j].y, params);
//			diagonal
//			if (i > 0)
//				draw_line(map[i][j].x, map[i][j].y, map[i - 1][j + 1].x, map[i - 1][j + 1].y, params);
			j++;
		}
		i++;
	}
}
int main(void)
{
	t_params	params;
//	atexit(checkleaks);
	int	map_dims[2];
	t_coords **map;
	int	win_dims[2];

	map_dims[0] = 0;
	map_dims[1] = get_map_rows();
	get_map_cols(&map_dims[0]);
	map = malloc(sizeof(t_coords*) * (map_dims[1] + 1));
	map[map_dims[1]] = 0;

	set_window_dimensions(&win_dims, map_dims);
//	printf("cols: %i", cols);
//	printf(" rows: %i\n", rows);
	parse_and_fill(map_dims[0], map_dims[1], map);

	int		initial_x;
//	int		initial_y;

	initial_x = set_initial_x(map, map_dims[1], map_dims[0], win_dims);

	params.mlx = mlx_init();
	if (!params.mlx)
		return (1);

	params.mlx_window = mlx_new_window(params.mlx, win_dims[0], win_dims[1], "Pepe");
//	params.mlx_window = mlx_new_window(params.mlx, 530, 410, "Pepe");
	if (!params.mlx_window)
	{
		write(1, "Error creating window\n", 22);
	   	exit(1);
	}
	print_map(map, &params, map_dims[0], map_dims[1], initial_x);

//	mlx_string_put(params.mlx, params.mlx_window, 10, 10, 16409700, "holaaaa");
	//wait for "esc" key

//	mlx_hook(params.mlx_window, 6, (1L<<6), mouse_win3, 0);
	mlx_key_hook(params.mlx_window, window_close_destroy, &params);
	mlx_hook(params.mlx_window, 17, (1L<<17), byebye, &params);
	mlx_loop(params.mlx);
//	mlx_destroy_window(params->mlx, params->mlx_window);
//	mlx_destroy_display(params.mlx);
//	mlx_destroy_display(params.mlx);
	free_mlx_ptr(params.mlx);
//	free(params.mlx);
}

int	byebye(void)
{
	exit(0);
}

