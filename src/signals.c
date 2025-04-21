/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 19:28:32 by nchairun          #+#    #+#             */
/*   Updated: 2025/04/21 01:40:42 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
    ECHOCTL is a flag used in terminal settings (termios) that controls whether control characters
    like Ctrl+C, Ctrl+\, etc. are visibly echoed as ^C, ^\\, etc. in the terminal.

    struct termios is a data structure from the <termios.h> library
    that stores settings for the terminal (TTY) — like input behavior, output formatting, signal control, and more.

    You use it with functions like:
        tcgetattr() → get current terminal settings
        tcsetattr() → apply modified settings

    Main Parts of struct termios
    struct termios {
        tcflag_t c_cflag;   // control modes
        tcflag_t c_lflag;   // local modes (like ECHO, ICANON, ISIG)
        ...
    };

    tcflag_t is the type used for terminal flag fields in termios
*/

void	disable_echoctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr");
		return ;
	}
	term.c_lflag &= ~(tcflag_t)ECHOCTL;             // Disable echoing of control characters (^C, ^\)
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		perror("tcsetattr");
	}
}

void	sigint_handler(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1); // Print a newline
    rl_replace_line("", 0);        // Clear the current input line
	rl_on_new_line();               // Inform readline that a new line has started
	rl_redisplay();                // Redisplay the prompt
}

void	sigquit_handler(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1); // Handle Ctrl+\ (default behavior)
}

void	sigchld_handler(int signal)
{
	(void)signal;
	waitpid(-1, NULL, WNOHANG);
		// Clean up terminated child processes (prevents zombies)
}

/*
    struct sigaction is a structure defined in <signal.h>
    to customize how program handles signals like SIGINT, SIGQUIT, SIGCHLD, etc.

    Common Fields You Use
    sa_handler:   A function you write that runs when a signal arrives. Example: sigint_handler()
    sa_flags  :   Flags like SA_RESTART (helps readline keep working after signals)

    SA_RESTART is a flag used with struct sigaction to control how system calls behave when a signal interrupts them.
    SIG_IGN is a special signal handler that tells the operating system to ignore a specific signal.
*/

void	init_signals(void)
{
	struct sigaction	sa;

	// Handle SIGINT (Ctrl+C)
	sa.sa_handler = sigint_handler;
	sa.sa_flags = SA_RESTART; // Restart interrupted system calls
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN; // Ignore SIGQUIT (Ctrl+\)
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_handler = sigchld_handler; // Handle SIGCHLD (child process termination)
	sigaction(SIGCHLD, &sa, NULL);
    disable_echoctl();
}
