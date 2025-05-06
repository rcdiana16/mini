/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 11:20:16 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/19 12:19:27 by maximemarti      ###   ########.fr       */
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
	while (env_mini)
	{
		ft_printf("%s=%s\n", env_mini->variable, env_mini->value);
		env_mini = env_mini->next;
	}
	return (0);
}
