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
		return (get_free(&buffer));
	}
	line_size = ft_strlen(ptr_newline) - 1;
	rest_line = calloc((line_size + 1), sizeof(char));
	if (!rest_line)
	{
		get_free(&buffer);
	}
    temp = rest_line;
	while (0 < line_size--)
		*temp++ = *++ptr_newline;
	//*temp = '\0';
	free (buffer);
	buffer = rest_line;
	return (buffer);
}

char *read_from_file(int fd, char *buffer)
{
    char *r_buffer;
    int  bytes_nbr;

    r_buffer = calloc(BUFFER_SIZE + 1, sizeof(char));
    if (!r_buffer)
        return (NULL);
    while (1)
    {
        bytes_nbr = read(fd, r_buffer, BUFFER_SIZE);
        if (bytes_nbr == -1)
            return (get_free(&r_buffer));
        r_buffer[bytes_nbr] = '\0';
        buffer = append(buffer, r_buffer);
        if (ft_strchr(buffer, '\n') || bytes_nbr == 0)
            break ;
 }
 get_free(&r_buffer);
 return (buffer);
}

char *get_free(char **str1)
{
	if (str1 && *str1)
	{
		free(*str1);
		*str1 = NULL;
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
	persistent_buffer = calloc(1, sizeof(char));
	if (!persistent_buffer)
		return (get_free(&persistent_buffer));

 if (!ft_strchr(persistent_buffer, '\n'))
	persistent_buffer = read_from_file(fd, persistent_buffer);
 if (!persistent_buffer)
	return (get_free(&persistent_buffer));
 line = extract_line(persistent_buffer);
 if (!line)
 {
 	persistent_buffer = get_free(&persistent_buffer);
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
