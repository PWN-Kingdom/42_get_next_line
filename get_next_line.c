/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: white <white@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 20:56:40 by white             #+#    #+#             */
/*   Updated: 2020/06/29 18:00:22 by white            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int			ft_check_sumbol(char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		if (src[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static int			ft_init_string(int fd, char **string)
{
	char	*buf;
	int		len;
	int		return_value;

	if ((buf = (char *)malloc(BUFFER_SIZE + 1)) == NULL)
		return (-1);
	while ((len = read(fd, buf, BUFFER_SIZE)) >= 0)
	{
		return_value = 2;
		buf[len] = '\0';
		if ((*string = ft_strjoin_and_free(string, buf)) == NULL)
			return_value = -1;
		else if (len < BUFFER_SIZE)
			return_value = 0;
		else if (ft_check_sumbol(*string) != 0)
			return_value = 1;
		if (return_value != 2)
		{
			free(buf);
			return (return_value);
		}
	}
	free(buf);
	return (-1);
}

static int			ft_init_line(char *string, char **line)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (string[i] != '\n' && string[i] != '\0')
		i++;
	str = (char *)malloc(i + 1);
	if (str == NULL)
	{
		*line = NULL;
		return (-1);
	}
	while (j < i)
	{
		str[j] = string[j];
		j++;
	}
	str[j] = '\0';
	*line = str;
	return (1);
}

static int			ft_edit_string(char **string)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	while (string[0][i] != '\n' && string[0][i] != '\0')
		i++;
	if (string[0][i] == '\0')
	{
		free(*string);
		*string = NULL;
		return (0);
	}
	j = ++i;
	while (string[0][i] != '\0')
		i++;
	if ((str = (char *)malloc(i - j + 1)) == NULL)
		return (-1);
	i = 0;
	while (string[0][j] != '\0')
		str[i++] = string[0][j++];
	str[i] = '\0';
	free(*string);
	*string = str;
	return (1);
}

int					get_next_line(int fd, char **line)
{
	static char	*string;
	int			result;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	if (string == NULL || ft_check_sumbol(string) == 0)
		if ((result = ft_init_string(fd, &string)) == -1)
			return (-1);
	if (ft_init_line(string, line) == -1 || ft_edit_string(&string) == -1)
	{
		free(string);
		free(*line);
		return (-1);
	}
	if (string == NULL && result == 0)
		return (0);
	return (1);
}
