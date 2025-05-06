/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:08:21 by cosmos            #+#    #+#             */
/*   Updated: 2025/04/28 11:13:36 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	process_exit_code(char *result, int j, t_shell *shell)
{
	char	*var_value;
	char	*tmp;

	var_value = ft_itoa(shell->exit_code);
	tmp = var_value;
	while (*tmp)
		result[j++] = *tmp++;
	free(var_value);
	return (j);
}

char	*get_env_value(t_env *env_mini, const char *var)
{
	if (var != NULL)
	{
		while (env_mini != NULL)
		{
			if ((ft_strncmp(env_mini->variable, var, \
				ft_strlen(var) + 1)) == 0)
				return (env_mini->value);
			env_mini = env_mini->next;
		}
	}
	return (NULL);
}

long long	ft_atoll(const char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}
