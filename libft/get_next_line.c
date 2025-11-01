/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:59:39 by dikhalil          #+#    #+#             */
/*   Updated: 2025/09/10 11:59:23 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*free_and_return(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

static char	*ft_extract_line(char *buffer)
{
	char	*line;
	int		i;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_substr_gnl(buffer, 0, i);
	if (!line)
		return (NULL);
	return (line);
}

static char	*ft_extract_leftover(char *buffer, char *line)
{
	char	*leftover;
	int		buflen;
	int		linelen;

	if (!buffer)
		return (NULL);
	buflen = ft_strlen_gnl(buffer);
	if (!line)
		return (NULL);
	linelen = ft_strlen_gnl(line);
	leftover = ft_substr_gnl(buffer, linelen, buflen - linelen);
	if (!leftover || !leftover[0])
		return (free_and_return(&leftover));
	return (leftover);
}

static char	*read_until_newline(int fd, char *leftover, char *buf)
{
	char	*buffer;
	ssize_t	bytes;

	if (leftover)
		buffer = ft_strdup_gnl(leftover);
	else
		buffer = ft_strdup_gnl("");
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (!ft_strchr_gnl(buffer, '\n') && bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
			return (free_and_return(&buffer));
		buf[bytes] = '\0';
		buffer = ft_strjoin_gnl(buffer, buf);
		if (!buffer)
			return (NULL);
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*buf;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	buffer = read_until_newline(fd, leftover, buf);
	free(buf);
	if (!buffer)
		return (free_and_return(&leftover));
	line = ft_extract_line(buffer);
	if (!line)
		return (free_and_return(&buffer));
	if (leftover)
		free(leftover);
	leftover = ft_extract_leftover(buffer, line);
	free(buffer);
	if ((!line || !*line) && !leftover)
		return (free_and_return(&line));
	return (line);
}
