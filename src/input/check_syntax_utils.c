/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diramire <diramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 22:14:53 by diana             #+#    #+#             */
/*   Updated: 2025/05/07 11:34:51 by diramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	return_syntax_error(char **bad_token, char *token, int code)
{
	if (bad_token)
		*bad_token = token;
	return (code);
}

int	check_initial_syntax(char **cmd, char **bad_token)
{
	if (!cmd[0])
		return (-1);
	if (ft_strncmp(cmd[0], ">>", 3) == 0)
		return (return_syntax_error(bad_token, cmd[0], 2));
	if (ft_strncmp(cmd[0], "\">>\"", 5) == 0)
		return (return_syntax_error(bad_token, cmd[0], 4));
	if (ft_strncmp(cmd[0], "'<<'", 5) == 0)
		return (return_syntax_error(bad_token, cmd[0], 3));
	if (ft_strncmp(cmd[0], "|", 2) == 0)
		return (return_syntax_error(bad_token, cmd[0], 0));
	return (-1);
}

int	is_redirection(char *token)
{
	if (!token)
		return (0);
	return (ft_strncmp(token, ">", 1) == 0 || \
			ft_strncmp(token, ">>", 2) == 0 || \
			ft_strncmp(token, "<", 1) == 0 || \
			ft_strncmp(token, "<<", 2) == 0);
}
