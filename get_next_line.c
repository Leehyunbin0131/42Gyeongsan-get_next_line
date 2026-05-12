/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunlee <hyunlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 14:40:52 by hyunlee           #+#    #+#             */
/*   Updated: 2026/05/12 23:51:10 by hyunlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*my_strjoin(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*arr;

	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	arr = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (arr == NULL)
		return (NULL);
	ft_memcpy(arr, s1, s1_len);
	ft_memcpy(arr + s1_len, s2, s2_len + 1);
	return (arr);
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	size_t	maxlen;
	char	*arr;
	size_t	i;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - start)
		maxlen = slen - start;
	else
		maxlen = len;
	arr = (char *)malloc((maxlen + 1) * sizeof(char));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (i < maxlen)
	{
		arr[i] = s[start + i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

static int	fill_until_nl_or_eof(int fd, char **backup)
{
	char		buf[BUFFER_SIZE + 1];
	ssize_t		buf_len;
	char		*temp;

	while (1)
	{
		buf_len = read(fd, buf, BUFFER_SIZE);
		if (buf_len < 0)
		{
			free(*backup);
			*backup = NULL;
			return (-1);
		}
		buf[buf_len] = '\0';
		temp = *backup;
		*backup = my_strjoin(*backup, buf);
		free(temp);
		if (ft_strchr(*backup, '\n') || buf_len == 0)
			break ;
	}
	return (0);
}

static char	*take_one_line(char **backup)
{
	char	*one_line;
	char	*temp;
	size_t	len;

	len = 0;
	while ((*backup)[len] && (*backup)[len] != '\n')
		len++;
	if ((*backup)[len] == '\n')
		len++;
	one_line = ft_substr(*backup, 0, len);
	if ((*backup)[len] != '\0')
	{
		temp = *backup;
		*backup = ft_substr(*backup, len, ft_strlen(*backup) - len);
		free(temp);
	}
	else
	{
		temp = *backup;
		free(temp);
		*backup = NULL;
	}
	return (one_line);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*one_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (fill_until_nl_or_eof(fd, &backup) < 0)
		return (NULL);
	if (!backup || backup[0] == '\0')
	{
		free(backup);
		backup = NULL;
		return (NULL);
	}
	one_line = take_one_line(&backup);
	return (one_line);
}
