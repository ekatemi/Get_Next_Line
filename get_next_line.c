/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <emikhayl@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:29:13 by emikhayl          #+#    #+#             */
/*   Updated: 2023/11/16 19:36:29 by emikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define BUF_SIZE 7

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

char	*ft_strjoin(char *s1, char *s2)
{
	
	char	*joined;
	size_t	i;
    size_t	j;

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

char *append_buffer(char *buffer, char *spoon_buffer)
{
    char *temp;
    
    temp = ft_strjoin(buffer, spoon_buffer);
    free(buffer);
    return (temp);
}

void    print_newline_helper(char *buffer)
{

    while (*buffer)
    {
        if (*buffer == '\n') 
        {
            *buffer= '#';
        }
        printf("%c",*buffer);
        buffer++;
    }
}

char *read_line(int fd)
{
    int bytes_read;
    char *spoon_buffer;
    
    spoon_buffer = malloc(sizeof(char) * BUF_SIZE + 1);
    if (!spoon_buffer)
        return NULL;
    bytes_read = read(fd, spoon_buffer, BUF_SIZE);
    print_newline_helper(spoon_buffer);
    if (bytes_read <= 0)
	{
		free(spoon_buffer);
        return NULL;
	}
    spoon_buffer[bytes_read] = '\0';
    return spoon_buffer;
}

char *get_next_line(int fd)
{
    static char *big_buffer;
    char *line = NULL;
    
    big_buffer = malloc(sizeof(char) + 1);
    line = read_line(fd);


    big_buffer = ft_strjoin(big_buffer, line);
    return(big_buffer);
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
	next_line = read_line(fd);
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
