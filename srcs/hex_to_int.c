/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_to_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 14:00:20 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/20 18:41:33 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_colors	hex_to_int(char *str)
{
	int		i;
	t_colors cl;

	i = 0;
	while (char_in_hex(str[i]))
		i++;
	if (i != 6)
	{
		ft_putstr_fd("Invalid map: hex color error\n", 2);
		exit(1);
	}
	cl.r = hex_decimal_converter(str[0], str[1]);
	cl.g = hex_decimal_converter(str[2], str[3]);
	cl.b = hex_decimal_converter(str[4], str[5]);
	cl.rgb = ((cl.r << 8) | (cl.g << 4) | cl.b);
	printf("color: %i, %i, %i\n", cl.r, cl.g, cl.b);
	return (cl);
}

int	char_in_hex(char c)
{
	char	*base;
	int		i;

	i = 0;
	base = malloc(sizeof(char) * 17);
	base = "0123456789ABCDEF";
	while (base[i])
	{
		if (ft_toupper(c) == base[i])
			return (1);
		i++;
	}
//	free(base);
	return (0);
}

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c = c - 32;
	return (c);
}

int	char_position(char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	hex_decimal_converter(char a, char b)
{
	int		num;
	char	*base;

	base = malloc(sizeof(char) * 17);
	base = "0123456789ABCDEF";
	num = char_position(base, ft_toupper(b)) + (char_position(base, ft_toupper(a)) * 16);	
	return (num);
}
