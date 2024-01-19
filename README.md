# 42_get_next_line

<p align="center">
    <img src="https://github.com/alx-sch/42_get_next_line/assets/134595144/4c3cadb7-0375-4908-a67a-a90bd865ea6d" alt="libft" />
</p>

The get_next_line() function is designed to handle multiple file descriptors, allowing to read lines one-by-one from different sources, only using static variables to keep track of read content between successive calls of get_next_line().

## Features

- **Line-by-Line Reading:** Implement sequential line-by-line reading to facilitate easy processing.
- **Multiple File Descriptors:** Enable concurrent reading from multiple file descriptors.
- **Dynamic Memory Allocation**: Efficiently manage memory using dynamic allocation for reading and storing lines.
- **Persistent State Handling**: Utilize static variables for seamless continuation of line-by-line reading across successive calls to get_next_line().
- **Tailored Configuration**: Easily adjust buffer size and the maximum number of used file descriptors via compilation flags.
- **Error Handling and Edge Cases**: Handle binary file reading logically to avoid undefined behavior.

## Static Variables
- Static variables are used to retain their values between function calls and throughout the entire execution of a program.  
- They are declared within a function and are only accessible within that function.
- They are initialized only once during the first function call; subsequent calls to the function do not reinitialize them.
- **Fun Fact:** Unlike other types of variables, static variables are automatically initialized to zero; for pointers, this means they are initialized to a null pointer. According to [42's coding standard](https://github.com/42School/norminette), it is acceptable to declare and initialize static variables in the same line ("_Declaration and an initialisation cannot be on the same line, except for global variables (when allowed), static variables, and constants._"). So please go ahead and maintain good practice and readability without losing 'real estate' 😉 ("_Each function must be maximum 25 lines._"), e.g.: `static char *stash = NULL;`.

## The read() System Call
The read() system call is a low-level function in C that allows a program to read data from a file descriptor; the protype is `ssize_t read(int fd, void *buffer, size_t count)`.
- **fd (File Descriptor):** The file descriptor represents the file or I/O stream from which the data will be read. It could be a file, the standard input, or other types of I/O resources. It's an integer value returned by the open() system call.
- **Buffer:** Memory location where the data read from the file descriptor is stored. It must be a pointer to a memory block that is large enough to accomodate the specified 'count' bytes of data.
- **Count:** The number of bytes to be read from the file descriptor; defined as `BUFFER_SIZE` in the get_next_line() project.
- **Return Value**:
    - **'>0'**: The number of bytes read.
    - **'0'**: In case of reaching the end of file (EOF).
    - **'-1'**: If an error occurs.

## Function Flowchart
![gnl_flowchart_5](https://github.com/alx-sch/42_get_next_line/assets/134595144/38bb8ea3-38b1-43c6-9760-785444e92124)
- **High-Level:**
    - Helper functions (e.g. **ft_strlen()**, **ft_strlcat()**, **ft_strchr()**, as included in the [libft library](https://github.com/alx-sch/42_libft)) are not shown.
    - Error handling for null checks, including failed memory allocation, is not shown (returning NULL).
- **Functions:**
    -   **`char *get_next_line(int fd)`** (greenish-blue): Reads a line from the specified file descriptor and returns it as a pointer to a string (green). Successive calls fetch subsequent lines. Returns NULL for errors, like invalid input (red), or when the EOF is reached (blue 'stash').
    -    **`char *ft_stash_buf_join(char *stash, char *buffer)`** (light green): Concatenates the 'stash' and 'buffer' into a new string, combining the current read content from 'buffer' with the previous content stored in 'stash.' If 'stash' is NULL, it's assigned an empty string.
    -    **`char *ft_read_until_newline_or_eof(int fd, char *stash)`** (yellow): Utilizes the read() function to fetch content into a 'buffer,' which is then appended to the 'stash.' The function returns the 'stash' if it contains a newline character or when the EOF is reached.
    -    **`char *ft_extract_line(char *stash)`** (orange): Extracts and returns a substring from the 'stash,' starting from the beginning and ending either at the first newline character (purple 'stash') or the null-terminator (green 'stash'). Returns NULL if the 'stash' is empty (blue 'stash').
    -    **`char *ft_trim_until_newline(char *stash)`** (light blue): Trims content from the 'stash,' including the first newline character, and returns the remaining content in a new string (purple 'stash'). If no newline character is found in 'stash,' the function returns NULL (green and blue 'stash').
- **Variables:**
   - **`static char *stash`**: A static pointer to a string that accumulates content from previous reads, storing data until a newline character is encountered or the EOF is reached. Before get_next_line() returns the extracted line, 'stash' is updated to only contain content after the encountered newline character.
    - **`char *buffer`**: A temporary storage for reading data from a file descriptor. The content of the buffer is appended to the 'stash' after each read operation.
    -  **`BUFFER_SIZE`**: The size of the buffer used for reading from the file descriptor. The variable type should be provided by the user as needed in the main.c (e.g. `#define BUFFER_SIZE_TYPE size_t`).
    - **`FD_SIZE`** (bonus):  The maximum number of file descriptors the program is designed to handle. This value represents the size of the array (`static char *stash[FD_SIZE]`) used to store content for multiple file descriptors. The variable type should be provided by the user as needed in the main.c (e.g. `#define FD_SIZE_TYPE size_t`).

## Handling of Binary Data
Binary files, such as executables, images, and audio files (.exe, .jpeg, .png, .mp3, etc.), contain data in formats not composed of readable characters. While the project's specifications allow for undefined behavior when reading binary files, it's good practice to this in a controlled way to avoid unexpected outputs or issues.

Here's an example of an output when reading binary data:
```bash
�=ѧ�?k`m�N+�f�|�x�f��V�����x��v=]���BEUg#D
֡�z���� =��ʵ���U|��gHt>ײ�����D�[���ɟ�9ѧ{B��X�o_���q��7=��꼋��ڏ��
@�^���Jǋ���S}'��N��Yk���        &걋9���Г��V��*�_�����Lь��P
```

The following function checks if the read data contains ASCII values less than 32 or greater than 126, as well as NULL terminators, which are not indicative of an EOF. This helps to identify binary data.
```C
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
```


## Avoiding Memory Leaks
get_next_line() allocates memory for the line it returns, which should be freed by the user before the program ends. Additionally, read data between calls to get_next_line() is stored in the static variable 'stash'. To prevent memory leaks when the user is done reading lines, it is necessary to free the allocated memory for this variable. This can be achieved by calling `get_next_line(-1)` using the following code in get_next_line():

```C
//get_next_line.c
if (fd < 0 || BUFFER_SIZE <= 0)
{
	if (stash != NULL)
		free(stash);
	return (NULL);
}

//get_next_line_bonus.c
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

	while ((line = get_next_line(fd)) != NULL) // Print all lines in file.txt
	{
		printf("-->%s\n", line);
		free(line); // Free memory allocated for the extracted line
	}

	close(fd);
	get_next_line(-1); // Free memory allocated for the stash

	return (0);
}
```
## Testing
Feel free to uncomment the testing programs found at the end of 'get_next_line.c' and 'get_next_line_bonus.c'. Try out different edge cases when testing:
- Read different files as provided in the folder 'test_files', which encompass several edge cases.
- Test reading from the standard input (`fd = 0`).
	- Pipe a file via standard input:
		```bash
		./TEST.out < test_files/test_1.txt
		```	
	- Provide multiline input when prompted (after calling the test program, e.g. `./TEST`). Copy and past the following as input:
   		```bash
		This is the first line.
		This is the second line.
		The third.
		Fourth.
		And last! EOF.
		```
- Adjust the `BUFFER_SIZE` while compiling with: `cc -Wall -Werror -Wextra get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=1 -o TEST`


## Reading from standard input:
- fd = 0 -> prompted to input text when calling program -> multiline not trivial -> you can copy and past this, for example, run the testing program and paste a multiline input, e.g. this one:
```bash
This is the first line.
This is the second line.
And the last! EOF
```

or through piping

```bash
./a.out < test_files/test_1.txt
```

```bash
echo "First line\nThis is the second one\nAnd third!" | ./a.out
```
## Acknowledgements  
- Some of the test files were retrieved from Fabricio Soares' [testing framework](https://github.com/xicodomingues/francinette/tree/master/tests/get_next_line/fsoares) for get_next_line().   
- The project badge used is retrieved from [this repo](https://github.com/ayogun/42-project-badges) by Ali Ogun.
