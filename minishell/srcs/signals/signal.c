/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:49:10 by mertan            #+#    #+#             */
/*   Updated: 2024/04/10 11:53:13 by mertan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//ctl_C sends SIGINT;
//ctl_Slash sends SIGQUIT;
//ctl_D sends EOF (NULL);

void	handler_ctl_c(int sig)
{
	g_exit = sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	init_sighandler(t_mini *mini)
{
	struct sigaction	ctrl_c;
	struct sigaction	ctrl_slash;

	(void) mini;
	ctrl_c.sa_handler = &handler_ctl_c;
	sigemptyset(&ctrl_c.sa_mask);
	ctrl_c.sa_flags = SA_RESTART;
	sigaction(SIGINT, &ctrl_c, NULL);
	ctrl_slash.sa_handler = SIG_IGN;
	sigemptyset(&ctrl_slash.sa_mask);
	ctrl_slash.sa_flags = 0;
	sigaction(SIGQUIT, &ctrl_slash, NULL);
}

void	block_sighandler(void)
{
	struct sigaction	ctrl_c;
	struct sigaction	ctrl_slash;

	ctrl_c.sa_handler = SIG_IGN;
	sigemptyset(&ctrl_c.sa_mask);
	ctrl_c.sa_flags = 0;
	sigaction(SIGINT, &ctrl_c, NULL);
	ctrl_slash.sa_handler = SIG_IGN;
	sigemptyset(&ctrl_slash.sa_mask);
	ctrl_slash.sa_flags = 0;
	sigaction(SIGQUIT, &ctrl_slash, NULL);
}

void	default_sighandlers(void)
{
	struct sigaction	ctrl_c;
	struct sigaction	ctrl_slash;

	ctrl_c.sa_handler = SIG_DFL;
	sigemptyset(&ctrl_c.sa_mask);
	ctrl_c.sa_flags = 0;
	sigaction(SIGINT, &ctrl_c, NULL);
	ctrl_slash.sa_handler = SIG_DFL;
	sigemptyset(&ctrl_slash.sa_mask);
	ctrl_slash.sa_flags = 0;
	sigaction(SIGQUIT, &ctrl_slash, NULL);
}
/*
void	set_flag(int sig)
{
	(void)sig;
	flag = 1;
}

void	new_sighandler(void)
{
	struct sigaction act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = set_flag;
	sigaction(SIGINT, &act, NULL);
}*/