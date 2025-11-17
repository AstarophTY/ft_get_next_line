/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil--de <sgil--de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 17:15:59 by sgil--de          #+#    #+#             */
/*   Updated: 2025/11/17 14:47:57 by sgil--de         ###   ########.fr       */
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

	str = NULL;
	readen[BUFFER_SIZE] = '\0';
	while (!ft_strchr(str, (int)'\n') && !ft_strchr(str, (int)'\0') && read(fd, readen, BUFFER_SIZE) > 0)
	{
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

char	*return_line(char **str, int fd)
{
	char	*temp;
	size_t	len;
	char	*backup;

	len = 0;
	temp = read_line(fd);
	while (temp[len] && (temp[len] != '\n' || temp[len] == '\0'))
		len++;
	*str = ft_substr(temp, 0, len);
	backup = ft_substr(temp, len, ft_strlen(temp) - len);
	free(temp);
	return (backup);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*str;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (backup && (ft_strchr(backup, (int)'\n') || ft_strchr(backup, (int)'\0')))
	{
		str = ft_substr(backup, 0, ft_strlen(backup) - ft_strlen(ft_strchr(backup, (int)'\n')));
		temp = ft_substr(backup, ft_strlen(str), ft_strlen(backup) - ft_strlen(str));
		free(backup);
		backup = temp;
		return (str);
	}
	backup = return_line(&str, fd);
	if (str && ft_strlen(str) == 0)
	{
		free(str);
		return (NULL);
	}
	return (str);
}

int	main(void)
{
	int		fd;
	char	*str;

	fd = open("README.md", O_RDONLY);
	if(fd == -1)
		return (1);
	for (size_t i = 0; i < 4; i++)
	{
		str = get_next_line(fd);
		printf("%lu : %s\n", i, str);
		free(str);
	}
	return (0);
}