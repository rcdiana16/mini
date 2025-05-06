/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:36:41 by maximemarti       #+#    #+#             */
/*   Updated: 2024/11/06 11:06:00 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (1);
}

int	ft_print_s(va_list *ptr)
{
	char	*tmp;
	int		i;

	tmp = va_arg(*ptr, char *);
	if (tmp == NULL)
		tmp = ("(null)");
	i = 0;
	while (tmp[i] != '\0')
	{
		if (write(1, &tmp[i], 1) == -1)
			return (-1);
		i++;
	}
	return (i);
}

int	ft_print_c(va_list *ptr)
{
	char	c;

	c = va_arg(*ptr, int);
	if (write(1, &c, 1) == -1)
		return (-1);
	return (1);
}
