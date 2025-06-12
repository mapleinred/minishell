/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_inpipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 05:56:16 by xzhang            #+#    #+#             */
/*   Updated: 2024/06/30 17:56:25 by xzhang            ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_command(char *path, char **cmd, t_instr *instr, \
t_exitnum *exitnum)
{
	if (path)
	{
		execve(path, cmd, instr->mini->e);
		free(path);
	}
	else
		execve(cmd[0], cmd, instr->mini->e);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_env(instr->mini->e);
	free(exitnum);
	free_tkn(instr->mini);
	free_instr(instr->mini);
	free(instr->mini->pipe);
	exit(EXIT_FAILURE);
}

int	handle_single_command(t_mini *mini, t_exitnum *exitnum)
{
	if (mini->instr_num == 1 && mini->instr->redir_num != 0)
	{
		if (handle_redirections(mini->instr, exitnum) == 1)
			return (1);
	}
	if (mini->instr->cmd == NULL && mini->instr->redir_num == 0)
		return (1);
	if ((check_buil(mini->instr->cmd) == 1) && mini->instr_num == 1)
	{
		if (exec_buil(mini, exitnum) == 1)
			return (1);
		return (2);
	}
	return (0);
}

void	create_pipes(int pipes[][2], int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipes[i]) == -1)
			fterror("Pipe error in exec_pipeline");
		i++;
	}
}

void	setup_signals_for_fork(t_mini *mini)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_l);
	if (mini->instr->cmd && ft_strcmp("./minishell", mini->instr->cmd) == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
