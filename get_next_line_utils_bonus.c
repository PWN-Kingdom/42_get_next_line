/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: white <white@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 21:09:01 by white             #+#    #+#             */
/*   Updated: 2020/06/29 18:06:59 by white            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}

char	*ft_strjoin_and_free(char **s1, char const *s2)
{
	char	*src;
	size_t	i;
	size_t	j;

	i = s1[0] != NULL ? ft_strlen(s1[0]) : 0;
	i += s2 != NULL ? ft_strlen(s2) : 0;
	if ((src = (char *)malloc(i + 1)) == NULL)
	{
		free(s1[0]);
		return (NULL);
	}
	i = 0;
	if (s1[0] != NULL)
		while (s1[0][i] != '\0')
		{
			src[i] = s1[0][i];
			i++;
		}
	j = 0;
	if (s2 != NULL)
		while (s2[j] != '\0')
			src[i++] = s2[j++];
	src[i] = '\0';
	free(s1[0]);
	return (src);
}
