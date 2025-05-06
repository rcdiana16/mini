/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:38:57 by maximemarti       #+#    #+#             */
/*   Updated: 2024/11/06 11:06:19 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	help_ptr(uintptr_t ptr)
{
	int	remainder;
	int	count;

	remainder = 0;
	count = 0;
	if (ptr >= 16)
	{
		count = help_ptr(ptr / 16);
		if (count == -1)
			return (-1);
	}
	remainder = ptr % 16;
	if (remainder < 10)
	{
		if (ft_putchar(remainder + '0') == -1)
			return (-1);
		count++;
	}
	else
	{
		if (ft_putchar(remainder - 10 + 'a') == -1)
			return (-1);
		count++;
	}
	return (count);
}

int	print_ptr(va_list *ptr)
{
	uintptr_t	prt;
	int			count;

	prt = va_arg(*ptr, uintptr_t);
	if (write(1, "0x", 2) == -1)
		return (-1);
	count = help_ptr(prt);
	if (count == -1)
		return (-1);
	return (count + 2);
}
