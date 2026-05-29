/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunlee <hyunlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 14:40:52 by hyunlee           #+#    #+#             */
/*   Updated: 2026/05/20 17:54:09 by hyunlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	freemem(char **mem)
{
	free(*mem);
	*mem = NULL;
}

static char	*backup_in_buf(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*arr;

	if (!s1)
		s1_len = 0;
	else
	{
		s1_len = ft_strlen(s1);
	}
	s2_len = ft_strlen(s2);
	arr = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (arr == NULL)
		return (NULL);
	ft_memcpy(arr, s1, s1_len);
	ft_memcpy(arr + s1_len, s2, s2_len + 1);
	free(s1);
	return (arr);
}

static char	*read_line(char *backup, int fd)
{
	int		buf_len;
	char	*buf;

	buf_len = 0;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (!backup || !ft_strchr(backup, '\n'))
	{
		buf_len = read(fd, buf, BUFFER_SIZE);
		if (buf_len == -1)
			freemem(&backup);
		if (buf_len <= 0)
			break ;
		buf[buf_len] = '\0';
		backup = backup_in_buf(backup, buf);
	}
	freemem(&buf);
	if (!backup || *backup == '\0')
	{
		freemem(&backup);
		return (NULL);
	}
	return (backup);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*one_line;
	int			index;
	char		*temp;

	index = 0;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	backup = read_line(backup, fd);
	if (!backup)
		return (NULL);
	while (backup[index] != '\n' && backup[index] != '\0')
		index++;
	temp = backup;
	one_line = ft_substr(backup, 0, index + 1);
	backup = ft_substr(backup, index + 1, (ft_strlen(backup) - index));
	freemem(&temp);
	return (one_line);
}
