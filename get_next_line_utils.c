/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <emikhayl@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 18:01:57 by emikhayl          #+#    #+#             */
/*   Updated: 2023/11/30 23:19:08 by emikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == '\0')
		return (NULL);
	return (&s[i]);
}

char	*ft_strjoin(char *buffer, char *str)
{
	char	*new_buf;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_buf = malloc(sizeof(char) * (ft_strlen(buffer) + ft_strlen(str) + 1));
	if (!new_buf)
		return (get_free(&buffer));
	while (buffer[i])
	{
		new_buf[i] = buffer[i];
		i++;
	}
	while (str[j])
		new_buf[i++] = str[j++];
	new_buf[i] = '\0';
	free(buffer);
	return (new_buf);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(sizeof(char) * (count * size));
	if (!ptr)
		return (NULL);
	while (i < count * size)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}
