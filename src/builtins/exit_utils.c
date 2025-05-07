/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:35:47 by diana             #+#    #+#             */
/*   Updated: 2025/05/07 14:45:17 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_exit_argument_error(t_command *cmd_info)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	cmd_info->exit_code = 1;
}

const char	*get_llong_limit_and_skip_zeros(char *arg, int *start_index)
{
	const char	*max_llong;

	*start_index = 0;
	if (arg[0] == '-')
		max_llong = "9223372036854775808";
	else
		max_llong = "9223372036854775807";
	if (arg[0] == '-' || arg[0] == '+')
		(*start_index)++;
	while (arg[*start_index] == '0')
		(*start_index)++;
	return (max_llong);
}

int	would_overflow_longlong(char *arg)
{
	int			i;
	int			j;
	size_t		len;
	const char	*max_llong;

	max_llong = get_llong_limit_and_skip_zeros(arg, &i);
	len = 0;
	while (arg[i + len])
		len++;
	if (len > ft_strlen(max_llong))
		return (1);
	if (len == ft_strlen(max_llong))
	{
		j = 0;
		while (arg[i + j])
		{
			if (arg[i + j] > max_llong[j])
				return (1);
			else if (arg[i + j] < max_llong[j])
				return (0);
			j++;
		}
	}
	return (0);
}

int	validate_exit_argument(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '-' || arg[0] == '+')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	if (would_overflow_longlong(arg))
		return (0);
	return (1);
}
