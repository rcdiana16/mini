/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diramire <diramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:12:36 by cosmos            #+#    #+#             */
/*   Updated: 2025/05/07 11:36:01 by diramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	prepare_token(t_command *cmd_info, int i)
{
	char	*new_cmd;

	new_cmd = make_good_cmd2(cmd_info->tokens[i]);
	if (new_cmd)
		cmd_info->tokens[i] = new_cmd;
	if (cmd_info->tokens[i][0] == '$' && cmd_info->tokens[i][1] == ' ')
		return (0);
	return (1);
}

static int	check_ambiguous_redirect(t_command *cmd_info, char *token)
{
	if (cmd_info->c_red_o > 0)
	{
		cmd_info->flag_test = 1;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		if (cmd_info->og_stdin != -1)
		{
			close(cmd_info->og_stdin);
			cmd_info->og_stdin = -1;
		}
		if (cmd_info->og_stdout != -1)
		{
			close(cmd_info->og_stdout);
			cmd_info->og_stdout = -1;
		}
		return (1);
	}
	return (0);
}

static void	replace_or_remove_token(t_command *cmd_info, int i, char *tmp)
{
	if (!tmp)
	{
		replace_token_with_empty(cmd_info, i);
		if (!cmd_info->tokens[i])
			return ;
	}
	else if (tmp[0] != '\0')
		replace_token_with_tmp(cmd_info, i, tmp);
	else
		remove_token(cmd_info, i, tmp);
}

static void	handle_env_var_replacement(t_command *cmd_info, \
			t_env *env_mini, t_shell *shell, int i)
{
	char	*tmp;

	tmp = replace_env_vars(cmd_info->tokens[i], env_mini, shell);
	if (tmp == NULL)
	{
		if (check_ambiguous_redirect(cmd_info, cmd_info->tokens[i]))
			return ;
	}
	replace_or_remove_token(cmd_info, i, tmp);
}

void	handle_double_quotes_and_env_vars(t_command *cmd_info, \
		t_env *env_mini, t_shell *shell, int i)
{
	if (!prepare_token(cmd_info, i))
		return ;
	handle_env_var_replacement(cmd_info, env_mini, shell, i);
}
