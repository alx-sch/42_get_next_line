/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:02:05 by aschenk           #+#    #+#             */
/*   Updated: 2024/01/12 11:50:06 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
As included in the libft project/library.
Returns length of NULL-terminated string.
*/
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*
As included in the libft project/library.
Concatenates two strings and NULL-terminates. Fct. strcat() would
have even been a bit simpler, but it's not readily available via libft.
*/
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;
	size_t	j;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	i = 0;
	j = len_dst;
	if (len_dst < size)
	{
		while (src[i] && (len_dst + i) < (size - 1))
		{
			dst[j] = src[i];
			i++;
			j++;
		}
		dst[j] = '\0';
	}
	else
		len_dst = size;
	return (len_dst + len_src);
}

/*
Similar to ft_strjoin() of the libft library, but also manages:
-	NULL input for 'stash' -> allocates memory for an empty string.
-	Frees memory for 'stash' after being concatenated with 'buffer' in 'str'.
*/
char	*ft_stash_buf_join(char *stash, char *buffer)
{
	char	*str_joined;
	size_t	len_stash;
	size_t	len_buffer;

	if (!stash)
	{
		stash = (char *)malloc(1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	len_stash = ft_strlen(stash);
	len_buffer = ft_strlen(buffer);
	str_joined = (char *)malloc(len_stash + len_buffer + 1);
	if (!str_joined)
	{
		free(stash);
		return (NULL);
	}
	str_joined[0] = '\0';
	ft_strlcat(str_joined, stash, len_stash + len_buffer + 1);
	ft_strlcat(str_joined, buffer, len_stash + len_buffer + 1);
	free(stash);
	return (str_joined);
}

/*
As included in the libft project/library.
Finds specific character in a string and returns pointer pointing to its first
occurence, returns NULL if character is not found.
*/
char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

/*
Removes the content of the input string ('stash') from the start until
the first newline char by copying the content of 'stash' after '\n' into
a new string and frees memory allocated for 'stash'.
If there is no '\n' in 'stash', it frees memory allocated for 'stash' and
returns NULL.
*/
char	*ft_trim_until_newline(char *stash)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	if (stash[i] == '\0')
	{
		free(stash);
		return (NULL);
	}
	new_str = (char *)malloc((ft_strlen(stash) - i + 1));
	if (!new_str)
	{
		free(stash);
		return (NULL);
	}
	i++;
	j = 0;
	while (stash[i] != '\0')
		new_str[j++] = stash[i++];
	new_str[j] = '\0';
	free(stash);
	return (new_str);
}
