/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 20:28:00 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/22 19:40:32 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*buff;
	char	*line;
	char	*aux;

	line = 0;
	aux = 0;
	if (fd < 0 || read(fd, line, 0) == -1)
		return (0);
	buff = malloc(sizeof(char) * 2);
	while (ft_c(line, 10) == -1 && read(fd, buff, 1) > 0)
	{
		if (!line)
			line = ft_strjoin("", buff);
		else
		{
			aux = ft_strjoin(line, buff);
			free(line);
			line = aux;
		}
		ft_bzero(buff, 2);
	}
	free(buff);
	if (!line)
		return (0);
	return (line);
}

int	ft_c(const char *s, int c)
{
	size_t	i;
	char	*s2;

	if (!s)
		return (-1);
	i = 0;
	c = (char) c;
	s2 = (char *)s;
	while (s2 && s2[i])
	{
		if (s2[i] == c)
			return (i + 1);
		i++;
	}
	if (s2[i] == c)
		return (i + 1);
	return (-1);
}
