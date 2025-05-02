/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:26:37 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/05/02 02:55:27 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_env
{
	char					*key;
	char					*value;
	struct s_env			*next;
}							t_env;
typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}							t_token_type;

typedef enum e_quote_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}							t_quote_type;
typedef struct s_token
{
	t_token_type			type;
	t_quote_type			quote_type;
	char					*value;
	struct s_token			*next;
	bool					start_is_whitespace;
}							t_token;

typedef struct s_redirection
{
	t_token_type			redirection_type;
	char					*name_of_file_to_redirect;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_redirection_list
{
	t_redirection			*head;
	t_redirection			*tail;
	int						size_of_list;
}							t_redirection_list;

typedef struct s_pipe
{
	t_redirection_list		*list_of_redirections;
	char					**cmd;
	struct s_pipe			*next;
}							t_pipe;

typedef struct s_pipe_list
{
	t_pipe					*head;
	t_pipe					*tail;
	int						size_of_list;
}							t_pipe_list;

typedef struct s_minishell
{
	t_pipe_list				*pipe_list;
	t_token					*tokens;
	char					**paths;
	t_env					*env;
	int						exit_code;
}							t_minishell;

//----------SRCS----------//

// init_mini
t_env						*env_from_envp(char **envp);
t_env						*new_env_node(char *key, char *value);
t_minishell					*init_mini(char **envp);
void						free_parts(char **parts);

// tests.c
bool						quotes_error(char *user_input);
bool						syntax_error_check(t_token *token_head);

// signals.c
void						disable_echoctl(void);
void						sigint_handler(int signal);
void						sigquit_handler(int signal);
void						sigchld_handler(int signal);
void						init_signals(void);

//----------LEXER----------//

// lexer.c
void						skip_spaces(char *user_input, int *i);
void						add_token_to_back(t_token **head_token,
								t_token *new_token);
t_token						*create_tokens(char *user_input);
void						join_tokens(t_token *head_token);

// read_tokens.c
bool						delimiter_check(char c);
t_token						*new_token(t_token_type type, t_quote_type qtype,
								char *value);
t_token						*read_quoted_token(char *user_input, int *i);
t_token						*read_redirection_token(char *user_input, int *i);
t_token						*read_word(char *user_input, int *i);

// expander.c
void						expand_tokens(t_token *head_token_list, t_env *env,
								int exit_code);
void						ft_expand(t_token *token, t_env *env,
								int exit_code);
int							handle_expansion(char **expanded, char *start,
								t_env *env, int exit_code);
char						*append_char(char *str, char c);

// expander_utils.c
int							get_var_len(char *str);
char						*ft_strjoin_gc(char *s1, char *s2);
char						*get_env_value(t_env *env, const char *key,
								int var_len);
int							handle_special_expansion(char **expanded,
								char *start, int exit_code);
int							handle_non_alpha_expansion(char **expanded,
								char *start);

//----------PARSING----------//

// parsing.c
bool						parsing(t_minishell *mini, char *user_input);
void						parse_tokens_to_pipe_list(t_minishell *mini);
void						handle_redirection_token(t_pipe *pipe,
								t_token **curr);
void						add_word_to_cmd(t_pipe *pipe, char *word);
void						add_redirection(t_pipe *pipe, t_token_type type,
								char *filename);

// parsing_utils.c
void						merge_tokens(t_token *curr);
t_pipe						*create_pipe(void);
void						add_pipe_to_list(t_pipe_list *list, t_pipe *pipe);
void						add_first_word(t_pipe *pipe, char *word);
void						copy_cmd_array(char **new_cmd, char **cmd,
								int count);

//----------EXECUTION----------//

// execution.c
void						handle_heredoc(t_redirection *redir);
void						handle_redirections(t_redirection *redir_list);
void						child_exec(t_pipe *cmd, int prev_fd, int *pipe_fd,
								t_minishell *mini);
void						close_pipe_fds(int *prev_fd, int *pipe_fd);
void						execution(t_minishell *mini);

// execution_utils_1.c
char						*get_full_path(char *cmd, t_env *env);
char						**env_to_array(t_env *env);
char						**get_paths(t_env *env);
char						*ft_strjoin_path(char *path, char *cmd);
void						free_paths(char **paths);

// execution_utils_2.c
void						process_fd_redirection(t_redirection *redir,
								int fd);
int							open_redirection_file(t_redirection *redir);
bool						is_builtin(char *cmd);
int							execute_builtin(char **cmd, t_minishell *mini);
void						execute_command(t_pipe *cmd, t_minishell *mini);

// execution_utils_3.c
void						setup_io_for_child(t_pipe *cmd, int prev_fd,
								int *pipe_fd);
void						execute_pipeline(t_minishell *mini, t_pipe *cmd,
								int prev_fd);
void						process_builtin(t_pipe *cmd, t_minishell *mini);
void						wait_for_children(t_minishell *mini);
void						prepare_pipes(t_pipe *cmd, int *pipe_fd,
								int **pipe_ptr);

// execution_utils_4.c
void						setup_redirection_with_backup(t_pipe *cmd,
								int *stdin_backup, int *stdout_backup);
void						restore_std_fds(int stdin_backup,
								int stdout_backup);

//----------BUILT_INS----------//

// cd.c
void						update_env_value(t_env *env, const char *key,
								const char *value);
void						add_env_node(t_env **env, const char *key,
								const char *value);
void						set_env_value(t_env **env, const char *key,
								const char *value);
int							ft_cd(char **args, t_minishell *mini);

// echo.c
int							ft_echo(char **args, t_minishell *mini);

// env.c
int							ft_env(char **args, t_minishell *mini);

// exit.c
int							is_numeric(const char *str);
int							ft_exit(char **args, t_minishell *mini);

// export.c
void						sort_string_array(char **array);
void						print_export(t_env *env);
int							ft_export(char **args, t_minishell *mini);
int							bubble_pass(char **array, int pass, int len);
void						handle_export_arg(t_minishell *mini, char *arg);

// pwd.c
int							ft_pwd(char **args, t_minishell *mini);

// unset.c
int							ft_unset(char **args, t_minishell *mini);

#endif
