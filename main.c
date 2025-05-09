/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:52:16 by diana             #+#    #+#             */
/*   Updated: 2025/05/07 17:42:29 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	init_shell(char **env, t_env **env_list, char ***path_splitted, \
		char ***path_sp_w_slash)
{
	*path_splitted = NULL;
	*path_sp_w_slash = NULL;
	*env_list = initialize_environment(env, *env_list);
	disable_echoctl();
	using_history();
	return (0);
}

int	handle_user_input(t_command **cmd_info, t_env *env_list, \
		t_shell *shell, char **path)
{
	set_signals();
	if (isatty(STDIN_FILENO))
	{
		*cmd_info = get_input(env_list, 0, shell, path);
		if (!*cmd_info)
			return (0);
	}
	else
	{
		*cmd_info = get_input(env_list, 1, shell, path);
		if (!*cmd_info)
			return (0);
	}
	return (1);
}

void	initialize_shell(t_env **env_list, char **env, t_shell_data *data)
{
	data->shell.exit_code = 0;
	if (init_shell(env, env_list, &data->path_splitted, \
			&data->path_sp_w_slash) == 1)
		exit(EXIT_FAILURE);
}

void	execute_shell_loop(t_env *env_list, char **env)
{
	t_shell_data	data;
	t_command		*cmd_info;
	int				input_status;

	initialize_shell(&env_list, env, &data);
	while (1)
	{
		cmd_info = NULL;
		handle_path(&data.path_splitted, &data.path_sp_w_slash, env_list);
		set_signals();
		input_status = handle_user_input(&cmd_info, env_list, \
										&data.shell, data.path_sp_w_slash);
		if (input_status != 0)
			data.shell.exit_code = execute_command(cmd_info, \
										data.path_sp_w_slash, env_list);
		handle_cmd_info(cmd_info);
	}
}

int	main(int ac, char **av, char **env)
{
	t_env	*env_list;

	if (ac == 0)
		return (1);
	*av = NULL;
	env_list = NULL;
	execute_shell_loop(env_list, env);
	return (0);
}
