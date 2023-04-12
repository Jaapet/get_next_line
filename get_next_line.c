/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndesprez <ndesprez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:35:17 by ndesprez          #+#    #+#             */
/*   Updated: 2023/04/12 17:29:07 by ndesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// free the void* objects and returns NULL
static char	*free_temps(char *a, char *b)
{
	free(a);
	free(b);
	return (NULL);
}

static char	*read_line(int fd, char *save)
{
	char	*buffer;
	int		readed;

	if (!save)
		save = (char *)ft_calloc(1, sizeof(char));
	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!save || buffer)
		return (free_temps(save, buffer));
	readed = 1;
	while (readed)
	{
		//ft_bzero(buffer, BUFFER_SIZE);
		readed = read(fd, buffer, BUFFER_SIZE);
		if ((!save[0] && !readed) || readed == -1)
			return (free_temps(save, buffer));
		else if (!readed)
			break ;
		save = ft_strjoin_bufs(save, buffer);
		if (!save)
			return (free_temps(save, buffer));
		if (readed < BUFFER_SIZE || (save[ft_strchri(save, '\n')] == '\n'))
			break ;
	}
	free(buffer);
	return (save);
}

static char	*getline(char *src)
{
	char	*line;
	int		i;

	line = (char *)calloc(ft_strchri(src, '\n') + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (i <= ft_strchri(src, '\n'))
	{
		line[i] = src[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*update_save(char *save)
{
	char	*new_save;
	int		size;
	int		index;
	int		i;

	size = ft_strchri(save, '\0') - ft_strchri(save, '\n');
	if (!size)
		return (NULL);
	new_save = (char *)ft_calloc(size, sizeof(char));
	index = ft_strchri(save, '\n');
	i = 0;
	while (i <= index)
	{
		new_save[i] = save[index];
		i++;
		index++;
	}
	new_save[i] = '\0';
	free(save);
	return (new_save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	save = read_line(fd, save);
	if (!save)
		return (NULL);
	line = getline(save);
	if (!line)
		return (NULL);
	save = update_save(save);
	return (line);
}
