/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:35:54 by maximemarti       #+#    #+#             */
/*   Updated: 2024/10/02 10:45:02 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*tmp_s1;
	unsigned char	*tmp_s2;
	size_t			i;

	tmp_s1 = (unsigned char *) s1;
	tmp_s2 = (unsigned char *) s2;
	i = 0;
	if (n == 0)
		return (0);
	while (tmp_s1[i] == tmp_s2[i] && i < n - 1)
		i++;
	return (tmp_s1[i] - tmp_s2[i]);
}
