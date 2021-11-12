/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:44:56 by potero-d          #+#    #+#             */
/*   Updated: 2021/11/12 12:08:43 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*buff;
	char		*print;
	char		*aux;
	char		*aux2;
	size_t		j;
	size_t		i;

	if (fd < 0 || 1 <= 0)
		return (0);
	j = ft_strlen(rest);
	if (rest != 0 && j != 0)
	{
		buff = ft_substr(rest, 0, j + 1);
		free(rest);
	}
	else
	{
		free(rest);
		buff = ft_calloc(1, 1 + 1);
		read(fd, buff, 1);
	}
	j = ft_strlen(buff);
	if (j == 0)
	{
		free(buff);
		return (0);
	}
	print = ft_calloc(1, 1);
	i = 0;
	while (buff[i] != '\n')
	{
		if (i == j - 1)
		{
			aux = print;
			print = ft_strjoin(aux, buff);
			free(aux);
			free(buff);
			buff = ft_calloc(1, 1 + 1);
			read(fd, buff, 1);
			j = ft_strlen(buff);
			if (j == 0)
				break ;
			i = -1;
		}
		i++;
	}
	aux2 = ft_substr(buff, 0, i + 1);
	aux = print;
	print = ft_strjoin(aux, aux2);
	free(aux);
	free(aux2);
	if (1 > 1)
		rest = ft_substr(buff, i + 1, j - i);
	free(buff);
	return (print);
}
