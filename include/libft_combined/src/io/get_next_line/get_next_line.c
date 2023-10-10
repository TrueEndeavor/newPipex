/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:33:11 by lannur-s          #+#    #+#             */
/*   Updated: 2023/07/28 15:05:45 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* -------------------------------------------------------------------------- */
/*   Function to read lines from a file descriptor one at a time.             */
/*   The function gracefully retrieves each line (fish) from the aquarium     */
/*   file (input file) using a magical cup (buffer). The objective is         */
/*   to avoid reading the entire file at once and return each line found      */
/*   (fish) gracefully.                                                       */
/* -------------------------------------------------------------------------- */

#include "get_next_line.h"

/* -------------------------------------------------------------------------- */
/* Function to obtain the remaining fish (remaining data) from the buffer.    */
/* The explorer identifies the first fish (newline character) in the buffer   */
/* and catches the remaining fish (remaining data) after it. The explorer     */
/* gracefully returns the remaining fish to be explored further.              */
/* It handles the EOF and EOL or End of Input of the STDIN & frees the buffer */
/* -------------------------------------------------------------------------- */
char	*obtain_remaining(char *basin_buffer)
{
	int		i;
	int		j;
	char	*remaining;

	i = 0;
	while (basin_buffer[i] && basin_buffer[i] != '\n')
		i++;
	if (!basin_buffer[i] || (basin_buffer[i] == '\n' && !basin_buffer[i + 1]))
	{
		free(basin_buffer);
		return (NULL);
	}
	remaining = ft_calloc((ft_strlen(basin_buffer) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (basin_buffer[i])
		remaining[j++] = basin_buffer[i++];
	free(basin_buffer);
	return (remaining);
}

/* -------------------------------------------------------------------------- */
/* Function to extract the first line (fish) from the partial content.        */
/* The explorer carefully studies the storage (basin) to find the             */
/* special fish (newline character). If the fish is found, it captures it     */
/* in a new cup (line) and presents it to the world.                          */
/* -------------------------------------------------------------------------- */

char	*extract_line(char *basin_buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!basin_buffer[i])
		return (NULL);
	while (basin_buffer[i] && basin_buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (basin_buffer[i] && basin_buffer[i] != '\n')
	{
		line[i] = basin_buffer[i];
		i++;
	}
	if (basin_buffer[i] && basin_buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

/* -------------------------------------------------------------------------- */
/* Function to read data from the file and append it to stored content.       */
/* The explorer dips its magical cup (cup_buffer) into the aquarium (file)    */
/* and retrieves a scoop of water (characters from the file). The explorer    */
/* continues scooping until it encounters the special fish (newline)          */
/* -------------------------------------------------------------------------- */

char	*read_from_file(char *basin_buffer, int fd)
{
	char	*cup_buffer;
	int		bytes_read;
	char	*temp;

	cup_buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!cup_buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, cup_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(cup_buffer), NULL);
		cup_buffer[bytes_read] = '\0';
		temp = ft_strjoin(basin_buffer, cup_buffer);
		free(basin_buffer);
		basin_buffer = temp;
		if (ft_strchr(basin_buffer, '\n'))
			break ;
	}
	free (cup_buffer);
	return (basin_buffer);
}

/* -------------------------------------------------------------------------- */
/* The main function to get the next line (fish) from the file descriptor.    */
/* The aquarium explorer (get_next_line) gracefully reads lines from the      */
/* magical aquarium (input file) using the cup (buffer). The explorer         */
/* aims to find and return each fish (line) one at a time without disturbing  */
/* the rest of the aquarium (file) and avoiding reading the entire file       */
/* at once. The explorer also handles edge cases and errors elegantly.        */
/* -------------------------------------------------------------------------- */

char	*get_next_line(int fd)
{
	static char	*basin_buffer;
	char		*line;

	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!basin_buffer)
		basin_buffer = ft_calloc(1, sizeof(char));
	if (!ft_strchr(basin_buffer, '\n'))
		basin_buffer = read_from_file(basin_buffer, fd);
	if (!basin_buffer)
		return (free(basin_buffer), NULL);
	line = extract_line(basin_buffer);
	basin_buffer = obtain_remaining(basin_buffer);
	return (line);
}
