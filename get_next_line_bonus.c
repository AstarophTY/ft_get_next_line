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

char	*join_and_free(char *temp, char *readen, char *str)
{
	temp = str;
	str = ft_strjoin(temp, readen);
	free(temp);
	return (str);
}

char	*read_line(int fd)
{
	char	*str;
	char	*temp;
	char	*readen;
	ssize_t	bytes_read;

	str = NULL;
	bytes_read = 1;
	temp = NULL;
	readen = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!readen)
		return (NULL);
	while (!ft_strchr(str, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, readen, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		readen[bytes_read] = '\0';
		if (!str)
			str = ft_strdup(readen);
		else
			str = join_and_free(temp, readen, str);
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

char	*get_next_line(int fd)
{
	static char	*backup[1024];
	char		*str;
	char		*temp;
	char		*line_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line_read = read_line(fd);
	if (backup[fd] && line_read)
	{
		temp = backup[fd];
		backup[fd] = ft_strjoin(temp, line_read);
		free(temp);
		free(line_read);
	}
	else if (line_read)
		backup[fd] = line_read;
	if (!backup[fd] || ft_strlen(backup[fd]) == 0)
	{
		free(backup[fd]);
		backup[fd] = NULL;
		return (NULL);
	}
	backup[fd] = return_line(&str, backup[fd]);
	return (str);
}
