/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_di.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:52:38 by maximemarti       #+#    #+#             */
/*   Updated: 2024/11/06 11:06:13 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	help_i(long int num)
{
	int	count;
	int	result;

	count = 0;
	if (num < 0)
	{
		result = ft_putchar('-');
		if (result == -1)
			return (-1);
		count++;
		num = -num;
	}
	if (num > 9)
	{
		result = help_i(num / 10);
		if (result == -1)
			return (-1);
		count += result;
	}
	result = ft_putchar(num % 10 + '0');
	if (result == -1)
		return (-1);
	count++;
	return (count);
}

int	ft_print_i(va_list *ptr)
{
	int	num;
	int	count;

	num = va_arg(*ptr, int);
	count = help_i(num);
	return (count);
}

static int	help_ui(unsigned int num)
{
	int	count;
	int	result;

	count = 0;
	if (num > 9)
	{
		result = help_ui(num / 10);
		if (result == -1)
			return (-1);
		count += result;
	}
	result = ft_putchar(num % 10 + '0');
	if (result == -1)
		return (-1);
	count++;
	return (count);
}

int	ft_print_ui(va_list *ptr)
{
	unsigned int	num;
	int				count;

	num = va_arg(*ptr, unsigned int);
	count = help_ui(num);
	return (count);
}
