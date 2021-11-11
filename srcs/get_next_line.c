/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 20:28:00 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/12 00:06:41 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char			*lft;

	if (fd < 0 || read(fd, lft, 0) == -1)
		return (0);
	return (ft_read_loop(fd, &lft));
}

char	*ft_create_line(char **lft)
{
	char	*line;
	char	*aux;
	int		appear;

	appear = ft_c(*lft, 10);
	if (appear)
	{
		line = ft_substr(*lft, 0, appear);
		aux = ft_substr(*lft, appear, ft_strlen(*lft) - appear);
	}
	else
		return (*lft);
	if (*lft)
		free(*lft);
	*lft = aux;
	return (line);
}

char *ft_read_loop(int fd, char **lft)
{
	char		*aux;
	char		*buff;
	static int	end;

	buff = malloc(sizeof(char) * (1 + 1));
	if (!buff)
		return (0);
	ft_bzero(buff, 1 + 1);
	if (!(*lft))
		*lft = malloc(1);
	while (read(fd, buff, 1))
	{
		aux = ft_strjoin(*lft, buff);
		free(*lft);
		*lft = aux;
		if (ft_c(buff, '\n') != -1)
		{
			free(buff);
			return (ft_create_line(lft));
		}
		ft_bzero(buff, 1 + 1);
	}

	if (*lft && ft_strlen(*lft))
	{
		free(buff);
		return (ft_create_line(lft));
	}
	free(buff);
	if (!end)
	{
		end = 1;
		free(*lft);
	}
	return (0);
}

int	ft_c(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return (i + 1);
		i++;
	}
	return (-1);
}
