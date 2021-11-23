/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:41:31 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/23 16:32:12 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_map_cols(char *file, int *rows)
{
	int		fd;
	char	*row;
	char	*aux;
	int		cols[2];

	cols[0] = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		throw_parse_error(1);
	row = get_next_line(fd);
	while (row)
	{
		aux = row;
		cols[1] = cols_counter(row);
		if (cols[0] == 0)
			cols[0] = cols[1];
		else if (cols[0] != cols[1])
			throw_parse_error(2);
		free(aux);
		row = get_next_line(fd);
		(*rows)++;
	}
	close(fd);
	return (cols[0]);
}

int	cols_counter(char *row)
{
	int	num;
	int	cols;

	num = 0;
	cols = 0;
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

int	get_map_rows(char *file)
{
	int		rows;
	int		fd;
	char	*row;

	rows = 0;
	fd = open(file, O_RDONLY);
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

void	throw_parse_error(int n)
{
	if (n == 1)
	{
		perror("fdf: Error opening file");
		exit(errno);
	}
	else if (n == 2)
	{
		ft_putstr_fd("Found wrong line length. Exiting.\n", 2);
		exit(1);
	}
	else if (n == 3)
	{
		ft_putstr_fd("No data found.\n", 2);
		exit(1);
	}
}
