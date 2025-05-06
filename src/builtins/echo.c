/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 21:32:03 by cosmos            #+#    #+#             */
/*   Updated: 2025/04/16 00:39:33 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_echo(char **cmd, int i, int newline)
{
	while (cmd[i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (newline != 0)
		write(1, "\n", 1);
}

int	is_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_our_echo(char **cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (!cmd[1])
	{
		write(1, "\n", 1);
		return ;
	}
	while (cmd[i] && is_n_flag(cmd[i]))
	{
		newline = 0;
		i++;
	}
	print_echo(cmd, i, newline);
}
