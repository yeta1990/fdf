/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:22:44 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/03 16:44:39 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct	s_params{
	void	*mlx;
	void	*mlx_window;
}				t_params;

int	byebye(void);
int	draw_other(int keycode, t_params *params);
int	mouse_win3(int x, int y, void *params);

int main(void)
{
	t_params	params;

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

	mlx_hook(params.mlx_window, 6, 1L<<6, mouse_win3, 0);
	mlx_key_hook(params.mlx_window, draw_other, &params);
	mlx_hook(params.mlx_window, 17, 0, byebye, &params);
	mlx_loop(params.mlx);

//	mlx_destroy_display(params.mlx);
	free(params.mlx);

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
		free(params->mlx);
		exit(0);
	}
	return (1);
}
