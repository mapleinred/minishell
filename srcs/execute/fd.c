/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 05:23:34 by xzhang            #+#    #+#             */
/*   Updated: 2024/06/23 05:23:37 by xzhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	initfd(t_mini *mini)
{
	mini->pipe = (t_pipe *)malloc(sizeof(t_pipe));
	if (mini->pipe == NULL)
	{
		perror("Failed to allocate memory for mini->pipe");
	}
	mini->pipe->orgstdin = dup(STDIN_FILENO);
	mini->pipe->orgstdout = dup(STDOUT_FILENO);
	mini->pipe->orgstderr = dup(STDERR_FILENO);
	if (mini->pipe->orgstdin == -1 || mini->pipe->orgstdout == -1
		|| mini->pipe->orgstderr == -1)
	{
		fterror("Failed to save original file descriptors");
		free(mini->pipe);
	}
	return ;
}

void	restorefd(t_mini *mini)
{
	dup2(mini->pipe->orgstdin, STDIN_FILENO);
	dup2(mini->pipe->orgstdout, STDOUT_FILENO);
	dup2(mini->pipe->orgstderr, STDERR_FILENO);
	close(mini->pipe->orgstdin);
	close(mini->pipe->orgstdout);
	close(mini->pipe->orgstderr);
}

void	handle_sigint1(int sig)
{
	(void) sig;
	write(1, "\n", 1);
	g_exit = 1;
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit = 1;
		write(STDIN_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_up_signals(void)
{
	struct sigaction	act1;
	struct sigaction	act2;

	act1.sa_handler = signal_handler;
	act2.sa_handler = SIG_IGN;
	act1.sa_flags = 0;
	act2.sa_flags = 0;
	sigemptyset(&act1.sa_mask);
	sigemptyset(&act2.sa_mask);
	sigaction(SIGINT, &act1, NULL);
	sigaction(SIGQUIT, &act2, NULL);
}
