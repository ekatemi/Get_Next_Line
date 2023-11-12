/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <emikhayl@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:19:55 by emikhayl          #+#    #+#             */
/*   Updated: 2023/11/12 16:07:45 by emikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int main(void)
{
    int     file_descriptor;
    char    *result;
    file_descriptor = open("archivo.txt", O_RDONLY);
    result = get_next_line(file_descriptor);
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
