/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunlee <hyunlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 14:42:37 by hyunlee           #+#    #+#             */
/*   Updated: 2026/05/14 01:39:10 by hyunlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
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

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (n > 0)
	{
		*d = *s;
		d++;
		s++;
		n--;
	}
	return (dest);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	slen;
	size_t	maxlen;
	char	*arr;

	slen = 0;
	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		maxlen = 0;
	else if (len > slen - start)
		maxlen = slen - start;
	else
		maxlen = len;
	arr = (char *)malloc((maxlen + 1) * sizeof(char));
	if (arr == NULL)
		return (NULL);
	if (maxlen > 0)
		ft_memcpy(arr, s + start, maxlen);
	arr[maxlen] = '\0';
	return (arr);
}
