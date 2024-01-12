# !!WIP!! 42_get_next_line !!WIP!!

<p align="center">
    <img src="https://github.com/alx-sch/42_get_next_line/assets/134595144/4c3cadb7-0375-4908-a67a-a90bd865ea6d" alt="libft" />
</p>

Function to read lines from a file descriptor one-by-one using static variables.


## Why using linked lists?
Using linked lists offers several advantages:

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
./a.out < input.txt
```

```bash
echo "First line\nThis is the second one\nAnd third!" | ./a.out
```
