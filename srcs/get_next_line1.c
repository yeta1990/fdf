/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 11:22:42 by potero            #+#    #+#             */
/*   Updated: 2021/10/20 13:26:59 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

char	*get_next_line(int fd)
{
	char	*buff;
	char	*print;
	char	*aux;
	char	*aux2;
	size_t	i;
	static char	*rest;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buff = ft_calloc_bzero(1, (BUFFER_SIZE + 1));
 	read(fd, buff, BUFFER_SIZE);
	if (rest != 0)
	{
		aux = buff;
		buff = ft_strjoin(rest, aux);
		free(rest);
		free(aux);
	}
	if (ft_strlen(buff) == 0)
	{
		free(buff);
		return (0);
	}
	print = ft_calloc_bzero(1, 1);
	i = 0;
	while (buff[i] != '\n')
	{
	 	if (i == ft_strlen(buff) - 1)
		{
			aux = print;
			print = ft_strjoin(aux, buff);
			free(aux);
			free(buff);
			buff = ft_calloc_bzero(1, (BUFFER_SIZE + 1));
			read(fd, buff, BUFFER_SIZE);
			if (ft_strlen(buff) == 0)
				break;
			i = -1;
		}
		i++;
	}
	aux2 = ft_substr(buff, 0, i + 1);
	aux = ft_strjoin(print, aux2);
	free(aux2);
	free(print);
	if (BUFFER_SIZE > 1)
		rest = ft_substr(buff, i + 1, ft_strlen(buff) - i + 1);
	free(buff);
	return (aux);
}
