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

    joined = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
    if (!joined)
        return (get_free(&joined, NULL));
    temp = joined;
    while (*str1)
        *temp++ = *str1++;
    while (*str2)
        *temp++ = *str2++;
    *temp = '\0';
    return (joined);
}

char *append(char *buffer, char *str)
{
    char *new_buf;
    
    new_buf = strjoin(buffer, str);
    if(!new_buf)
        return (NULL);
    get_free(&buffer, NULL);
    return (new_buf);
}

char *extract_line(char *buffer) 
{    
	int line_size;
	char *temp;

	if (buffer[0] == '\0') 
        return NULL;
    line_size = 0;
    while (buffer[line_size] && buffer[line_size] != '\n')
        line_size++;
    if (buffer[line_size] == '\n') 
        line_size++;  // Include the newline character in the extracted line
    char *line = malloc(sizeof(char) * (line_size + 1));
    if (!line) 	
        return NULL;  // Memory allocation failed
    temp = line;
    while (0 < line_size--) 
        *temp++ = *buffer++;
    *temp = '\0';  // Null-terminate the string
    return (line);
}

char	*update_storage(char *buffer)
{
	char	*ptr_newline;
	char	*rest_line;
	int		line_size;
	char    *temp;

	ptr_newline = ft_strchr(buffer, '\n');
	if (!ptr_newline)
	{
		return (get_free(&buffer, NULL));
	}
	line_size = ft_strlen(ptr_newline) - 1;
	rest_line = calloc(sizeof(char), (line_size + 1));
	if (!rest_line)
	{
		get_free(&buffer, NULL);
	}
    temp = rest_line;
	while (0 < line_size--)
		*temp++ = *++ptr_newline;
	*temp = '\0';
	free (buffer);
	buffer = rest_line;
	return (buffer);
}

char *read_from_file(int fd, char *buffer)
{
    char *r_buffer;
 //to check if read function works correctly
    int  bytes_nbr;
//memory allocation for readtime buffer
    r_buffer = calloc(BUFFER_SIZE, sizeof(char) + 1);
    if (!r_buffer) //error alloc
        return (NULL);
    while (1) //endless loop
    {
        bytes_nbr = read(fd, r_buffer, BUFFER_SIZE);
        if (bytes_nbr == -1)
        {
            return (get_free(&r_buffer, NULL));
            //r_buffer = NULL;
            //return (NULL);
        }
        r_buffer[bytes_nbr] = '\0';
        buffer = append(buffer, r_buffer);
        if (ft_strchr(buffer, '\n') || bytes_nbr == 0)
            break ;
 }
 free (r_buffer);
 return (buffer);
}
