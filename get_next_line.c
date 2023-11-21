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

#define BUF_SIZE 7



char *read_line(int fd)
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
	buffer[bytes_read] = '\0';
    return buffer;
}

int main(void)
{
    int     file_descriptor;
    char    *result;
    file_descriptor = open("archivo.txt", O_RDONLY);
    result = read_line(file_descriptor);
	printf("%s", result);
    /*
    while (result)
    {
        printf("%s", result);
        free(result);
        result = get_next_line(file_descriptor);
    }*/
    free(result);
    return (0);
}
