/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 11:20:16 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/20 23:57:26 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_our_env(t_env *env_mini, char **cmd)
{
	if (cmd[1])
	{
		write(2, "env: '", ft_strlen("env: '"));
		write(2, cmd[1], ft_strlen(cmd[1]));
		write(2, "': No such file or directory\n", \
		ft_strlen("': No such file or directory\n"));
		return (127);
	}
	if (!env_mini)
		return (0);
	while (env_mini)
	{
		if (ft_strncmp(env_mini->value, "\0", 2) != 0)
			ft_printf("%s=%s\n", env_mini->variable, env_mini->value);
		env_mini = env_mini->next;
	}
	return (0);
}
