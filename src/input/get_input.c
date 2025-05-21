/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:54:37 by diana             #+#    #+#             */
/*   Updated: 2025/05/07 17:56:48 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_eof_or_empty(char *line, t_shell *shell, t_env *env_mini, \
		int mode)
{
	if (!line)
	{
		if (mode == 0)
		{
			write(1, "exit\n", 5);
			shell->exit_code = 0;
		}
		free_env_list(env_mini);
		free(line);
		exit(shell->exit_code);
	}
	if (*line == '\0')
		free(line);
	else if (ft_strncmp(line, "\"\"", 2) == 0)
	{
		free(line);
		shell->exit_code = 127;
	}
}

int	is_only_whitespace(const char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n' && \
				*str != '\v' && *str != '\f' && *str != '\r')
			return (0);
		str++;
	}
	return (1);
}

void	manage_history(char *line)
{
	HIST_ENTRY	*last_entry;

	if (!line || *line == '\0' || is_only_whitespace(line))
		return ;
	if (history_length > 0)
	{
		last_entry = history_get(history_length - 1);
		if (last_entry && ft_strncmp(last_entry->line, line, \
		ft_strlen(line) + 1) == 0)
			return ;
	}
	add_history(line);
}

t_command	*parse_and_store_command(char *line, t_env *env_mini, \
			t_shell *shell)
{
	t_command	*cmd_info;

	cmd_info = verify_and_split_command(line, env_mini, shell);
	if (!cmd_info)
	{
		free(line);
		return (NULL);
	}
	free(line);
	return (cmd_info);
}

t_command	*get_input(t_env *env_mini, int mode, t_shell *shell, \
			char **path)
{
	char	*line;

	line = read_command_line(mode);
	if (!line || *line == '\0' || ft_strncmp(line, "\"\"", 2) == 0)
	{
		if (!line && path)
			free_arr(path);
		handle_eof_or_empty(line, shell, env_mini, mode);
		return (NULL);
	}
	manage_history(line);
	return (parse_and_store_command(line, env_mini, shell));
}
