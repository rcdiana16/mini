/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:54:37 by diana             #+#    #+#             */
/*   Updated: 2025/05/05 15:28:05 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*read_command_line(int mode)
{
	if (mode == 0)
		return (readline("\033[1;32mCBS$ \033[0m"));
	else
		return (get_next_line(0));
}

void	handle_eof_or_empty(char *line, t_shell *shell, t_env *env_mini, \
		int mode)
{
	if (!line)
	{
		if (mode == 0)
			write(1, "exit\n", 5);
		free_env_list(env_mini);
		free(line);
		exit(shell->exit_code);
	}
	if (*line == '\0')
		free(line);
	if (ft_strncmp(line, "\"\"", 2) == 0)
	{
		free(line);
		shell->exit_code = 127;
	}
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
	add_history(line);
	return (parse_and_store_command(line, env_mini, shell));
}
