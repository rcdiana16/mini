/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 21:08:20 by cosmos            #+#    #+#             */
/*   Updated: 2025/05/22 16:47:56 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	calculate_shlvl(const char *shlvl_str)
{
	int	shlvl;

	if (!shlvl_str || !*shlvl_str)
		return (1);
	shlvl = ft_atoi(shlvl_str);
	if (shlvl < 0)
		return (0);
	if (shlvl >= 999)
	{
		write(2, "warning: shell level (", 21);
		ft_putnbr_fd(shlvl + 1, 2);
		write(2, ") too high, resetting to 1\n", 26);
		return (1);
	}
	return (shlvl + 1);
}

static void	handle_shlvl(t_env **env_list)
{
	char	*shlvl_str;
	int		shlvl;
	char	*new_shlvl;

	shlvl_str = get_env_value(*env_list, "SHLVL");
	shlvl = calculate_shlvl(shlvl_str);
	new_shlvl = ft_itoa(shlvl);
	if (new_shlvl)
	{
		update_or_append_node(env_list, "SHLVL", new_shlvl);
		free(new_shlvl);
	}
}

static void	init_default_env(t_env **env_list)
{
	char	cwd[PATH_MAX];
	char	*ret;

	ret = getcwd(cwd, sizeof(cwd));
	if (ret != NULL)
		append_node(env_list, "PWD", cwd);
	handle_shlvl(env_list);
	append_node(env_list, "_", "./minishell");
}

t_env	*get_list_env(char **envp, t_env *env_list)
{
	int		i;
	char	*equal_sign;

	env_list = NULL;
	if (!envp || !envp[0])
	{
		init_default_env(&env_list);
		return (env_list);
	}
	i = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			if (ft_strncmp(envp[i], "OLDPWD", 7) != 0)
				append_node(&env_list, envp[i], equal_sign + 1);
			*equal_sign = '=';
		}
		i++;
	}
	handle_shlvl(&env_list);
	return (env_list);
}

t_env	*initialize_environment(char **env, t_env *env_list)
{
	return (get_list_env(env, env_list));
}
