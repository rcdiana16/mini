/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_and_split_cmd_utils_bis.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 23:19:38 by diana             #+#    #+#             */
/*   Updated: 2025/05/05 23:20:05 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*handle_syntax_errors(t_command *cmd_info, \
			t_shell *shell, int ret, char *bad_token)
{
	if (ret == 0 || ret == 2 || ret == 3 || ret == 4)
	{
		if (ret == 0 || ret == 2)
			ret = 2;
		return (handle_token_error(cmd_info, shell, ret, bad_token));
	}
	return (cmd_info);
}

int	is_invalid_single_token(char *token)
{
	return (ft_strncmp(token, ">", 1) == 0 || \
	ft_strncmp(token, "<", 1) == 0 || ft_strncmp(token, "<<", 2) == 0);
}

void	process_command_tokens(t_command *cmd_info)
{
	int	i;

	i = 0;
	while (cmd_info->tokens[i])
	{
		count_redirections(cmd_info->tokens[i], cmd_info);
		remove_newline(cmd_info->tokens[i]);
		i++;
	}
}

char	**allocate_new_tokens(char **tokens)
{
	int	total;

	total = 0;
	while (tokens[total])
		total++;
	return (calloc(total * 2 + 1, sizeof(char *)));
}
