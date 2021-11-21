/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 11:19:47 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/21 11:19:49 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenGL/gl3.h>
#include <stdlib.h>
#include "mlx_int.h"

void	free_mlx_ptr(void *mlx)
{
	free(((mlx_ptr_t *)(mlx))->font->buffer);
	free(((mlx_ptr_t *)(mlx))->font);
	free(mlx);
}
