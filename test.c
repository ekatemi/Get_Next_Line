/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <emikhayl@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:29:13 by emikhayl          #+#    #+#             */
/*   Updated: 2023/11/14 22:39:12 by emikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "get_next_line.h"

#define BUFFER_SIZE 10

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

char *append_buffer(char *persistent_buffer, char *read_buffer)
{
 char *temp;

 temp = ft_strjoin(persistent_buffer, read_buffer);
 free(persistent_buffer);
 
 return (temp);
}


char *extract_line(char *storage) {
    int i;
	int size_line;
	
	if (storage[0] == '\0') {
        return NULL;  // Empty string, no line to extract
    }
    size_line = 0;
    while (storage[size_line] != 0 && storage[size_line] != '\n')
        size_line++;
    if (storage[size_line] == '\n') 
        size_line++;  // Include the newline character in the extracted line
    char *line = malloc((size_line + 1) * sizeof(char));
    if (!line) 
        return NULL;  // Memory allocation failed
    i = 0;
    while (i < size_line) 
	{
        line[i] = storage[i];
        i++;
    }
    line[i] = '\0';  // Null-terminate the string
    return (line);
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
	rest_of_line = malloc(size_rest_of_line * sizeof(char) + 1);
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

char *read_from_file(char *persistent_buffer, int fd)
{
 char *read_buffer;
 //to check if read function works correctly
 int  bytes_read;
//memory allocation for readtime buffer
 read_buffer = malloc(BUFFER_SIZE * sizeof(char) + 1);
 if (!read_buffer) //error alloc
  return (NULL);
 bytes_read = 1; //to enter the loop
 while (bytes_read > 0)
 {
  bytes_read = read(fd, read_buffer, BUFFER_SIZE);
  if (bytes_read == -1) //error
   return (free(read_buffer), NULL);
  read_buffer[bytes_read] = '\0'; //null terminate for using string func
  //append read buffer to static buffer
  persistent_buffer = append_buffer(persistent_buffer, read_buffer); 
  //if there is a newline in the static buffer, break the loop
  if (ft_strchr(persistent_buffer, '\n'))
   break ;
 }
 free (read_buffer);
 return (persistent_buffer);
}

char *get_next_line(int fd)
{
 static char *persistent_buffer;
 char  *line;
//check if fd and BUFFER_Size is valid
 if (fd < 0 || BUFFER_SIZE <= 0) 
  return (NULL);
//first call, we need to inicialize static buffer with 1 byte.
 if (!persistent_buffer)
  persistent_buffer = malloc(sizeof(char) * 1); 
 //if there is no newline in static buffer, read new portion from fd
 if (!ft_strchr(persistent_buffer, '\n'))
  persistent_buffer = read_from_file(persistent_buffer, fd);
 //if allocation fails free persistent buf and return NULL
 if (!persistent_buffer)
  return (free(persistent_buffer), NULL);
 //line is a substring from start to \n including
 line = extract_line(persistent_buffer);
 //update static buffer with the rest of string
 persistent_buffer = update_storage(persistent_buffer);
 return (line);
}

int main(void)
{
    int     file_descriptor;
    char    *result;
    file_descriptor = open("archivo.txt", O_RDONLY);
    result = get_next_line(file_descriptor);
    while (result)
    {
        printf(".....%s", result);
        free(result);
        result = get_next_line(file_descriptor);
    }
	
    free(result);
    return (0);
}