/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <emikhayl@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:29:42 by emikhayl          #+#    #+#             */
/*   Updated: 2023/11/29 20:06:35 by emikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char *get_free(char **str1, char **str2);
size_t ft_strlen(char *str);
char *ft_strchr(char *str, int c);
char *strjoin(char *str1, char *str2);
char *append(char *buffer, char *str);
char *extract_line(char *buffer);
char	*update_storage(char *buffer);
char *read_from_file(int fd, char *persistent_buffer);
char *get_next_line(int fd);


#endif
