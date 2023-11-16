#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 20

char *get_next_line(int fd)
{
    char *buffer = malloc(BUF_SIZE + 1);
    if (!buffer)
        return NULL;

    char *newline = NULL;
    int position = 0;

    while (1)
    {
        int bytes_read = read(fd, buffer + position, 1);
        if (bytes_read <= 0)
            break;

        if (buffer[position] == '\n')
        {
            newline = strndup(buffer, position);
            position = 0; // Reset position for the next line
            break;
        }

        position++;

        if (position == BUF_SIZE)
        {
            // Buffer full, need to allocate more space
            free(buffer);
            buffer = malloc((BUF_SIZE * 2) + 1);
            if (!buffer)
                return NULL;
        }
    }

    if (position > 0)
    {
        // If there's content left in the buffer after the loop ends
        newline = strndup(buffer, position);
    }

    return newline;
}

int main(void)
{
    int fd;
    char *next_line;
    //int count = 0;

    fd = open("archivo.txt", O_RDONLY);
    if (fd == -1)
    {
        return 1;
    }

    while ((next_line = get_next_line(fd)) != NULL)
    {
        //count++;
        printf("%s\n", next_line);
        free(next_line);
    }

    close(fd);
    return 0;
}
