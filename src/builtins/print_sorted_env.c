/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sorted_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:02:17 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/20 17:45:48 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_env(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

static char	*format_env_var(t_env *var)
{
	char	*line;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp1 = ft_strjoin(var->variable, "=\"");
	if (!tmp1)
		return (NULL);
	tmp2 = ft_strjoin(tmp1, var->value);
	free(tmp1);
	if (!tmp2)
		return (NULL);
	tmp3 = ft_strjoin(tmp2, "\"");
	free(tmp2);
	if (!tmp3)
		return (NULL);
	line = ft_strjoin("declare -x ", tmp3);
	free(tmp3);
	return (line);
}

static char	*build_env_line(t_env *var)
{
	if (var->value)
		return (format_env_var(var));
	return (ft_strjoin("declare -x ", var->variable));
}

static void	sort_env_list(char **list, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strncmp(list[i], list[j], 1000) > 0)
			{
				tmp = list[i];
				list[i] = list[j];
				list[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	print_sorted_env(t_env *env)
{
	int		count;
	int		i;
	char	**list;

	count = count_env(env);
	list = malloc(sizeof(char *) * (count + 1));
	if (!list)
		return (-1);
	i = 0;
	while (i < count && env)
	{
		list[i] = build_env_line(env);
		env = env->next;
		i++;
	}
	list[i] = NULL;
	sort_env_list(list, count);
	print_and_free_list(list);
	return (0);
}
