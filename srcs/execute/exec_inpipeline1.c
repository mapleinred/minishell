/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_inpipeline1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 05:56:27 by xzhang            #+#    #+#             */
/*   Updated: 2024/06/23 05:56:28 by xzhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	setup_pipes_for_child(int pipes[][2], int i, int num_pipes)
{
	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < num_pipes)
		dup2(pipes[i][1], STDOUT_FILENO);
	closepipes(pipes, num_pipes);
}

void	fork_child_process(t_mini *mini, int pipes[][2], int i, t_exitnum \
*exitnum)
{
	int	num_pipes;

	num_pipes = mini->instr_num - 1;
	handle_child_signals(i);
	setup_pipes_for_child(pipes, i, num_pipes);
	if (mini->instr_num > 1 && \
		handle_redirectionsinpipe(&mini->instr[i], exitnum) == 1)
		exit(EXIT_FAILURE);
	exec_inthepipe(&mini->instr[i], mini->e, exitnum);
	exit(EXIT_FAILURE);
}

void	closepipes(int pipes[][2], int num_pipes)
{
	int	j;

	j = 0;
	while (j < num_pipes)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

void	wait_for_children(t_mini *mini, int pids[], int instr_num)
{
	int	i;
	int	status;

	i = 0;
	while (i < instr_num)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			mini->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			mini->exit_status = WTERMSIG(status) + 128;
		i++;
	}
}

void	fork_processes(t_mini *mini, int pipes[][2], int pids[], \
t_exitnum *exitnum)
{
	int	i;

	i = 0;
	while (i < mini->instr_num)
	{
		setup_signals_for_fork(mini);
		pids[i] = fork();
		if (pids[i] == -1)
			ft_error(mini, "Fork error in exec_pipeline", 1);
		if (pids[i] == 0)
			fork_child_process(mini, pipes, i, exitnum);
		i++;
	}
}
