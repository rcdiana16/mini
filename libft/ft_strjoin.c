/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:09:31 by maximemarti       #+#    #+#             */
/*   Updated: 2024/10/02 18:22:34 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;
	size_t	len_s1;
	size_t	len_s2;
	size_t	total_len;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	total_len = len_s1 + len_s2 + 1;
	tmp = (char *)malloc(total_len);
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, s1, total_len);
	ft_strlcat(tmp, s2, total_len);
	return (tmp);
}
