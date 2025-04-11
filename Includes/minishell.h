/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:26:37 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/11 04:10:33 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_env
{
	char					*key;
	char					*value;
	struct s_env			*next;
}							t_env;
typedef enum e_token_type // enum for token identification during tokenizing
{
	WORD,          // 0
	PIPE,          // 1
	REDIR_IN,      // < 2
	REDIR_OUT,     // > 3
	REDIR_APPEND,  // >> 4
	REDIR_HEREDOC, // << 5
}							t_token_type;

typedef enum e_quote_type
{
	NO_QUOTE,     // 0
	SINGLE_QUOTE, // 1
	DOUBLE_QUOTE  // 2
}							t_quote_type;
typedef struct s_token // struct to save tokens during tokenization
{
	t_token_type type;
	t_quote_type quote_type;
	char *value;
	struct s_token *next;
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

// Function Prototypes BEGIN
void						dummy_file_function(void);
void						debug_putstr(char *msg, char *file,
								const char *function, int line);
void						print_token_type(t_token_type type);
void						print_quote_type(t_quote_type qtype);
void						debug_tokens(t_token *tokens);

// init_mini
t_env						*new_env_node(char *key, char *value);
t_env						*env_from_envp(char **envp);
t_minishell					*init_mini(char **envp);

// tests.c
bool						quotes_error(char *user_input);

//----------LEXER----------//

// lexer.c
void						skip_spaces(char *user_input, int *i);
void						add_token_to_back(t_token **head_token,
								t_token *new_token);
t_token						*create_tokens(char *user_input);

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
char						*ft_strjoin_free(char *s1, char *s2);
char						*get_env_value(t_env *env, const char *key);

//----------PARSING----------//

// parsing.c
bool						parsing(t_minishell *mini, char *user_input);

#endif
