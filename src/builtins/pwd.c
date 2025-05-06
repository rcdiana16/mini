/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:14:50 by diana             #+#    #+#             */
/*   Updated: 2025/03/14 11:07:06 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_our_pwd(t_env *env_mini)
{
	char	*pwd;
	char	*cwd;

	pwd = NULL;
	cwd = calloc(256, 4);
	pwd = get_env_value(env_mini, "PWD");
	if (pwd)
		ft_printf("%s\n", pwd);
	else
		ft_printf("%s\n", getcwd(cwd, 1024));
	free(cwd);
}
