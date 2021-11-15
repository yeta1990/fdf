/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line1.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:20:48 by potero-d          #+#    #+#             */
/*   Updated: 2021/11/15 15:59:47 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
#include <unistd.h>
//#include <fcntl.h>
#include <stdlib.h>

char	*get_next_line(int fd);
size_t  ft_strlen(const char *str);
char    *ft_substr(char const *s, int star, size_t len);
void    *ft_calloc(size_t count, size_t size);
char    *ft_strjoin(char const *s1, char const *s2);

#endif
