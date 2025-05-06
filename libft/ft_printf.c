/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:46:22 by maximemarti       #+#    #+#             */
/*   Updated: 2024/11/06 11:06:43 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	initilize_var(t_printf *opt)
{
	opt[0] = (t_printf){.symbol = 'c', .f = ft_print_c};
	opt[1] = (t_printf){.symbol = 's', .f = ft_print_s};
	opt[2] = (t_printf){.symbol = 'd', .f = ft_print_i};
	opt[3] = (t_printf){.symbol = 'i', .f = ft_print_i};
	opt[4] = (t_printf){.symbol = 'u', .f = ft_print_ui};
	opt[5] = (t_printf){.symbol = 'x', .f = ft_print_x};
	opt[6] = (t_printf){.symbol = 'X', .f = ft_print_bx};
	opt[7] = (t_printf){.symbol = 'p', .f = print_ptr};
	opt[8] = (t_printf){.symbol = '\0', .f = NULL};
}

static int	find_func(const char *format, t_printf *opt)
{
	int	y;

	y = 0;
	while (opt[y].symbol)
	{
		if (*format == opt[y].symbol)
			return (y);
		y++;
	}
	return (-1);
}

static int	handle_percent(const char *fo, t_printf *opt, va_list *ptr, int *i)
{
	int	find_result;

	find_result = find_func(&fo[*i + 1], opt);
	if (find_result >= 0)
		return (opt[find_result].f(ptr));
	if (write(1, &fo[*i + 1], 1) == -1)
		return (-1);
	return (1);
}

static int	parse_format(const char *format, t_printf *opt, va_list *ptr)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			count += handle_percent(format, opt, ptr, &i);
			if (count == -1)
				return (-1);
			i += 2;
		}
		else
		{
			if ((write(1, &format[i], 1)) == -1)
				return (-1);
			count++;
			i++;
		}
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list		ptr;
	t_printf	opt[9];
	int			count;

	if (format == NULL || (format[0] == '%' && format[1] == '\0'))
		return (-1);
	initilize_var(opt);
	va_start(ptr, format);
	count = parse_format(format, opt, &ptr);
	va_end(ptr);
	return (count);
}
