/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:09:43 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/12 12:31:07 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

typedef struct	s_coords{
	int	x;
	int	y;
	int	z;
	int	color;
}				t_coords;

# include <fcntl.h>
# include "get_next_line.h"

int	ft_atoi(const char *str);

#endif
