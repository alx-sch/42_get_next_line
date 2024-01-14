/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:02:24 by aschenk           #+#    #+#             */
/*   Updated: 2024/01/12 19:19:31 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

// Default value of 10 for BUFFER_SIZE if not defined during compilation
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

// Default value of 256 for available file descriptors.
// You can check the actual number via 'cat /proc/sys/fs/file-max'
// It is a staggering '9223372036854775807' on my system!
// It is a stretch to allocate an array with this amount of entries, but if
// need be, you can easily adjust while compiling via the '-D FD_LIMIT=n' flag.
# ifndef FD_SIZE
#  define FD_SIZE 256
# endif

# include <stdlib.h> // malloc(), free()
# include <unistd.h> // read()
# include <stddef.h> // size_t

char	*ft_stash_buf_join(char *stash, char *buffer);
char	*ft_strchr(const char *s, int c);
char	*ft_trim_until_newline(char *stash);
char	*ft_readf(int fd, char *stash);
char	*ft_getline(char *stash);
char	*get_next_line(int fd);

#endif
