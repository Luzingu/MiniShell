/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:32:44 by mcaquart          #+#    #+#             */
/*   Updated: 2024/07/13 12:10:03 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ss_reading_file(int fd, char *storage)
{
	char	tmp[BUFFER_SIZE + 1];
	long	i;

	i = -1;
	while (++i <= BUFFER_SIZE)
		tmp[i] = '\0';
	i = 1;
	while (!ft_strchr(tmp, '\n') && i)
	{
		i = read(fd, tmp, BUFFER_SIZE);
		if (i < 0 || (!i && !storage))
			return (NULL);
		tmp[i] = '\0';
		if (!storage)
			storage = ft_strdup(tmp);
		else
			storage = ft_strjoin(storage, tmp);
		if (!storage)
			return (NULL);
	}
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage[FILE_AMOUNT_TO_READ];
	char		*current_line;
	char		*backup;
	int			i;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	storage[fd] = ss_reading_file(fd, storage[fd]);
	if (!storage[fd])
		return (NULL);
	i = 0;
	while (storage[fd][i] != '\n' && storage[fd][i])
		++i;
	if (storage[fd][i] == '\n')
		++i;
	current_line = ft_substr(storage[fd], 0, i);
	backup = ft_substr(storage[fd], i, ft_strlen(storage[fd]) - i);
	free(storage[fd]);
	storage[fd] = backup;
	return (current_line);
}
