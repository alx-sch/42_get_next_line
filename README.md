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
- **Tailored Configuration**: Easily adjust buffer size and the maximum number of used file descriptors using flags when compiling.
- **Error Handling and Edge Cases**: Handle binary file reading logically to avoid undefined behavior.

Efficiently manage memory using dynamic allocation for reading and storing lines.

Multiple File Descriptors:

Enable the function to handle reading lines from multiple file descriptors concurrently.
Dynamic Memory Allocation:

Efficiently manage memory using dynamic allocation for reading and storing lines.
Line-by-Line Reading:

Implement functionality to read lines sequentially, allowing for easy line-by-line processing.
Static Variable Usage:

Utilize static variables to maintain state between successive calls of the get_next_line function.
Error Handling and Edge Cases:

Implement robust error handling and address edge cases to ensure the function's reliability in various scenarios
- 

## Static Variables
- Static variables are used to retain their values between function calls and throughout the entire execution of a program.  
- They are declared within a function and are only accessible within that function.
- They are initialized only once during the first function call; subsequent calls to the function do not reinitialize them.
  
## The read() System Call
The read() system call is a low-level function in C that allows a program to read data from a file descriptor: `   `


Dynamic Memory Management:

Linked lists allow dynamic memory allocation for each line of text, ensuring that memory is used efficiently based on the actual size of each line. This is particularly useful in scenarios where the length of lines varies significantly.
Buffer Management:

Linked lists can help manage the buffer for reading and storing characters efficiently. Each node in the linked list can represent a portion of the line, and as characters are read, new nodes can be dynamically allocated.
Ease of Concatenation:

Linked lists make it easier to concatenate characters or strings. When reading data in chunks, new nodes can be added to the list, and the linked structure allows efficient concatenation without needing to move or copy large chunks of data.
Scalability:

Linked lists provide a scalable solution, especially when dealing with files containing large lines or when there is a need to handle a large number of lines. The ability to allocate memory dynamically ensures that the program can adapt to varying line lengths and file sizes.
Efficient Memory Release:

When using linked lists, it's generally easier to release memory efficiently. Nodes can be traversed and freed individually, ensuring that memory is deallocated as soon as it is no longer needed.
Facilitates Modularity:

A linked list implementation can be more modular, making it easier to understand and maintain. Each node can encapsulate the logic for handling a portion of the line, leading to a more organized and readable codebase.
Adaptability to Different Data Sources:

Linked lists provide flexibility, making it easier to adapt the get_next_line function to different data sources. Whether reading from a file, a socket, or any other stream, the linked list structure can be adapted to handle various scenarios.

In Summary, the use of linked lists allows for a more flexible and efficient handling of lines of text with varying lengths and dynamic memory allocation needs.

## Binary File   
A binary file is a file that contains information in a format that is not composed of readable characters. 
Examples of binary files include executable files (e.g., .exe), image files (e.g., .jpg, .png), audio files (e.g., .mp3), and many others
```bash
�=ѧ�?k`m�N+�f�|�x�f��V�����x��v=]���BEUg#D
֡�z���� =��ʵ���U|��gHt>ײ�����D�[���ɟ�9ѧ{B��X�o_���q��7=��꼋��ڏ��
@�^���Jǋ���S}'��N��Yk���        &걋9���Г��V��*�_�����Lь��P
```

## Reading standardinput:
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
