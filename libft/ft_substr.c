/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:15:03 by maximemarti       #+#    #+#             */
/*   Updated: 2024/10/02 18:07:28 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tmp;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	tmp = (char *)malloc(len + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < len && s[start])
	{
		tmp[i] = s[start];
		i++;
		start++;
	}
	tmp[i] = '\0';
	return (tmp);
}
