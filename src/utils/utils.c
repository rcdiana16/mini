/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:08:21 by cosmos            #+#    #+#             */
/*   Updated: 2025/05/21 18:40:16 by diana            ###   ########.fr       */
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

const char	*parse_sign_and_skip_whitespace(const char *str, int *sign)
{
	*sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*sign = -1;
		str++;
	}
	return (str);
}

long long	ft_atoll(const char *str)
{
	long long	result;
	long long	prev;
	int			sign;

	result = 0;
	str = parse_sign_and_skip_whitespace(str, &sign);
	while (*str >= '0' && *str <= '9')
	{
		prev = result;
		result = result * 10 + (*str - '0');
		if (result / 10 != prev)
		{
			if (sign == 1)
				return (LLONG_MAX);
			else
				return (LLONG_MIN);
		}
		str++;
	}
	return (result * sign);
}

int	ft_arrlen(char **arr)
{
	int	i;

	i = 1;
	if (!arr)
		return (1);
	while (arr && arr[i])
		i++;
	return (i);
}
