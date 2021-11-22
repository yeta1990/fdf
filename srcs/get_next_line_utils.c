/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 19:30:47 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/22 19:41:23 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (NULL);
	ft_memmove(s3, (char *)s1, ft_strlen(s1));
	ft_memmove(s3 + ft_strlen(s1), (char *)s2, ft_strlen(s2));
	s3[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (s3);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*d;
	char	*s;

	s = (char *) src;
	d = (char *) dst;
	i = 0;
	if (!s && !d && len > 0)
		return (dst);
	if (d > s)
	{
		while (len > 0)
		{
			len--;
			d[len] = s[len];
		}
		return (dst);
	}
	while (i < len)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

void	ft_bzero(void *s, unsigned long n)
{
	unsigned long	i;
	char			*str;

	str = (char *) s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}
