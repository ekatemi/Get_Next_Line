/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <emikhayl@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:29:13 by emikhayl          #+#    #+#             */
/*   Updated: 2023/11/29 20:54:25 by emikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_free(char **str1, char **str2)
{
	if (str1 && *str1)
	{
		free(*str1);
		*str1 = NULL;
	}
	if (str2 && *str2)
	{
		free(*str2);
		*str2 = NULL;
	}
	return (NULL);
}

char *get_next_line(int fd)
{
 static char	*persistent_buffer;
 char			*line;

 if (fd < 0 || BUFFER_SIZE <= 0) 
	return (NULL);
 if (!persistent_buffer)
	persistent_buffer = calloc(sizeof(char), 1);
	if (!persistent_buffer)
		return (get_free(&persistent_buffer, NULL));

 if (!ft_strchr(persistent_buffer, '\n'))
	persistent_buffer = read_from_file(fd, persistent_buffer);
 if (!persistent_buffer)
	return (get_free(&persistent_buffer, NULL));
 line = extract_line(persistent_buffer);
 if (!line)
 {
 	persistent_buffer = get_free(&persistent_buffer, NULL);
	return (NULL);
 }
 persistent_buffer = update_storage(persistent_buffer);

 return (line);
}

// int main(void)
// {
//     int     fd;
//     char    *result;
//     fd = open("tst.txt", O_RDONLY);
//     result = get_next_line(fd);
//     //printf("Result is %s\n", result);
//     while (result)	
//     {
//         printf("RESULT--->>>%s", result);
//         free(result);
//         result = get_next_line(fd);
//     }
//     free(result);
//     return (0);
// }
