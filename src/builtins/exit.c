/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:09:42 by cosmos            #+#    #+#             */
/*   Updated: 2025/05/07 07:26:00 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	exit_cleanup(t_env *env_mini, t_command *cmd_info, char **path)
{
	free_env_list(env_mini);
	free_command(cmd_info);
	free_arr(path);
	close(0);
	close(1);
	close(2);
}

static void	exit_with_error(t_env *env_mini, t_command *cmd_info, \
											char **path, char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	close_fd(cmd_info);
	exit_cleanup(env_mini, cmd_info, path);
	exit(2);
}

static int	handle_exit_args(char **cmd, t_command *cmd_info, \
		t_env *env_mini, char **path)
{
	long long	ex;
	int			count;

	count = 0;
	ex = 0;
	while (cmd[count])
		count++;
	if (cmd[1])
	{
		if (!validate_exit_argument(cmd[1]))
			exit_with_error(env_mini, cmd_info, path, cmd[1]);
		else if (count > 2)
		{
			handle_exit_argument_error(cmd_info);
			return (-1);
		}
		ex = ft_atoll(cmd[1]);
	}
	else
		ex = cmd_info->exit_code;
	return ((unsigned char)ex);
}

static void	cleanup_and_exit(t_env *env_mini, t_command *cmd_info, \
		char **path, int ex)
{
	close_fd(cmd_info);
	exit_cleanup(env_mini, cmd_info, path);
	exit(ex);
}

int	ft_our_exit(t_env *env_mini, char **cmd, t_command *cmd_info, char **path)
{
	int	ex;

	ft_putstr_fd("exit\n", 2);
	get_next_line(-42);
	ex = handle_exit_args(cmd, cmd_info, env_mini, path);
	if (ex == -1)
		return (1);
	cleanup_and_exit(env_mini, cmd_info, path, ex);
	return (cmd_info->exit_code);
}
