# 42_get_next_line

<p align="center">
    <img src="https://github.com/alx-sch/42_get_next_line/assets/134595144/4c3cadb7-0375-4908-a67a-a90bd865ea6d" alt="libft" />
</p>

The get_next_line() function is designed to handle multiple file descriptors, allowing to read lines one-by-one from different sources, only using static variables to keep track of read content between successive calls of get_next_line().

## Features

- **Line-by-Line Reading:** Implement sequential line-by-line reading to facilitate easy processing.
- **Multiple File Descriptors:** Enable concurrent reading from multiple file descriptors.
- **Dynamic Memory Allocation:** Efficiently manage memory using dynamic allocation for reading and storing lines.
- **Persistent State Handling:** Utilize static variables for seamless continuation of line-by-line reading across successive calls to get_next_line().
- **Tailored Configuration:** Easily adjust buffer size and the maximum number of used file descriptors via compilation flags.
- **Error Handling and Edge Cases:** Handle binary file reading logically to avoid undefined behavior.

## Static Variables
- Static variables retain their values between function calls and throughout the entire execution of a program.  
- They are declared within a function and are only accessible within that function.
- They are initialized only once during the first function call; subsequent calls to the function do not reinitialize them.
- **Fun Fact:** Unlike other types of variables, static variables are automatically initialized to zero. For pointers, this means they are initialized to a NULL pointer. According to [42's coding standard](https://github.com/42School/norminette), it is acceptable to declare and initialize static variables in the same line ("_Declaration and an initialisation cannot be on the same line, except for global variables (when allowed), static variables, and constants._"). So please go ahead and maintain good practice and readability without losing 'real estate' 😉 ("_Each function must be maximum 25 lines._"), e.g.: `static char *stash = NULL;`.

## The read() System Call
The read() system call is a low-level function in C that allows a program to read data from a file descriptor; the prototype is `ssize_t read(int fd, void *buffer, size_t count)`.
- **fd (File Descriptor):** Represents the file or I/O stream from which the data will be read. It could be a file, the standard input, or other types of I/O resources. It's an integer value returned by the open() system call.
- **Buffer:** A memory location where the data read from the file descriptor is stored. It must be a pointer to a memory block large enough to accommodate the specified 'count' bytes of data.
- **Count:** The number of bytes to be read from the file descriptor, defined as `BUFFER_SIZE` in the get_next_line() project.
- **Return Value**:
    - **'>0'**: The number of bytes read.
    - **'0'**: In case of reaching the end of file (EOF).
    - **'-1'**: If an error occurs.

## Function Flowchart
![flowchart_gnl](https://github.com/alx-sch/42_get_next_line/assets/134595144/b3c9fdb9-9c2f-44a1-aa2e-8242720cf183)
- **High-Level:**
    - Helper functions (e.g. **ft_strlen()**, **ft_strlcat()**, **ft_strchr()**, as included in the [libft library](https://github.com/alx-sch/42_libft)) are not shown.
    - Error handling for null checks, including failed memory allocation, is not shown (returning NULL).
- **Functions:**
    -   **`char *get_next_line(int fd)`** (greenish-blue): Reads a line from the specified file descriptor and returns it as a pointer to a string (green). Successive calls fetch subsequent lines. Returns NULL for errors, like invalid input (red), or when the EOF is reached (blue 'stash').
    -    **`char *ft_stash_buf_join(char *stash, char *buffer)`** (light green): Concatenates the 'stash' and 'buffer' into a new string, combining the current read content from 'buffer' with the previous content stored in 'stash.' If 'stash' is NULL, it's assigned an empty string.
    -    **`char *ft_read_until_newline_or_eof(int fd, char *stash)`** (yellow): Utilizes the read() function to fetch content into a 'buffer', which is then appended to the 'stash'. The function returns the 'stash' if it contains a newline character or when the EOF is reached.
    -    **`char *ft_extract_line(char *stash)`** (orange): Extracts and returns a substring from the 'stash', starting from the beginning and ending either at the first newline character (purple 'stash') or the NULL terminator (green 'stash'). Returns NULL if the 'stash' is empty (blue 'stash').
    -    **`char *ft_trim_until_newline(char *stash)`** (light blue): Trims content from the 'stash', including the first newline character, and returns the remaining content in a new string (purple 'stash'). If no newline character is found in 'stash', the function returns NULL (green and blue 'stash').
- **Variables:**
   - **`static char *stash`**: The static variable that accumulates content from previous reads, storing data until a newline character is encountered or the EOF is reached. Before get_next_line() returns the extracted line, the 'stash' is updated to only contain content after the encountered newline character. Memory allocated for 'stash' can be freed by calling the function with an invalid file descriptor, e.g. `get_next_line(-1)`.
    - **`char *buffer`**: A temporary storage for reading data from a file descriptor. The content of the buffer is appended to the 'stash' after each read operation.
    - **`BUFFER_SIZE`**: The size of the buffer used for reading from the file descriptor. It is good practice to provide the data type in the main.c as needed (e.g. `#define BUFFER_SIZE_TYPE size_t`).
    - **`FD_SIZE`**:  The maximum number of file descriptors the program is designed to handle. This value represents the size of the array (`static char *stash[FD_SIZE]`) used to store content for multiple file descriptors. It is good practice to provide the data type in the main.c as needed (e.g. `#define FD_SIZE_TYPE size_t`).

## Handling of Binary Data
Binary files, such as executables, images, and audio files (.exe, .jpeg, .png, .mp3, etc.), contain data in formats not composed of readable characters. While the project's specifications allow for undefined behavior when reading binary files, it is advisable to handle this in a controlled manner to prevent unexpected outputs or issues.

Here's an example of what may be displayed when reading binary data:
```bash
�=ѧ�?k`m�N+�f�|�x�f��V�����x��v=]���BEUg#D
֡�z���� =��ʵ���U|��gHt>ײ�����D�[���ɟ�9ѧ{B��X�o_���q��7=��꼋��ڏ��
@�^���Jǋ���S}'��N��Yk���        &걋9���Г��V��*�_�����Lь��P
```

The following function verifies the content of read data by checking for ASCII values less than 32 or greater than 126 (non-printable characters) and 'non-EOF' NULL terminators. These checks help to identify binary data.
```C
int	ft_isbinary(char *stash)
{
	size_t	i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		if (stash[i] == '\0' || stash[i] < 32 || stash[i] > 126) // check for NULL terminator or non-printable characters
		{
			if (stash[i] == '\0' && stash[i + 1] == '\0') // check for EOF
				break ;
			else
				return (1);
		}
		i++;
	}

	return (0);
}
```

## Avoiding Memory Leaks
get_next_line() allocates memory for the line it returns, and it is the user's responsibility to free this memory before the program ends. Additionally, the read data between calls to get_next_line() is stored in the static variable 'stash'. To prevent memory leaks when the user is done reading lines, it is necessary to free the allocated memory for both the returned line and the 'stash'. This can be accomplished by extending the function's invalid input check to include appropriate memory deallocation, making a `get_next_line(-1)` call a command to free the 'stash':

```C
// get_next_line.c
if (fd < 0 || BUFFER_SIZE <= 0)
{
	if (stash != NULL)
		free(stash);

	return (NULL);
}

// get_next_line_bonus.c
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
```
A short program that uses get_next_line() and correctly frees all allocated memory would look like this:
```C
#include <stdio.h> // printf()
#include <fcntl.h> // open()

int	main(void)
{
	int	fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	if (fd == -1)
		return (1);

	while ((line = get_next_line(fd)) != NULL) // Read and print all lines from file.txt
	{
		printf("-->%s\n", line);
		free(line); // Free memory allocated for the extracted line
	}

	close(fd);
	get_next_line(-1); // Free memory allocated for the stash

	return (0);
}
```
Use Valgrind, a memory analysis tool, to detect memory leaks in your program: `valgrind ./TEST`.

## Error Handling
Due to the project's strict specifications, get_next_line() is designed to either return the read line or NULL for all other cases, making it impossible to differentiate between reaching EOF and encountering errors.

For future projects, consider adjusting the prototype to int `get_next_line(int fd, char **line)`. This modification would allow the return value to indicate success or error (e.g., '1' for success, '0' for EOF, '-1' for invalid input, '-2' for binary data, '-3' for failed memory allocation, etc.). Additionally, incorporating 'perror' messages within get_next_line functions would help provide more detailed information to the user:
```C
int	main(void)
{
	int	fd;
	char	*line;
	int	result;

	fd = open("file.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file.\n");
		return (1);
	}

	while ((result = get_next_line(fd, &line)) > 0)  // Read and print all lines from file.txt
	{
		printf("-->%s\n", line);
		free(line); 
	}

   	if (-3 <= result && result < 0) // Alternatively, include error printing within get_next_line functions directly.
	{
		perror("Error in get_next_line.\n");
		if (result == -1)
			perror("Invalid Input. Please check values for fd and BUFFER_SIZE.\n");
		if (result == -2)
			perror("Reading binary data.\n");
		if (result == -3)
			perror("Failed memory allocation.\n");

		close(fd);
		get_next_line(-42, &line); // get_next_line() adjusted so that 'fd == -42' frees memory allocated for stash

		return (1);
    	}

	close(fd);
	get_next_line(-42, &line); // get_next_line() adjusted so that 'fd == -42' frees memory allocated for stash

	return (0);	
}
```

## Testing


Feel free to uncomment the testing programs found at the end of 'get_next_line.c' and 'get_next_line_bonus.c'.

Try out the following:
- Read different files as provided in the 'test_files' folder, covering several edge cases.
- Adjust the `BUFFER_SIZE` during compilation using: `cc -Wall -Werror -Wextra get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=1 -o TEST`
- Test reading from standard input (`fd = 0`).
	- Pipe a file via standard input:
		```bash
		./TEST.out < test_files/test_1.txt
		```	
	- Provide multiline input when prompted (after calling the test program, e.g. `./TEST`). Copy and paste the following as input:
   		```bash
		This is the first line.
		This is the second line.
		The third.
		Fourth.
		And last! EOF.
		```

## Acknowledgements  
- Some of the test files were retrieved from Fabricio Soares' [testing framework](https://github.com/xicodomingues/francinette/tree/master/tests/get_next_line/fsoares).   
- The project badge used is retrieved from [this repo](https://github.com/ayogun/42-project-badges) by Ali Ogun.
