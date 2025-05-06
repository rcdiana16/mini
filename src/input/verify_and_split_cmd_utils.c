/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_and_split_cmd_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2025/04/23 10:50:53 by diana             #+#    #+#             */
/*   Updated: 2025/04/23 17:42:23 by diana            ###   ########.fr       */
=======
/*   Created: 2025/04/27 22:24:34 by diana             #+#    #+#             */
/*   Updated: 2025/05/05 23:23:27 by diana            ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

<<<<<<< HEAD
t_command	*handle_token_error(t_command *cmd_info, t_shell *shell, \
			int code, char *bad_token)
{
	if (!bad_token)
		ft_putstr_fd("minishell: syntax error near unexpected token \
		`newline'\n", 2);
	else
		ft_putstr_fd("minishell: syntax error near unexpected token", 2);
	if (bad_token)
	{
		ft_putstr_fd(" `", 2);
		ft_putstr_fd(bad_token, 2);
		ft_putstr_fd("'\n", 2);
	}
	shell->exit_code = code;
=======
static void	print_token_error(char *bad_token)
{
	ft_putstr_fd(" `", 2);
	if (ft_strncmp(bad_token, ">>", 3) == 0 \
	|| ft_strncmp(bad_token, "<<", 3) == 0)
		ft_putstr_fd(bad_token, 2);
	else if (ft_strlen(bad_token) > 2)
		write(2, bad_token, 2);
	else
		write(2, bad_token, 1);
	ft_putstr_fd("'\n", 2);
}

static t_command	*handle_code_3(t_command *cmd_info, t_shell *shell)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("<<", 2);
	ft_putstr_fd(": command not found\n", 2);
	close_fd(cmd_info);
	shell->exit_code = 127;
>>>>>>> main
	free_command(cmd_info);
	return (NULL);
}

<<<<<<< HEAD
t_command	*handle_syntax_errors(t_command *cmd_info, t_shell *shell, \
			int ret, char *bad_token)
{
	if (ret == 0 || ret == 2)
		return (handle_token_error(cmd_info, shell, 2, bad_token));
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
	return (malloc(sizeof(char *) * (total * 2 + 1)));
=======
static t_command	*handle_code_4(t_command *cmd_info, t_shell *shell)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(">>", 2);
	ft_putstr_fd(": command not found\n", 2);
	close_fd(cmd_info);
	shell->exit_code = 127;
	free_command(cmd_info);
	return (NULL);
}

static t_command	*handle_empty_token(t_command *cmd_info, t_shell *shell)
{
	close_fd(cmd_info);
	shell->exit_code = 127;
	free_command(cmd_info);
	return (NULL);
}

t_command	*handle_token_error(t_command *cmd_info, t_shell *shell, \
			int code, char *bad_token)
{
	if (!bad_token)
	{
		ft_putstr_fd("minishell: syntax error near unexpected "
			"token `newline'\n", 2);
	}
	else if (code == 3)
		return (handle_code_3(cmd_info, shell));
	else if (code == 4)
		return (handle_code_4(cmd_info, shell));
	else if (ft_strncmp(bad_token, "", 2) == 0)
		return (handle_empty_token(cmd_info, shell));
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token", 2);
		print_token_error(bad_token);
	}
	close_fd(cmd_info);
	shell->exit_code = code;
	free_command(cmd_info);
	return (NULL);
>>>>>>> main
}
