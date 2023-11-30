/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <emikhayl@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 18:01:57 by emikhayl          #+#    #+#             */
/*   Updated: 2023/11/29 20:12:15 by emikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

size_t ft_strlen(char *str)
{
    size_t len;
    len = 0;
    while(*str++)
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

char *strjoin(char *str1, char *str2)
{
    char *joined;
    char *temp;

    joined = calloc(sizeof(char),(ft_strlen(str1) + ft_strlen(str2) + 1));
    if (!joined)
        return (get_free(&joined));
    temp = joined;
    while (*str1)
        *temp++ = *str1++;
    while (*str2)
        *temp++ = *str2++;
    //*temp = '\0';
    return (joined);
}

char *append(char *buffer, char *str)
{
    char *new_buf;
    
    new_buf = strjoin(buffer, str);
    if(!new_buf)
        return (NULL);
    get_free(&buffer);
    return (new_buf);
}

void *ft_calloc(size_t count, size_t size)
{
    void *ptr;

    ptr = malloc(count * size);
    if (!ptr)
        return NULL;
    size_t i = 0;
    while (i < count * size)
    {
        *((char *)ptr + i) = 0;
        i++;
    }

    return ptr;
}
/*
void
	ft_bzero(void *s, size_t n)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (i < n)
	{
		*(char*)(s + i) = 0;
		i++;
	}
}*/