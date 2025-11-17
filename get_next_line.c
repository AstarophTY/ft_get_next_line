/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil--de <sgil--de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 17:15:59 by sgil--de          #+#    #+#             */
/*   Updated: 2025/11/17 13:00:46 by sgil--de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

static char	*ft_get_str(int fd)
{
	char	readen[BUFFER_SIZE];
	size_t	len;
	char	*str;
	char	*temp;

	str = NULL;
	temp = NULL;
	len = read(fd, readen, sizeof(readen));
	if (len == -1)
		return (NULL);
	while (!ft_strchr(str, (int)'\n') && len > 0)
	{
		if (!str)
			str = ft_strdup(readen);
		else
		{
			temp = str;
			str = ft_strjoin(temp, readen);
			free(temp);
		}
		len = read(fd, readen, sizeof(readen));
	}
	return (str);
}

char	*ft_return_line(char *str)
{
	size_t	len;
	char	*temp;
	char	*backup;

	len = 0;
	temp = ft_strdup(str);
	while (str[len] != '\n')
		len++;
	str = ft_substr(temp, 0, len + 1);
	backup = ft_substr(temp, len + 1, 1000000);
	free(temp);
	return (backup);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*str;
	char		*temp;

	if (backup && ft_strchr(backup, (int)'\n'))
	{
		backup = ft_return_line(str);
	}
	else if (backup)
	{
		temp = ft_get_str(fd);
		str = ft_strjoin(backup, temp);
		backup = ft_return_line(str);
		return (str);
	}
	else
	{
		temp = ft_get_str(fd);
		backup = ft_return_line(temp);
		str = ft_return_line(temp);
	}
	return (str);
}

int	main(void)
{
	int	fd;
	char	*str;

	fd = open("text.txt", O_RDONLY);
	if(fd == -1)
		return (1);
	for (size_t i = 0; i < 4; i++)
	{
		str = get_next_line(fd);
	printf("%lu : %s", i, str);
	free(str);
	}
	
	return (0);
}