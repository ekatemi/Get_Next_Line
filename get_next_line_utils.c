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

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;

	ptr = (char *)malloc(count * size);
	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	if (ptr)
		ft_bzero (ptr, count * size);
	return (ptr);
}

void	*ft_memset(void *b, int c, size_t len)

{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (len--)
		*ptr++ = c;
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
/*
int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

char	*ft_strdup(char *s1)
{
	size_t			size;
	unsigned int	i;
	char			*copy;

	i = 0;
	size = ft_strlen(s1);
	copy = (char *)malloc(sizeof(char) * (size + 1));
	if (copy == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}




char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*joined;
	size_t	i;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joined = (char *)malloc(s1_len + s2_len + 1);
	i = 0;
	if (joined == NULL)
		return (NULL);
	while (*s1)
	{
		joined[i] = *s1++;
		i++;
	}
	while (*s2)
	{
		joined[i] = *s2++;
		i++;
	}
	joined[i] = '\0';
	return (joined);
}

char	*ft_strchr(const char *s, int c)
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
	return ((void *)0);
}*/
