/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:22:44 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/05 17:13:32 by albgarci         ###   ########.fr       */
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

#include "mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
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

int main(void)
{
	t_params	params;
	
//	atexit(checkleaks);
	params.mlx = mlx_init();
	if (!params.mlx)
		return (1);
	params.mlx_window = mlx_new_window(params.mlx, 400, 400, "Pepe");
	if (!params.mlx_window)
	{
		write(1, "Error creating window\n", 22);
	   	exit(1);
	}
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
	
	//wait for "esc" key

	mlx_hook(params.mlx_window, 6, (1L<<6), mouse_win3, 0);
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
