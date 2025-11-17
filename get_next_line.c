/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil--de <sgil--de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 17:15:59 by sgil--de          #+#    #+#             */
/*   Updated: 2025/11/17 18:00:15 by sgil--de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

char	*read_line(int fd)
{
	char	*str;
	char	*temp;
	char	readen[BUFFER_SIZE + 1];
	ssize_t	bytes_read;

	str = NULL;
	bytes_read = 1;
	while (!ft_strchr(str, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, readen, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		readen[bytes_read] = '\0';
		if (!str)
			str = ft_strdup(readen);
		else
		{
			temp = str;
			str = ft_strjoin(temp, readen);
			free(temp);
		}
	}
	return (str);
}

char	*return_line(char **str, char *line_read)
{
	char	*backup;
	size_t	len;

	if (!line_read)
		return (NULL);
	len = 0;
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
	static char	*backup;
	char		*str;
	char		*temp;
	char		*line_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line_read = read_line(fd);
	if (backup && line_read)
	{
		temp = backup;
		backup = ft_strjoin(temp, line_read);
		free(temp);
		free(line_read);
	}
	else if (line_read)
		backup = line_read;
	if (!backup || ft_strlen(backup) == 0)
	{
		free(backup);
		backup = NULL;
		return (NULL);
	}
	backup = return_line(&str, backup);
	return (str);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*str;

// 	fd = open("README.md", O_RDONLY);
// 	if(fd == -1)
// 		return (1);
// 	for (size_t i = 0; i < 6; i++)
// 	{
// 		str = get_next_line(fd);
// 		printf("%lu : %s", i, str);
// 		free(str);
// 	}
// 	return (0);
// }