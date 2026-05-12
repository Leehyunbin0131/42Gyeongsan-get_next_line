/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunlee <hyunlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 14:40:52 by hyunlee           #+#    #+#             */
/*   Updated: 2026/05/12 16:51:32 by hyunlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2);

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
		*backup = ft_strjoin(*backup, buf);
		free(temp);
		if (ft_strchr(*backup, '\n') || buf_len == 0)
			break ;
	}
	return (0);
}

static char	*take_one_line(char **backup)
{
	char		*one_line;
	char		*temp;
	size_t		len;

	len = find_n_index(*backup, '\n');
	if ((*backup)[len] == '\n')
		len = len + 1;
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
