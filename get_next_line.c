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

#include "get_next_line.h"

#define BUF_SIZE 6

char *get_next_line(int fd)
{
    int bytes_read;
    char *buffer;
    static int count = 1;
    printf("malloc#[%d]---", count++);
    buffer = malloc(BUF_SIZE * sizeof(char) + 1);
    if (!buffer)
        return NULL;
    bytes_read = read(fd, buffer, BUF_SIZE);
    if (bytes_read <= 0)
	{
		free(buffer);
        return NULL;
	}
	buffer[BUF_SIZE] = '\0';
    return buffer;
}

int main (void)
{
	int fd;
	char *next_line;
	int count;
    
	count = 0;	
	fd = open("archivo.txt", O_RDONLY);
	if (fd == -1)
		return(1);
	while(42)
	{
	next_line = get_next_line(fd);
	if (next_line == NULL)
		break;
	count++;
	printf("[%d] :%s\n", count, next_line);
	free(next_line);
	next_line = NULL;
	}
	close(fd);
	return (0);
}
