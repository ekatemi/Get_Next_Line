#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 10

//PARAMETERS file descriptor
//RETURNS string with \n or \0 at the end


char *get_next_line(int fd)
{
    static char *buffer;
    char        *line;

    buffer = read_line(fd, buffer);
    line = extract_line(buffer);
    buffer = update_buffer(buffer);
   
    return line;
}

int main(void)
{
    int     fd;
    char    *result;
    fd = open("archivo.txt", O_RDONLY);
    result = get_next_line(fd);
    printf(".....%s", result);
    while (result)	
    free(result);
    return (0);
}
