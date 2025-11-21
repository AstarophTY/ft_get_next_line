/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil--de <sgil--de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 17:15:59 by sgil--de          #+#    #+#             */
/*   Updated: 2025/11/19 16:37:48 by sgil--de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_and_join(int fd, char *str, char *readen, ssize_t *bytes_read)
{
	char	*temp;

	*bytes_read = read(fd, readen, BUFFER_SIZE);
	if (*bytes_read <= 0)
		return (str);
	readen[*bytes_read] = '\0';
	if (!str)
		return (ft_strdup(readen));
	temp = str;
	str = ft_strjoin(temp, readen);
	free(temp);
	return (str);
}

char	*read_line(int fd, int *error)
{
	char	*str;
	char	*readen;
	ssize_t	bytes_read;

	str = NULL;
	*error = 0;
	bytes_read = 1;
	readen = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!readen)
		return (NULL);
	while (!ft_strchr(str, '\n') && bytes_read > 0)
		str = read_and_join(fd, str, readen, &bytes_read);
	if (bytes_read < 0)
	{
		*error = 1;
		free(str);
		str = NULL;
	}
	free(readen);
	return (str);
}

char	*return_line(char **str, char *line_read)
{
	char	*backup;
	size_t	len;

	len = 0;
	if (!line_read)
		return (NULL);
	while (line_read[len] && line_read[len] != '\n')
		len++;
	if (line_read[len] == '\n')
	{
		*str = ft_substr(line_read, 0, len + 1);
		backup = ft_strdup(line_read + len + 1);
	}
	else
	{
		*str = ft_strdup(line_read);
		backup = NULL;
	}
	free(line_read);
	return (backup);
}

char	*merge_backup(char *backup, char *line_read)
{
	char	*temp;

	if (backup && line_read)
	{
		temp = backup;
		backup = ft_strjoin(temp, line_read);
		free(temp);
		free(line_read);
	}
	else if (line_read)
		backup = line_read;
	return (backup);
}

char	*get_next_line(int fd)
{
	static char	*backup[1024];
	char		*str;
	char		*line_read;
	int			error;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line_read = read_line(fd, &error);
	if (error)
	{
		free(backup[fd]);
		backup[fd] = NULL;
		return (NULL);
	}
	backup[fd] = merge_backup(backup[fd], line_read);
	if (!backup[fd] || ft_strlen(backup[fd]) == 0)
	{
		free(backup[fd]);
		backup[fd] = NULL;
		return (NULL);
	}
	backup[fd] = return_line(&str, backup[fd]);
	return (str);
}
