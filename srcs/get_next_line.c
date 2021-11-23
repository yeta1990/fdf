/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 20:28:00 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/23 17:59:11 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char			*lft;
	static int			end;
	int					c;
	char				*last;

	c = 0;
	if (fd < 0 || read(fd, &end, 0) == -1 || 1000 <= 0)
		return (0);
	if (!lft)
		lft = (ft_first_read(fd, lft));
	if (!lft)
		return (0);
	if (ft_c(lft, 10) != -1)
		return (ft_create_line(&lft));
	c = ft_read_loop(fd, &lft);
	if (c > 0)
		return (get_next_line(fd));
	else if (c == 0 || (lft))
	{
		last = ft_strjoin("", lft);
		free(lft);
		lft = 0;
		return (last);
	}
	return (0);
}

char	*ft_create_line(char **lft)
{
	char	*line;
	char	*aux;

	line = ft_substr(*lft, 0, ft_c(*lft, 10));
	aux = ft_substr(*lft, ft_c(*lft, 10), ft_strlen(*lft) - ft_c(*lft, 10));
	free(*lft);
	*lft = aux;
	if (ft_strlen(*lft) == 0)
	{
		free(*lft);
		*lft = 0;
	}
	return (line);
}

char	*ft_first_read(int fd, char *lft)
{
	char	*buff;

	buff = malloc(sizeof(char) * (1000 + 1));
	if (!buff)
		return (0);
	ft_bzero(buff, 1000 + 1);
	if (read(fd, buff, 1000))
	{
		lft = ft_substr(buff, 0, 1000 + 1);
		free(buff);
		buff = 0;
		return (lft);
	}
	free(buff);
	return (0);
}

int	ft_read_loop(int fd, char **lft)
{
	char	*aux;
	char	*buff;
	int		j;

	j = -1;
	buff = malloc(sizeof(char) * (1000 + 1));
	if (!buff)
		return (0);
	ft_bzero(buff, 1000 + 1);
	while (read(fd, buff, 1000))
	{
		aux = ft_strjoin(*lft, buff);
		free(*lft);
		*lft = aux;
		if (ft_c(buff, '\n') != -1)
		{
			free(buff);
			return (1);
		}
		ft_bzero(buff, 1000 + 1);
		j = 0;
	}
	free(buff);
	return (j);
}

int	ft_c(const char *s, int c)
{
	size_t	i;
	char	*s2;

	i = 0;
	c = (char) c;
	s2 = (char *)s;
	while (s2[i])
	{
		if (s2[i] == c)
			return (i + 1);
		i++;
	}
	if (s2[i] == c)
		return (i + 1);
	return (-1);
}
