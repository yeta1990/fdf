/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:22:44 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/11 20:38:51 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//docs
//https://github.com/qst0/ft_libgfx#ft_wireframe
//https://github.com/qst0/ft_wireframe
//https://harm-smits.github.io/42docs/libs/minilibx/events.html
//https://github.com/42Paris/minilibx-linux
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

#include "mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "fdf.h"
#include "get_next_line.h"

//#include "mlx_int.h"

typedef struct	s_params{
	void	*mlx;
	void	*mlx_window;
}				t_params;

int	byebye(void);
int	draw_other(int keycode, t_params *params);
int	mouse_win3(int x, int y, void *params);

void	free_mlx_ptr(void *mlx);

void checkleaks()
{
	system("leaks fdf");
}

t_coords	create_coords(int x, int y, int z)
{
	t_coords	co;
	
	co.x = x;
	co.y = y;
	co.z = z;
	return (co);
}


void	draw_line(int x0, int y0, int x1, int y1, t_params params)
{
	int	dx;
	int	dy;
	int	stepx;
	int	stepy;
	int	fraction;

	dx = x1 - x0;
	dy = y1 - y0;
	if (dy < 0)
	{
		dy = dy * -1;
		stepy = -1;
	}
	else
		stepy = 1;
	if (dx < 0)
	{
		dx = dx * -1;
		stepx = -1;
	}
	else
		stepx = 1;
	dy = dy * 2;
	dx = dx * 2;
	if ((0 <= x0) && (x0 < 600) && (0 <= y0) && (y0 < 600))
		mlx_pixel_put(params.mlx, params.mlx_window, x0, y0, 16409700);
	if (dx > dy)
	{
		fraction = dy - (dx / 2);
		while (x0 != x1)
		{
			x0 += stepx;
			if (fraction >= 0)
			{
				y0 += stepy;
				fraction -= dx;
			}
			fraction += dy;
			if ((0 <= x0) && (x0 < 600) && (0 <= y0) && (y0 < 600))
				mlx_pixel_put(params.mlx, params.mlx_window, x0, y0, 16409700);
		}
	}
	else
	{
		fraction = dx - (dy / 2);
		while (y0 != y1)
		{
			if (fraction >= 0)
			{
				x0 += stepx;
				fraction -= dy;
			}
			y0 += stepy;
			fraction += dx;
			if ((0 <= x0) && (x0 < 600) && (0 <= y0) && (y0 < 600))
				mlx_pixel_put(params.mlx, params.mlx_window, x0, y0, 16409700);
		}
	}
}

static int	ft_is_space(char c)
{
	if (c == ' ' || c == 9 || c == 10 || c == 11 || c == 12 || c == 13)
		return (1);
	return (0);
}

int	get_map_cols(char *row)
{
	int	cols;
	int	i;
	int	num;

	num = 0;
	cols = 0;
	i = 0;
	while (row && *row)
	{
		if (ft_is_space(*row) == 0)
		{
			if (num == 0)
			{
				num = 1;
				cols++;
			}
		}
		else
			num = 0;
		row++;
	}
	return (cols);
}

int	get_map_rows(void)
{
	int	rows;
	int	file;

	rows = 0;
	file = open("test_maps/42.fdf", O_RDONLY);
	while (get_next_line(file) != 0)
	{
		printf("%i, ", rows);
		rows++;
	}
	close(file);
	return (rows);
}


int main(void)
{
	t_params	params;
//	atexit(checkleaks);
//	t_coords **map;
//	map = malloc(sizeof(t_coords) * );
	int		file;
	char	*row;
	int		cols;
	int		rows;

//	rows = 3;
	rows = get_map_rows();
	file = open("test_maps/42.fdf", O_RDONLY);
//	file = open("test_maps/pentenegpos.fdf", O_RDONLY);
	row = get_next_line(file);
	cols = get_map_cols(row);
	close(file);
	
//	t_coords **map;

//	map = malloc(sizeof(t_coords*) * (rows + 1));
	//	map[rows] = 0;
	
/*	int	mm;

	mm = 0;
	while (map[mm])
	{
		map[mm] = malloc(sizeof(t_coords) * (cols + 1));
		mm++;
	}
	map[mm] = 0;
*/
//	fill_rows(map, "test_maps/42.fdf");
	
	printf("cols: %i\n", cols);
	params.mlx = mlx_init();
	if (!params.mlx)
		return (1);
	params.mlx_window = mlx_new_window(params.mlx, 1200, 1200, "Pepe");
	if (!params.mlx_window)
	{
		write(1, "Error creating window\n", 22);
	   	exit(1);
	}

	t_coords	*c;
	int			z;
	int			i;
	int			j;

	i = 0;
	z = 0;
	c = malloc(sizeof(t_coords) * 4);
//	c[25] = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 2)
		{
			c[z] = create_coords((i * 10 - j * 10) + 50, ((i*10 + j*10) / 2) + 50, 0);
			j++;
			z++;
		}
		i++;
	}
	draw_line(500, 500, 400, 550, params);
	draw_line(500, 500, 600, 550, params);
	draw_line(500, 600, 600, 550, params);
	draw_line(500, 600, 400, 550, params);

	z = 0;
	while (z < 4)
	{
		printf("%d, %d\n", c[z].x, c[z].y);
		z++;
	}

/*	
	int	i;
	i = 0;
	while (i < 50)
	{
		mlx_pixel_put(params.mlx, params.mlx_window, 100, 100 + i, 16409700);
		i++;
	}
	i = 0;
	while (i < 25)
	{
		mlx_pixel_put(params.mlx, params.mlx_window, 100 + i, 100, 16409700);
		i++;
	}
	i = 0;
	while (i < 250)
	{
		mlx_pixel_put(params.mlx, params.mlx_window, 100 + i, 120 + 2*i, 16409700);
		i++;
	}
	i = 0;
	while (i < 21)
	{
		mlx_pixel_put(params.mlx, params.mlx_window, 125, 100 + i, 16409700);
		i++;
	}

	mlx_string_put(params.mlx, params.mlx_window, 10, 10, 16409700, "holaaaa");
*/	
	//wait for "esc" key

//	mlx_hook(params.mlx_window, 6, (1L<<6), mouse_win3, 0);
	mlx_key_hook(params.mlx_window, draw_other, &params);
	mlx_hook(params.mlx_window, 17, (1L<<17), byebye, &params);
	mlx_loop(params.mlx);
//	mlx_destroy_window(params->mlx, params->mlx_window);
//	mlx_destroy_display(params.mlx);
//	mlx_destroy_display(params.mlx);
	free_mlx_ptr(params.mlx);
//	free(params.mlx);

}

int	mouse_win3(int x, int y, void *p)
{
	printf("Mouse moving in Win3, at %dx%d.%p\n", x, y, p);
	return (1);
}


int	byebye(void)
{
	exit(0);
}

int	draw_other(int keycode, t_params *params)
{
	if (keycode == 53)
	{
		mlx_destroy_window(params->mlx, params->mlx_window);
	//	mlx_destroy_window(params.mlx, params.mlx_window);
		free_mlx_ptr(params->mlx);
		exit(0);
	}
	return (1);
}
