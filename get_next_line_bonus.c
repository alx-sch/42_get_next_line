/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:02:36 by aschenk           #+#    #+#             */
/*   Updated: 2024/01/12 19:20:37 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

/*
Extracts a content from the input string ('stash') until the first newline
character, so one line. Allocates memory for the extracted line, including the
newline character if present and returns extracted line as string.
Returns NULL if 'stash' is empty.
*/
char	*ft_extract_line(char *stash)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] != '\n' && stash[i])
		i++;
	line = (char *)malloc((i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

/*
Reads data from a file descriptor ('fd') and appends it to a string ('stash')
until a newline character is encountered or the end of the file is reached.
The function dynamically allocates memory for a buffer to read data, and it
manages the concatenation of the buffer with the existing 'stash'.
If an error occurs during reading or memory allocation, it frees the allocated
memory and returns NULL.

Parameters:
	- fd: File descriptor representing the file to read from.
	- stash: String containing the accumulated data read so far.

Returns:
	- If successful, returns the updated 'stash' string with appended data.
	- If an error occurs, returns NULL, and memory allocated
	  for 'stash' is freed.
*/
char	*ft_read_until_newline_or_eof(int fd, char *stash)
{
	int		bytes_read;
	char	*buffer;

	buffer = malloc((BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stash = ft_stash_buf_join(stash, buffer);
	}
	free(buffer);
	return (stash);
}

/*
Reads a line from a file descriptor ('fd') and returns it as a dynamically
allocated string. Returns the next line when the get_next_line() is called
again (or NULL when the EOF ('\0') was reached).

Read data is appended to a string ('stash') until either a newline character
or the EOF is encountered. This 'stash' is maintained as static storage,
which accumulates reads between function calls (size of reads is defined by
BUFFER_SIZE).
A complete line (meaning until '\n' or EOF) is extracted from the
'stash'. Afterwards, the 'stash' is trimmed so it only containts content after
the newline character, which will be stored and used in the next function call.

To handle the reading of binary data in a more controlled way, get_next_line()
checks the data input for non-printable characters and NULL terminators not
followed by another NULL terminator, which indicates an EOF. If the binary data
check was successful (i.e., if non-printable characters or a single NULL
terminator were found without an EOF indication), the function returns NULL.

Manages multiple file descriptors at the same time by declaring 'stash' as a
pointer to an array of characters (before: pointer to a single char). This way,
'stash' can hold multiple character pointers (one for each file descriptor).

Parameters:
	- fd: File descriptor representing the file to read from.

Returns:
	- If successful, returns a dynamically allocated string containing the
	  next line from the file ('line').
	- If an error occurs, if the EOF is reached or if file is binary,
	  NULL is returned.
*/

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash[FD_LIMIT];
	size_t		i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = ft_read_until_newline_or_eof(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	i = 0;
	while (stash[fd][i] && stash[fd][i] != '\n')
	{
		if (stash[fd][i] == '\0' || !ft_isprint((stash[fd][i])))
		{
			if (stash[fd][i] == '\0' && stash[fd][i + 1] == '\0')
				break ;
			else
				return (NULL);
		}
		i++;
	}
	line = ft_extract_line(stash[fd]);
	stash[fd] = ft_trim_until_newline(stash[fd]);
	return (line);
}

/*
#include <stdio.h>
#include <fcntl.h>

// Testing reading from a file or standard input
int	main(void)
{
	int		fd;
	char	*line;
	int		line_nr;

	line_nr = 1;

	fd = open("test_1.txt", O_RDONLY);
	// fd = 0; // fd for standard input

	line = get_next_line(fd);
	printf("line %d-->%s\n", line_nr++, line);

	line = get_next_line(fd);
	printf("line %d-->%s\n", line_nr++, line);

	line = get_next_line(fd);
	printf("line %d-->%s\n", line_nr++, line);

	line = get_next_line(fd);
	printf("line %d-->%s\n", line_nr++, line);

	line = get_next_line(fd);
	printf("line %d-->%s\n", line_nr++, line);

	close(fd);
	return (0);
}
*/