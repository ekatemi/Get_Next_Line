#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "get_next_line.h"

#define BUF_SIZE 10

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



char *ft_strjoin(char *s1, char *s2)
{
    size_t len1;
    size_t len2;
    size_t i;
    size_t j;
    
    len1 = 0;
    len2 = 0;
    i = 0;
    j = 0;
    if (s1 != NULL)
        len1 = strlen(s1);
    if (s2 != NULL)
        len2 = strlen(s2);
    char *joined = malloc(len1 + len2 + 1);
    if (!joined)
        return NULL; // Allocation failed
    while (s1 != NULL && s1[i])
        joined[j++] = s1[i++];
    i = 0;
    while (s2 != NULL && s2[i])
        joined[j++] = s2[i++];
    joined[j] = '\0';
    return joined;
}

char *append_buffer(char *buffer, char *spoon_buffer)
{
    char *temp;
    
    temp = ft_strjoin(buffer, spoon_buffer);
    free(buffer);
    return (temp);
}


char *read_from_file(char *bucket_buffer, int fd)
{
    char *spoon_buffer;
    int bytes_read;

    spoon_buffer = malloc(BUF_SIZE * sizeof(char) + 1);
    if (!spoon_buffer)
        return NULL;

    // Read data into the spoon_buffer
    bytes_read = read(fd, spoon_buffer, BUF_SIZE);
    if (bytes_read == -1)
        return free(spoon_buffer), NULL;

    if (bytes_read == 0)
    {
        // End of file reached, free spoon_buffer and return NULL
        free(spoon_buffer);
        return NULL;
    }

    spoon_buffer[bytes_read] = '\0';

    // Append spoon_buffer to bucket_buffer
    bucket_buffer = append_buffer(bucket_buffer, spoon_buffer);

    // Free spoon_buffer
    free(spoon_buffer);

    return bucket_buffer;
}

char *extract_line(char *bucket_buffer)
{
    char *line;
    char *newline_pos = ft_strchr(bucket_buffer, '\n');

    if (newline_pos == NULL)
    {
        // No newline found, return the entire content
        line = ft_strdup(bucket_buffer);
        bucket_buffer = NULL; // No remaining characters in the buffer
    }
    else
    {
        // Newline found, extract characters up to newline
        size_t line_length = newline_pos - bucket_buffer;
        line = malloc(line_length + 1); // +1 for null-termination
        if (!line)
            return NULL;
        strncpy(line, bucket_buffer, line_length);
        line[line_length] = '\0';
        
        // Update bucket_buffer to point to the remaining characters
        bucket_buffer = ft_strdup(newline_pos + 1); // +1 to skip the newline
    }

    return line;
}


char *obtain_remaining(char *str)
{
    char *line = NULL;
    char *n = ft_strchr(str, '\n');

    if (n != NULL)
    {
        // Calculate the length of the remaining characters
        size_t remaining_length = strlen(n + 1);

        // Allocate memory for the remaining characters
        line = malloc(remaining_length + 1);  // +1 for null-termination
        if (!line)
            return NULL;

        // Copy the remaining characters using strncpy
        strncpy(line, n + 1, remaining_length);
        line[remaining_length] = '\0';  // Null-terminate the string
    }

    return line;
}

char *get_next_line(int fd)
{
    static char *bucket_buffer;
    char *line;

    if (fd < 0 || BUF_SIZE <= 0) 
        return NULL;

    if (!bucket_buffer)
    {
        // Allocate memory for the initial buffer
        bucket_buffer = malloc(BUF_SIZE + 1);
        if (!bucket_buffer)
            return NULL;
    }

    if (!ft_strchr(bucket_buffer, '\n'))
    {
        // Read more data into the buffer if needed
        bucket_buffer = read_from_file(bucket_buffer, fd);
        //printf("What returns read_from_file ----->%s\n", bucket_buffer);
    }

    line = extract_line(bucket_buffer);
    //printf("What returns extract_line ----->%s\n", bucket_buffer);
    if (line == NULL)
    {
        // No more lines, free the buffer and return NULL
        free(bucket_buffer);
        bucket_buffer = NULL;
    }
    else
    {
        // Update bucket_buffer to point to the remaining characters
        bucket_buffer = obtain_remaining(bucket_buffer);
    }
    if(!line)
        return NULL;
    return line;
}


int main(void)
{
    int     file_descriptor;
    char    *result;
    file_descriptor = open("archivo.txt", O_RDONLY);
	result = get_next_line(file_descriptor);
    //result = get_next_line(file_descriptor);
	printf("%s", result);
    while (result)
    {
        printf("%s", result);
        free(result);
        result = get_next_line(file_descriptor);
    }
    free(result);
    return (0);
}