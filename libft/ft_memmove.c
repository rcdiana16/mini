/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:53:07 by maximemarti       #+#    #+#             */
/*   Updated: 2024/10/05 12:31:07 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	const unsigned char	*tmp_src;
	unsigned char		*tmp_dst;

	if (!dst && !src)
		return (NULL);
	if (len == 0)
		return (dst);
	tmp_src = (const unsigned char *) src;
	tmp_dst = (unsigned char *) dst;
	i = 0;
	if (tmp_src < tmp_dst)
	{
		while (len-- > 0)
			tmp_dst[len] = tmp_src[len];
	}
	else
	{
		while (i < len)
		{
			tmp_dst[i] = tmp_src[i];
			i++;
		}
	}
	return (dst);
}
