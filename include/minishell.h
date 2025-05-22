/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:46:38 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/22 10:06:59 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <limits.h>
# include <termios.h>
# include <unistd.h>
# include <sys/stat.h>
# include "../libft/libft.h"

typedef struct s_split_data
{
	char		**res;
	int			*j;
	int			*s_word;
	const char	*delimiters;
	const char	*s;
}	t_split_data;

typedef struct s_command
{
	char	**tokens;
	char	**envp;
	char	*file_out;
	char	*file_in;
	int		fd_out;
	int		fd_in;
	int		c_pipe;
	int		c_red_i;
	int		c_red_o;
	int		here_doc;
	int		fd_here_doc;
	int		c_append;
	int		flag;
	int		quotes_s;
	int		quotes_d;
	int		exit_code;
	int		flag_test;
	int		og_stdout;
	int		og_stdin;
}	t_command;

typedef struct s_env
{
	char			*variable;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd_state
{
	char		*cmd;
	int			i;
	t_command	*cmd_info;
}	t_cmd_state;

typedef struct s_shell
{
	int	exit_code;
}	t_shell;

typedef struct s_shell_env
{
	t_env	*env_mini;
	t_shell	*shell;
}	t_shell_env;

typedef struct s_shell_data
{
	char	**path_splitted;
	char	**path_sp_w_slash;
	t_shell	shell;
	int		original_stdout;
	int		original_stdin;
}	t_shell_data;
typedef struct s_pipe_exec_info
{
	int			prev_pipe_fd;
	int			pipe_fd[2];
	int			fd_redir_out;
	int			i;
	char		**current_command;
	char		**path_sp_w_slash;
	t_env		*env_list;
	t_command	*cmd_info;
	t_shell		*shell;
}	t_pipe_exec_info;

typedef struct s_split_res
{
	char	***result;
	int		*res_i;
}	t_split_res;

typedef struct s_split_ctx
{
	char	**result;
	int		index;
}	t_split_ctx;

extern volatile sig_atomic_t	g_heredoc_interrupted;

//----------------------------builtins---------------------------------
//----cd_utils.c----
void		update_env(t_env *env, char *new_path, \
			char *env_to_update, int flag);
void		update_pwd_env(t_env *env_mini, char *oldpwd, char *path);
int			print_cd_error(char *path);

//----cd.c----
int			is_valid_path(char *path, t_env *env_mini, \
	t_command *cmd_info, char **cmd);

//----echo.c----
void		ft_our_echo(char **cmd);

//----env.c----
int			ft_our_env(t_env *env_mini, char **cmd);

//----exit.c----
int			ft_our_exit(t_env *env_mini, char **cmd, t_command *cmd_info, \
	char **path);

//----exit_utils.c----
void		handle_exit_argument_error(t_command *cmd_info);
int			validate_exit_argument(char *arg);

//----export.c----
int			ft_export(t_env *env_mini, char **cmd);
void		join_quoted_values(char **cmd, char **value);
void		assign_value(char **cmd, char **value);
int			is_invalid_identifier(char *tokens);
void		add_new_variable(t_env *env_mini, char **tokens, t_env *new_var);
//----export_utils.c----
void		init_new_variable(t_env *new_var, char **tokens);
int			is_valid_variable_name(char *name);

//----export_utils_update.c----
int			handle_existing_variable(t_env *env_mini, char **cmd);
int			update_existing_variable(t_env *env_mini, char **cmd);
int			handle_export_arg(t_env *env_mini, char *arg);
int			alloc_and_init_new_var(t_env *env_mini, char **tokens);
//----export_utils_bis.c----
char		**get_tokens(char *cmd);

//----export_utils_bis.c----
void		join_cmd_values(char **cmd, char **value);
void		print_and_free_list(char **list);
//----print_sorted_env.c----
int			print_sorted_env(t_env *env);

//----pwd.c----
void		ft_our_pwd(t_env *env_mini);

//----unset.c----
void		ft_unset(t_env *env_mini, char **cmd);

//----------------------------check_cmd----------------------------
//----check_builtins.c----
int			check_standard_builtins(char **command, t_env *env_mini, \
	t_command **cmd_info, char **path);
int			check_env_builtins(char **command, t_env *env_mini);

//----check_builtins_utils.c----
int			check_builtins(char **cmd, t_env *env_mini, t_command *cmd_info, \
	char **path);

//----------------------------execute----------------------------
//----execute.c----
int			execute_command(t_command *cmd_info, char **path_sp_w_slash, \
	t_env *env_list);
int			execute_child_process(t_command *cmd_info, char **path_sp_w_slash, \
	t_env *env_list);

//----execute_error.c----
void		handle_empty_command(t_command *cmd_info, char **path_sp_w_slash, \
	t_env *env_list);
void		handle_dotdot_command(t_command *cmd_info, char **path_sp_w_slash, \
	t_env *env_list);
void		handle_is_directory(char *command, t_command *cmd_info, \
	t_env *env_list, char **path_sp_w_slash);
void		handle_command_found(t_command *cmd_info, \
	t_env *env_list, char **path_sp_w_slash);

//----execute_error_utils.c----
void		handle_command_not_found(char *command, t_command *cmd_info, \
	t_env *env_list, char **path_sp_w_slash);

//----execute_utils.c----
char		*find_no_builtin(char **good_path, char **command);
int			wait_for_child_processes(int *pids, int pipe_count);
int			execute_builtin(t_command *cmd_info, t_env *env_list, \
	char **path_sp_w_slash);

//----execute_utils_exit.c----
void		exec_builtin_or_exit(char *command, t_command *cmd_info, \
	t_env *env_list, char **path_sp_w_slash);
char		*find_builtin_or_exit(char **path_sp_w_slash, t_command *cmd_inf, \
	t_env *env_list);

//----utils_execute.c----
int			wait_for_child_processes(int *pids, int pipe_count);

//----execute_utils_env.c----
char		**convert_env_to_array(t_env *env_mini);

//----here_doc_utils.c----
int			process_heredoc_line(char *line, char *delimiter, int *pipefd);
int			init_heredoc_io(void);

//----here_doc_signals.c----
void		sigint_handler_heredoc(int sig);
int			check_heredoc_interrupt(char *line, int *pipefd, \
	struct sigaction *sa_old);
void		init_here_doc_signals(struct sigaction *sa_new, \
	struct sigaction *sa_old);

//----here_doc_main.c----
int			handle_heredoc_input(char *delimiter, \
	t_pipe_exec_info *pipe_exec_info);

//----here_doc_execute.c----
int			execute_heredoc(char *delimiter, t_pipe_exec_info *pipe_exec_info);
void		restore_heredoc_stdin(t_command *cmd_info);
void		handle_heredoc_redirection(char **cmd_tokens, int *i, \
	t_pipe_exec_info *pipe_exec_info);

//----redir.c----
int			handle_redirection(char **cmd_tokens, t_command *cmd_info, int *i, \
	t_pipe_exec_info *pipe_exec_info);

//----execute_pipe.c----
char		**clean_redir(char **cmd_tokens, t_command *cmd_info, \
	t_pipe_exec_info *pipe_exec_info);
int			execute_child_process_pipe(char **cmd_info, char **path_sp_w_slash, \
	t_env *env_list, t_command *stru);

//----execute_pipe_utils.c----
int			execute_pipes(t_command *cmd_info, \
	char **path_sp_w_slash, t_env *env_list);

//----execute_pipe_utils_bis.c----
char		*find_builtin_or_exit_pipe(char **path_sp_w_slash, char **cmd_inf, \
	t_env *env_list, t_command *stru);
char		**allocate_cleaned_cmd(char **cmd_tokens);

//----execute_pipe_utils_handle.c----
int			handle_redirection_and_builtins(t_pipe_exec_info *pipe_exec_info);

//----execute_child_auxiliar.c----
int			child_process_execute_command(t_pipe_exec_info *pipe_exec_info);

//----utils_pipe.c----
int			get_pipe_bounds(t_command *cmd_info, int i, int *start, int *end);
char		**get_pipe_command(t_command *cmd_info, int i);
int			create_pipe(int *pipe_fd);
void		child_process_setup_io(t_pipe_exec_info *pipe_exec_info);
int			execute_child_process_pipe_helper(t_pipe_exec_info *pipe_exec_info);

//----utils.c----
void		exec_builtin_or_exit_pipe(char **command, t_command *cmd_info, \
	t_env *env_list, char **path_sp_w_slash);

//----check_redir.c----
int			open_file(char *file, int mode, t_command *cmd_info);
int			manage_redirection(t_command *cmd_info);
void		execute_in_child(t_command *cmd_info, char **path_sp_w_slash, \
	t_env *env_list);
void		close_fd(t_command *cmd_info);

//----------------------------free----------------------------
//----free.c----
void		free_command(t_command *cmd_info);
void		free_node(t_env *node);
void		free_env_list(t_env *env);
void		free_split_data(t_split_data *data);
void		free_cmd_state(t_cmd_state *state);

//----free_bis.c----
void		free_all(t_command *cmd_info, char **path_sp_w_slash, \
	t_env *env_list);
void		free_arr(char **tok);

//----------------------------ft_list----------------------------
//----list.c----
t_env		*initialize_environment(char **env, t_env *env_list);

//----list_node.c----
void		append_node(t_env **head, char *var, char *val);
t_env		*create_node(char *var, char *val);
void		update_or_append_node(t_env **env_list, const char *key, \
			char *value);

//----------------------------input----------------------------
//----get_input.c----
void		handle_eof_or_empty(char *line, t_shell *shell, t_env *env_mini, \
			int mode);
int			is_only_whitespace(const char *str);
void		manage_history(char *line);
t_command	*get_input(t_env *env_mini, int mode, t_shell *shell, \
			char **path);
t_command	*verify_and_split_command(char *cmd, t_env *env_mini, \
			t_shell *shell);

//----get_input_read.c----
char		*read_command_line(int mode);

//----get_input_utils.c----
char		**tokenize_quotes(char *input);

//----get_strjoin.c----
char		**ft_strjoin_arr(char *first, char **arr);

//----handle_input.c----
char		*make_good_cmd2(char *cmd);
char		*make_good_cmd(char *cmd);
void		remove_newline(char *str);
int			copy_non_var_part(t_cmd_state *state, char *result, int j);
bool		has_enclosed_double_quotes(char *token);

//----verify_and_split_cmd.c----
void		split_double_redirection(char **tokens, \
	char **new_tokens, int *i, int *j);
void		split_single_redirection(char **tokens, \
	char **new_tokens, int *i, int *j);
t_command	*verify_and_split_command(char *cmd, t_env *env_mini, \
	t_shell *shell);

//----verify_and_split_cmd_utils.c----
t_command	*handle_token_error(t_command *cmd_info, t_shell *shell, \
	int code, char *bad_token);

//----verify_and_split_cmd_utils_bis.c----
t_command	*handle_syntax_errors(t_command *cmd_info, \
	t_shell *shell, int ret, char *bad_token);
int			is_invalid_single_token(char *token);
void		process_command_tokens(t_command *cmd_info);
char		**allocate_new_tokens(char **tokens);

//----verify_and_split_cmd_split.c----
char		**split_joined_redirections(char **tokens);
char		**split_tokens_with_operators(char **tokens);
void		copy_normal_token(char **tokens, char **new_tokens, int *i, int *j);
int			should_split_at(char *token, int i);
int			is_operator_char(char c);
//-----new----
void		split_token_at_operator(char *token, char ***result, int *res_i);
//---new2----

//---check_syntax.c----
int			check_syntax(char **cmd, char **bad_tokens);
int			check_middle_syntax(char **cmd, char **bad_token);
int			check_final_syntax(char **cmd, int i, char **bad_token);

//---check_syntax_utils.c----
int			check_initial_syntax(char **cmd, char **bad_token);
int			is_redirection(char *token);

//----count_sp_ch.c----
void		count_special_chars(char *cmd, t_command *cmd_info);

//----rep_env_var.c----
char		*replace_env_vars(char *cmd, t_env *env_mini, t_shell *shell);
int			process_env_var(t_cmd_state *state, char *result, \
	int j, t_env *env_mini);

//----rep_env_var_utils.c----
int			process_var(t_cmd_state *state, char *result, \
	int j, t_shell_env *shell_env);
char		*process_replace_env_vars(t_cmd_state *state, \
	char *result, t_shell_env *shell_env);
char		*initialize_replace_env_vars(t_cmd_state *state);

//----utils_input.c----
void		count_special_chars(char *cmd, t_command *cmd_info);
void		handle_double_quotes_and_env_vars(t_command *cmd_info, \
	t_env *env_mini, t_shell *shell, int i);

//----utils_input_2.c----
void		process_tokens(t_command *cmd_info, t_env *env_mini, \
	t_shell *shell);
void		handle_single_quotes(t_command *cmd_info, int i);
t_command	*initialize_command(t_shell *shell);

//----utils_replace_tok.c----
void		replace_token_with_empty(t_command *cmd_info, int i);
void		replace_token_with_tmp(t_command *cmd_info, int i, char *tmp);
void		remove_token(t_command *cmd_info, int i, char *tmp);

//----quote.c----
bool		has_enclosed_single_quotes(char *token);
void		delete_quotes(char *token);
void		clean_quotes(char *token);
void		remove_single_quotes(char *token);

//----redirection.c----
void		count_redirections(char *cmd, t_command *cmdf_info);

//----------------------------path----------------------------
//----path.c----
void		handle_path(char ***path_splitted, char ***path_sp_w_slash, \
	t_env *env_mini);

//---path_utils.c----
char		**add_slash(char **path_splited);
int			count_paths(char **path_splited);

//----------------------------signals----------------------------
//----ctrl_c.c----
void		disable_echoctl(void);
void		set_signals(void);
void		sigint(void);
void		handle_sigint(int sig);

//----ctrl_nothing.c----
void		sigquit(void);
void		handle_sigquit(int sig);

//----------------------------utils----------------------------
//----utils.c----
char		*get_env_value(t_env *env_mini, const char *var);
int			process_exit_code(char *result, int j, t_shell *shell);
long long	ft_atoll(const char *str);
int			ft_arrlen(char **arr);

//----main_utils.c----
void		handle_cmd_info(t_command *cmd_info);
void		reset_stdin(t_command *cmd_info);
void		reset_stdout(t_command *cmd_info);
void		handle_is_directory_empty(char *command, t_command *cmd_info, \
	t_env *env_list, char **path_sp_w_slash);

#endif