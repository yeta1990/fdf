/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_to_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 14:00:20 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/21 12:28:07 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_colors	hex_to_int(char *str)
{
	int			i;
	t_colors	cl;

	i = hex_map_checker(str);
	cl.r = 0;
	cl.g = 0;
	if (i == 2)
		cl.b = hex_decimal_converter(str[0], str[1]);
	else if (i == 4)
	{
		cl.g = hex_decimal_converter(str[0], str[1]);
		cl.b = hex_decimal_converter(str[2], str[3]);
	}
	else if (i == 6)
	{
		cl.r = hex_decimal_converter(str[0], str[1]);
		cl.g = hex_decimal_converter(str[2], str[3]);
		cl.b = hex_decimal_converter(str[4], str[5]);
	}
	cl.rgb = ((cl.r << 16) | (cl.g << 8) | cl.b);
	return (cl);
}

int	hex_map_checker(char *str)
{
	int	i;

	i = 0;
	while (char_in_hex(str[i]))
		i++;
	if (i != 2 && i != 4 && i != 6)
	{
		ft_putstr_fd("Invalid map: hex color error12\n", 2);
		exit(1);
	}
	return (i);
}

int	char_in_hex(char c)
{
	char	*base;
	int		i;

	i = 0;
	base = "0123456789ABCDEF";
	while (base[i])
	{
		if (ft_toupper(c) == base[i])
			return (1);
		i++;
	}
	return (0);
}

int	char_pos(char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == ft_toupper(c))
			return (i);
		i++;
	}
	return (-1);
}

int	hex_decimal_converter(char a, char b)
{
	int		num;
	char	*base;

	base = "0123456789ABCDEF";
	num = char_pos(base, ft_toupper(b)) + (char_pos(base, ft_toupper(a)) * 16);
	return (num);
}
