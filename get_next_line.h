/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:02:24 by aschenk           #+#    #+#             */
/*   Updated: 2024/01/17 19:01:58 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// Default value of 42 for BUFFER_SIZE if not defined during compilation
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h> // malloc(), free()
# include <unistd.h> // read()
# include <stddef.h> // size_t
# include <stdint.h> // SIZE_MAX

char	*ft_stash_buf_join(char *stash, char *buffer); // in utils
char	*ft_strchr(const char *s, int c); // in utils
char	*ft_trim_until_newline(char *stash); // in utils
void	*ft_calloc(size_t nmemb, size_t size);
char	*get_next_line(int fd);

#endif
