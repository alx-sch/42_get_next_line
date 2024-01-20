/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:02:36 by aschenk           #+#    #+#             */
/*   Updated: 2024/01/19 18:00:56 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*
To handle the reading of binary data in a more controlled way, ft_isbinary()
checks if the 'stash' contains non-printable characters and NULL terminators not
followed by another NULL terminator, which indicates an end-of-file (EOF).
If the binary data check was successful (i.e., if non-printable characters or a
single NULL terminator was found without an EOF indication), '1' is returned,
otherwise '0'.
*/
int	ft_isbinary(char *stash)
{
	size_t	i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		if (stash[i] == '\0' || stash[i] < 32 || stash[i] > 126)
		{
			if (stash[i] == '\0' && stash[i + 1] == '\0')
				break ;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

/*
As included in the libft project/library but with ft_bzero() incorporated
to accommodate the Norm (max. number of functions).
*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*ptr;
	unsigned char	*byte_ptr;
	size_t		total_size;

	if (nmemb > 0)
	{
		if (SIZE_MAX / nmemb < size)
			return (NULL);
	}
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	byte_ptr = (unsigned char *)ptr;
	total_size = nmemb * size;
	while (total_size > 0)
	{
		*byte_ptr = 0;
		byte_ptr++;
		total_size--;
	}
	return (ptr);
}

/*
Extracts content from the input string ('stash') until the first newline
character, so one line. Allocates memory for the extracted line, including the
newline character if present, and returns the extracted line as a string.
Returns NULL if 'stash' is an empty string (stash[0] == '\0').
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
	line = (char *)ft_calloc(i + 2, sizeof(char));
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
Initializes an empty string for 'stash', if NULL
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
	int	bytes_read;
	char	*buffer;

	if (!stash)
		stash = (char *)ft_calloc(1, sizeof(char));
	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
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
which accumulates reads between function calls (the size of reads is defined
by BUFFER_SIZE).
A complete line (meaning until '\n' or EOF) is extracted from the
'stash'. Afterward, the 'stash' is trimmed so it only contains content after
the newline character, which will be stored and used in the next function call.

Manages multiple file descriptors at the same time by declaring 'stash' as a
pointer to an array of characters (before pointer to a single char). This way,
'stash' can hold multiple character pointers (one for each file descriptor).
The default value for the max. number of file descriptors is defined in the
header file but can be adjusted while compiling using the '-D FD_SIZE=n' flag.

Parameters:
	- int fd: File descriptor representing the file to read from.

Returns:
	- If successful, returns a dynamically allocated string containing the
	  next line from the file ('line').
	- If an error occurs, if the EOF is reached, or if the file is binary,
	  NULL is returned.
*/

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash[FD_SIZE] = {NULL};
	size_t		i;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		i = 0;
		while (i < FD_SIZE)
		{
			if (stash[i] != NULL)
				free(stash[i]);
			i++;
		}
		return (NULL);
	}
	stash[fd] = ft_read_until_newline_or_eof(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	if (ft_isbinary(stash[fd]))
		return (NULL);
	line = ft_extract_line(stash[fd]);
	stash[fd] = ft_trim_until_newline(stash[fd]);
	return (line);
}

/*
#include <stdio.h> // printf()
#include <fcntl.h> // open()

// Test: Handling Multiple File Descriptors at the same time
int	main(void)
{
	int	fd_1;
	int	fd_2;
	int	fd_3;
	char	*line;
	int	line_nr_1;
	int	line_nr_2;
	int	line_nr_3;

	line_nr_1 = 1;
	line_nr_2 = 1;
	line_nr_3 = 1;

	fd_1 = open("test_files/test_1.txt", O_RDONLY);
	fd_2 = open("test_files/test_2.txt", O_RDONLY);
	fd_3 = open("test_files/test_3.txt", O_RDONLY);

	line = get_next_line(fd_1);
	printf("fd_1, line %d-->%s\n", line_nr_1++, line);
	free(line);

	line = get_next_line(fd_2);
	printf("fd_2, line %d-->%s\n", line_nr_2++, line);
	free(line);

	line = get_next_line(fd_3);
	printf("fd_3, line %d-->%s\n", line_nr_3++, line);
	free(line);

	line = get_next_line(fd_1);
	printf("fd_1, line %d-->%s\n", line_nr_1++, line);
	free(line);

	line = get_next_line(fd_2);
	printf("fd_2, line %d-->%s\n", line_nr_2++, line);
	free(line);

	line = get_next_line(fd_3);
	printf("fd_3, line %d-->%s\n", line_nr_3++, line);
	free(line);

	line = get_next_line(fd_1);
	printf("fd_1, line %d-->%s\n", line_nr_1++, line);
	free(line);

	line = get_next_line(fd_2);
	printf("fd_2, line %d-->%s\n", line_nr_2++, line);
	free(line);

	line = get_next_line(fd_3);
	printf("fd_3, line %d-->%s\n", line_nr_3++, line);
	free(line);

	line = get_next_line(fd_1);
	printf("fd_1, line %d-->%s\n", line_nr_1++, line);
	free(line);

	line = get_next_line(fd_2);
	printf("fd_2, line %d-->%s\n", line_nr_2++, line);
	free(line);

	line = get_next_line(fd_3);
	printf("fd_3, line %d-->%s\n", line_nr_3++, line);
	free(line);

	line = get_next_line(fd_1);
	printf("fd_1, line %d-->%s\n", line_nr_1++, line);
	free(line);

	line = get_next_line(fd_2);
	printf("fd_2, line %d-->%s\n", line_nr_2++, line);
	free(line);

	line = get_next_line(fd_3);
	printf("fd_3, line %d-->%s\n", line_nr_3++, line);
	free(line);

	line = get_next_line(fd_1);
	printf("fd_1, line %d-->%s\n", line_nr_1++, line);
	free(line);

	line = get_next_line(fd_2);
	printf("fd_2, line %d-->%s\n", line_nr_2++, line);
	free(line);

	line = get_next_line(fd_3);
	printf("fd_3, line %d-->%s\n", line_nr_3++, line);
	free(line);

	close(fd_1);
	close(fd_2);
	close(fd_3);
	get_next_line(-1); // freeing stash

	return (0);
}
*/
