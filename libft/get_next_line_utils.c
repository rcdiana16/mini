/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:21:33 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/05 16:38:10 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_strlen_gnl(char *s1)
{
	ssize_t	i;

	i = 0;
	while (s1[i])
		i++;
	return (i);
}

static char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = (char *)malloc(sizeof(char) \
	* (ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		new_str[i++] = s2[j++];
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new_str;

	if (!s1)
	{
		s1 = (char *)malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	new_str = ft_strjoin_gnl(s1, s2);
	if (s1)
		free(s1);
	return (new_str);
}

char	*cleanup(char **buffer)
{
	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (NULL);
}

int	should_stop(int fd, char *buffer)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (1);
	if (!buffer || !buffer[0])
		return (1);
	return (0);
}
