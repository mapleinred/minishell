/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocinp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 05:41:31 by xzhang            #+#    #+#             */
/*   Updated: 2024/06/23 05:41:33 by xzhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_l(int sig)
{
	(void) sig;
	write(1, "Quit (core dumped)\n", 19);
}

void	child_process_setup(int fd[2], char *delimiter, \
t_instr *instr, t_exitnum *exitnum)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint2;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	limiter(delimiter, fd, instr->mini, exitnum);
	if (g_exit == 1)
		exit(130);
	exit(EXIT_SUCCESS);
}

int	parent_process_setup(int fd[2], int pid, t_instr *instr)
{
	int	wstatus;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &wstatus, 0);
	close(fd[1]);
	if (WIFEXITED(wstatus))
	{
		instr->mini->exit_status = WEXITSTATUS(wstatus);
	}
	else if (WIFSIGNALED(wstatus))
	{
		instr->mini->exit_status = 128 + WTERMSIG(wstatus);
	}
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (1);
	}
	close(fd[0]);
	return (0);
}

int	create_pipe_and_fork(int fd[2])
{
	int	pid;

	if (pipe(fd) == -1)
		fterror("Pipe error in heredoc");
	pid = fork();
	if (pid == -1)
		fterror("Fork error in heredoc");
	return (pid);
}

int	heredoc(char *delimiter, t_instr *instr, t_exitnum *exitnum)
{
	int	fd[2];
	int	pid;

	pid = create_pipe_and_fork(fd);
	if (pid == 0)
	{
		child_process_setup(fd, delimiter, instr, exitnum);
	}
	else
	{
		if (parent_process_setup(fd, pid, instr) == 1)
			return (1);
	}
	return (0);
}
