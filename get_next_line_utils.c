/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <emikhayl@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 18:01:57 by emikhayl          #+#    #+#             */
/*   Updated: 2023/11/14 22:24:49 by emikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

int ft_strlen(char *str)
{
    int len;

    len = 0;
    while (*str)
    {
        len++;
        str++;
    }
    return (len);
}

char    *ft_strjoin(char *s1, char *s2)
{

    char    *joined;
    size_t  i;
    size_t  j;

    joined = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    i = 0;
    j = 0;
    if (joined == NULL)
        return (NULL);
    while (s1[i])
    {
        joined[j++] = s1[i++];
    }
    i = 0;
    while (s2[i])
    {
        joined[j++] = s2[i++];
    }
    joined[j] = '\0';
    return (joined);
}

char	*ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	if ((char)c == '\0')
	{
		return ((char *)s);
	}
	return (NULL);
}



char *append_buffer(char *basin_buffer, char *read_buffer)
{
 char *temp;

 temp = ft_strjoin(basin_buffer, read_buffer);
 free(basin_buffer);
 return (temp);
}

char	*extract_line(char *storage)
{
	int		size_line;
	char	*line_return;
	int		i;

	i = 0;
	size_line = 0;
	if (storage[0] == '\0')
		return (NULL);
	while (storage[size_line] && storage[size_line] != '\n')
		size_line++;
	if (storage[size_line] == '\n')
		size_line++;
	line_return = (char *) malloc((size_line + 1) * sizeof(char));
	if (!line_return)
		return (NULL);
	i = 0;
	while (i < size_line)
	{
		line_return[i] = storage[i];
		i++;
	}
	line_return[i] = '\0';
	return (line_return);
}

char	*update_storage(char *storage)
{
	char	*ptr_newline;
	char	*rest_of_line;
	int		size_rest_of_line;
	int		i;

	ptr_newline = ft_strchr(storage, '\n');
	if (!ptr_newline)
	{
		free(storage);
		return (NULL);
	}
	size_rest_of_line = ft_strlen(ptr_newline + 1);
	rest_of_line = (char *) malloc(size_rest_of_line * sizeof(char) + 1);
	if (!rest_of_line)
	{
		free(storage);
		return (NULL);
	}
	i = -1;
	while (++i < size_rest_of_line)
		rest_of_line[i] = ptr_newline[i + 1];
	rest_of_line[i] = '\0';
	free (storage);
	storage = rest_of_line;
	return (storage);
}