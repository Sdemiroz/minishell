/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:26:37 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/09 03:27:56 by sdemiroz         ###   ########.fr       */
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
typedef enum e_redirection_type
// enum for redirection identification during parsing
{
	REDIR_INPUT,  // 1 <
	REDIR_OUTPUT, // 2 >
	REDIR_APP, // 3 >>
	REDIR_HERE // 4 <<
}							t_redirection_type;

typedef struct s_token // struct to save tokens during tokenization
{
	t_token_type type;
	t_quote_type quote_type;
	char *value;
	struct s_token *next;
}							t_token;

typedef struct s_redirection
{
	t_redirection_type		redirection_type;
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
	char					**env;
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
int							count_env_entries(char **envp);
char						**dup_envp(char **envp, int env_size);
t_minishell					*init_mini(char **envp);
bool						parsing(t_minishell *mini, char *user_input);

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

#endif
