#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stddef.h>  // Include for size_t

#define BUFFER_SIZE 999999999

size_t ft_strlen(char *str)
{
    size_t len;
    len = 0;
    while(*str++)
        len++;
    return (len);
}

char *ft_strchr(char *str, int c)
{
    while(*str)
    {
        if (*str == (char)c)
            return (str);
        str++;
    }
    if ((char)c == '\0')
        return (str);
    return (NULL);
}

char *strjoin(char *str1, char *str2)
{
    char *joined;
    char *temp;

    joined = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
    if (!joined)
        return (NULL);
    temp = joined;
    while (*str1)
        *temp++ = *str1++;
    while (*str2)
        *temp++ = *str2++;
    *temp = '\0';
    return (joined);
}

//this function appends string to buffer, allocates memory for new string and frees
//memory of the old buffer. Returns pointer to concactenaited string
char *append(char *buffer, char *str)
{
    char *new_buf;
    
    new_buf = strjoin(buffer, str);
    if(!new_buf)
        return (NULL);
    free(buffer);
    return (new_buf);
}

char *ft_strcpy(char *s1, char *s2)
{
    char *temp;

    temp = s1;
    while (*s2)
    {
        *s1++ = *s2++;
    }
    *s1 = '\0';
    return (temp);
}


//PARAMETERS file descriptor
//RETURNS string with \n or \0 at the end
char *extract_line(char *buffer) 
{    
	int line_size;
	char *temp;

	if (buffer[0] == '\0') 
        return NULL;  // Empty string, no line to extract
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
		free(buffer);
		return (NULL);
	}
	line_size = ft_strlen(ptr_newline) - 1;
	rest_line = malloc(sizeof(char) * (line_size + 1));
	if (!rest_line)
	{
		free(buffer);
		return (NULL);
	}
    temp = rest_line;
	while (0 < line_size--)
		*temp++ = *++ptr_newline;
	*temp = '\0';
	free (buffer);
	buffer = rest_line;
	return (buffer);
}

char *read_from_file(int fd, char *persistent_buffer)
{
 char *r_buffer;
 //to check if read function works correctly
 int  bytes_nbr;
//memory allocation for readtime buffer
 r_buffer = malloc(BUFFER_SIZE * sizeof(char) + 1);
 if (!r_buffer) //error alloc
  return (NULL);
 while (1) //endless loop
 {
  bytes_nbr = read(fd, r_buffer, BUFFER_SIZE);
  if (bytes_nbr == -1) //error
   return (free(r_buffer), NULL);
   r_buffer[bytes_nbr] = '\0';
  //append read buffer to static buffer
  persistent_buffer = append(persistent_buffer, r_buffer); 
  //if there is a newline in the static buffer, break the loop
  if (ft_strchr(persistent_buffer, '\n') || bytes_nbr == 0)
   break ;
 }
 free (r_buffer);
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
  persistent_buffer = read_from_file(fd, persistent_buffer);
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
    int     fd;
    char    *result;
    fd = open("archivo.txt", O_RDONLY);
    result = get_next_line(fd);
    //printf("Result is %s\n", result);
    while (result)	
    {
        printf("RESULT--->>>%s", result);
        free(result);
        result = get_next_line(fd);
    }
    free(result);
    return (0);
}
