/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:58:35 by maximemarti       #+#    #+#             */
/*   Updated: 2024/11/06 11:06:24 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_h(unsigned int num)
{
	int	remainder;
	int	count;
	int	result;

	count = 0;
	if (num >= 16)
	{
		result = ft_print_h(num / 16);
		if (result == -1)
			return (-1);
		count += result;
	}
	remainder = num % 16;
	if (remainder < 10)
		result = ft_putchar(remainder + '0');
	else
		result = ft_putchar(remainder - 10 + 'a');
	if (result == -1)
		return (-1);
	count++;
	return (count);
}

static int	ft_print_bh(unsigned int num)
{
	int	remainder;
	int	count;
	int	result;

	count = 0;
	if (num >= 16)
	{
		result = ft_print_bh(num / 16);
		if (result == -1)
			return (-1);
		count += result;
	}
	remainder = num % 16;
	if (remainder < 10)
		result = ft_putchar(remainder + '0');
	else
		result = ft_putchar(remainder - 10 + 'A');
	if (result == -1)
		return (-1);
	count++;
	return (count);
}

int	ft_print_x(va_list *ptr)
{
	unsigned int	num;

	num = va_arg(*ptr, unsigned int);
	return (ft_print_h(num));
}

int	ft_print_bx(va_list *ptr)
{
	unsigned int	num;

	num = va_arg(*ptr, unsigned int);
	return (ft_print_bh(num));
}
