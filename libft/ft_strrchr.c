/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:33:03 by maximemarti       #+#    #+#             */
/*   Updated: 2024/10/01 22:51:34 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*res;

	i = 0;
	res = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			res = ((char *) &s[i]);
		i++;
	}
	if (s[i] == (char) c)
		res = ((char *) &s[i]);
	return (res);
}
