/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:42:58 by ldubuche          #+#    #+#             */
/*   Updated: 2022/02/08 12:42:58 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*__get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*current_read;
	int			len;

	if (fd < 0 || fd > FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	current_read = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!current_read)
		return (NULL);
	len = read(fd, current_read, BUFFER_SIZE);
	if (len < 0)
		return (__free_str(current_read));
	current_read[len] = '\0';
	if (len > 0)
	{
		buffer = __fill_buffer(current_read, buffer, fd);
		if (buffer == NULL)
			return (__free_str(current_read));
	}
	else if (len == 0 && (!buffer || buffer[0] == '\0'))
	{
		__free_str(buffer);
		return (__free_str(current_read));
	}
	return (__r_value(&buffer, current_read));
}

char	*__fill_buffer(char *current_read, char *buffer, int fd)
{
	int		len;

	len = 1;
	if (!buffer)
	{
		buffer = __strdup("");
		if (!buffer)
			return (__free_str(buffer));
	}
	buffer = __buffjoin(buffer, current_read, buffer);
	if (!buffer)
		return (NULL);
	while (__strrchr(buffer, '\n') == NULL && len != 0)
	{
		len = read(fd, current_read, BUFFER_SIZE);
		if (len < 0)
			return (NULL);
		current_read[len] = '\0';
		buffer = __buffjoin(buffer, current_read, buffer);
		if (!buffer)
			return (NULL);
	}
	return (buffer);
}

char	*__r_value(char **buffer, char *current_read)
{
	int		len;
	char	*retour;
	char	*nl_position;

	__free_str(current_read);
	nl_position = __strrchr(*buffer, '\n');
	if (nl_position)
		len = nl_position - *buffer + 1;
	else
		len = __strlen(*buffer);
	retour = (char *) malloc(sizeof(char) * len + 1);
	if (!retour)
		return (__free_str(*buffer));
	__fill_retour(buffer, len, retour);
	if (nl_position)
		*buffer = __buffjoin("", nl_position + 1, *buffer);
	else
		*buffer = __buffjoin("", *buffer + len, *buffer);
	if (!(*buffer))
		return (__free_str(*buffer));
	return (retour);
}

char	*__buffjoin(char *buffer, char *str, char *to_free)
{
	buffer = __strjoin(buffer, str);
	if (!buffer)
		return (NULL);
	free(to_free);
	return (buffer);
}

void	__fill_retour(char **buffer, int len, char *retour)
{
	int	i;

	i = 0;
	while (len--)
	{
		retour[i] = (*buffer)[i];
		i++;
	}
	retour[i] = '\0';
}
