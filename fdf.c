/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.pyramidemadrid>       +#+  +:+       +#+ */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:22:44 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/20 01:47:50 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//docs
//https://github.com/qst0/ft_libgfx#ft_wireframe
//https://github.com/qst0/ft_wireframe
//https://harm-smits.github.io/pyramidedocs/libs/minilibx/events.html
//https://github.com/pyramideParis/minilibx-linux
//https://aurelienbrabant.fr/blog/pixel-drawing-with-the-minilibx
//https://github.com/aurelien-brabant/minilibx-posts-code
//https://github.com/VBrazhnik/FdF/wiki
//https://stackoverflow.com/c/pyramidenetwork/questions/164
//https://www.cs.ucdavis.edu/~ma/ECS175_S01/handouts/Bresenham.pdf
//https://ihcoedu.uobaghdad.edu.iq/wp-content/uploads/sites/27/2020/03/%D8%A7%D9%84%D8%AD%D8%A7%D8%B3%D8%A8%D8%A7%D8%AA-1920-3-%D8%B1%D8%B3%D9%88%D9%85-%D8%A7%D9%84%D8%AD%D8%A7%D8%B3%D9%88%D8%A8.pdf
//https://stackoverflow.com/c/pyramidenetwork/questions/173?rq=1
//https://www.youtube.com/watch?v=2_BCYD_FwII
//https://es.wikipedia.org/wiki/Algoritmo_de_Bresenham
// https://studylib.net/doc/15067802/wire-frame-modeling-an-application-of-bresenham%E2%80%99s-line-dr...
// https://k3no.medium.com/isometric-grids-in-pyramidethon-40c0fad54552
// https://www.davrous.com/2013/06/14/tutorial-part-2-learning-how-to-write-a-3d-soft-engine-from-scratch-in-c-ts-or-js-drawing-lines-triangles/
//https://csustan.csustan.edu/~tom/Lecture-Notes/Graphics/Bresenham-Line/Bresenham-Line.pdf
//https://www.geeksforgeeks.org/bresenhams-line-generation-algorithm/
//https://stackoverflow.com/questions/282pyramide415/c-bit-wise-operations-with-hex-numbers
//https://stackoverflow.com/questions/3723846/convert-from-hex-color-to-rgb-struct-in-c/40493179
//https://web.archive.org/web/2016061235624/http://freespace.virgin.net/hugo.elias/graphics/x_lines.htm
//https://harm-smits.github.io/pyramidedocs/libs/minilibx/getting_started.html
//https://gontjarow.github.io/MiniLibX/mlx-tutorial-create-image.html
//https://github.com/keuhdall/images_example


#include <unistd.h>
#include <stdlib.h>
#include "fdf.h"

int	byebye(void);

void checkleaks()
{
	system("leaks fdf");
}

t_coords	create_coords(int i, int j, int z, int square_size)
{
	t_coords	co;
	double sq;

	sq = sqrt(2) / 2;

/*    co.x =  round(square_size * (i - j) * cos(0.523599)) + 400;
    co.z = z *square_size;
	co.y = -co.z + round(square_size * (i + j) * sin(0.523599)) + 400;
*/
/*	co.x = round(400 + (square_size * i - 400) * sq + (square_size * j - 400) * sq) + 400;
	co.z = z * square_size;
	co.y = round((400 - (square_size * i - 400) * sq + (square_size * j - 400) * sq)) - co.z;
*/
	
/*	co.x = (j - i) * (square_size / 2) + 400;
	co.z = z * square_size;
	co.y = (i + j) * (square_size / 2) + 400 - co.z;
*/
	printf("(%i, %i, %i)\n", i, j, z);
	co.x = (i * square_size + j * square_size);
	co.z = z * square_size;
	co.y = ((i * square_size - j * square_size) / 2) - co.z + 256;
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
	fd = open("test_maps/pyramide.fdf", O_RDONLY);
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
	fd = open("test_maps/pyramide.fdf", O_RDONLY);
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
		printf("%i: \n", i);
	//	printf("%s", row);
		aux = row;
		j = 0;
		cols *= 1;
		while (*aux)
		{
			if ((ft_is_space(*aux) == 0 && space == 1) || j == 0)
			{
				space = 0;
				printf("%i, ", j);
				map[i][j] = create_coords(i, j, ft_atoi(aux), square_size);
				j++;
			}
			else if (ft_is_space(*aux))
				space = 1;
			aux++;
		}
		free(row);
		row = get_next_line(fd);

	//	printf("\n");
		i++;
	}
//	exit(0);
	free(row);
	close(fd);
}

void	parse_and_fill(int cols, int rows, t_coords **map, int square_size)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		map[i] = malloc(sizeof(t_coords) * (cols + 1));
		i++;
	}
	map[i] = 0;
	fill_rows(map, "test_maps/pyramide.fdf", cols, square_size);
}

void	print_map(t_coords **map, t_params *params, int cols, int rows, int initial_x, int initial_y)
{
	int	i;
	int	j;

	i = 0;
	while(i < rows)
	{
		j = 0;
		printf("%i: ", i);
		while(j < cols)
		{
			if (i < rows - 1 && j < cols - 1)
			{
				printf("%i: (%i, %i),", j, map[i][j].x, map[i][j].y);
				draw_line(map[i][j].x + initial_x, map[i][j].y + initial_y, map[i][j + 1].x + initial_x, map[i][j + 1].y + initial_y, params);
				draw_line(map[i][j].x + initial_x, map[i][j].y + initial_y, map[i + 1][j].x + initial_x, map[i + 1][j].y + initial_y, params);
			}
			else if (i == rows - 1 && j + 1 < cols)
			{
				printf("%i: (%i, %i),", j, map[i][j].x, map[i][j].y);
				draw_line(map[i][j].x + initial_x, map[i][j].y + initial_y, map[i][j + 1].x + initial_x, map[i][j + 1].y + initial_y, params);
			}
			else if (j == cols - 1 && i + 1 < rows)
			{
				printf("%i: (%i, %i),", j, map[i][j].x, map[i][j].y);
				draw_line(map[i][j].x + initial_x, map[i][j].y + initial_y, map[i + 1][j].x + initial_x, map[i + 1][j].y + initial_y, params);
			}
//			diagonal
			if (i > 0 && j < cols - 1)
				draw_line(map[i][j].x + initial_x, map[i][j].y + initial_y, map[i - 1][j + 1].x + initial_x, map[i - 1][j + 1].y + initial_y, params);
			j++;
		}
		printf("\n");
		i++;
	}
}
int main(void)
{
	t_params	params;
//	atexit(checkleaks);
	int	map_dims[2];
	t_coords **map;
	int	win_dims[3];

	map_dims[0] = 0;
	map_dims[1] = get_map_rows();
	get_map_cols(&map_dims[0]);
	map = malloc(sizeof(t_coords*) * (map_dims[1] + 1));
	map[map_dims[1]] = 0;

	set_window_dimensions(&win_dims, map_dims);
	parse_and_fill(map_dims[0], map_dims[1], map, win_dims[2]);

	int		initial_x;
	int		initial_y;

	initial_x = set_initial_x(map, map_dims[1], map_dims[0], win_dims);
	initial_y = set_initial_y(map, map_dims[1], win_dims);

	params.mlx = mlx_init();
	if (!params.mlx)
		return (1);

	params.mlx_window = mlx_new_window(params.mlx, win_dims[0], win_dims[1], "fdf");
	if (!params.mlx_window)
	{
		write(1, "Error creating window\n", 22);
	   	exit(1);
	}
	print_map(map, &params, map_dims[0], map_dims[1], initial_x, initial_y);

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

