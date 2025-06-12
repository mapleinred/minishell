/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:49:10 by mertan            #+#    #+#             */
/*   Updated: 2024/06/30 18:56:20 by xzhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_buil(t_mini *mini, t_exitnum *exitnum)
{
	int	i;
	int	exit_status;

	i = -1;
	exit_status = 0;
	while (++i < mini->instr_num)
	{
		if (mini->instr[i].cmd == NULL || mini->instr[i].cmd == NULL)
			break ;
		if (ft_strcmp(mini->instr[i].cmd, "echo") == 0)
			exit_status = ft_echo(&mini->instr[i]);
		if (ft_strcmp(mini->instr[i].cmd, "exit") == 0)
			exit_status = ft_exit(&mini->instr[i], exitnum);
		if (ft_strcmp(mini->instr[i].cmd, "cd") == 0)
			exit_status = ft_cd(&mini->instr[i]);
		if (ft_strcmp(mini->instr[i].cmd, "pwd") == 0)
			exit_status = ft_pwd(&mini->instr[i]);
		if (ft_strcmp(mini->instr[i].cmd, "env") == 0)
			exit_status = ft_env(&mini->instr[i]);
		if (ft_strcmp(mini->instr[i].cmd, "unset") == 0)
			exit_status = ft_unset(&mini->instr[i]);
		if (ft_strcmp(mini->instr[i].cmd, "export") == 0)
			exit_status = ft_export(&mini->instr[i]);
	}
	return (exit_status);
}

int	exec_buil1(t_instr *instr, t_exitnum *exitnum)
{
	int	exit_status;

	if (instr->cmd == NULL || instr->cmd == NULL)
		return (0);
	if (ft_strcmp(instr->cmd, "echo") == 0)
		exit_status = ft_echo(instr);
	if (ft_strcmp(instr->cmd, "exit") == 0)
		exit_status = ft_exit(instr, exitnum);
	if (ft_strcmp(instr->cmd, "cd") == 0)
		exit_status = ft_cd(instr);
	if (ft_strcmp(instr->cmd, "pwd") == 0)
		exit_status = ft_pwd(instr);
	if (ft_strcmp(instr->cmd, "env") == 0)
		exit_status = ft_env(instr);
	if (ft_strcmp(instr->cmd, "unset") == 0)
		exit_status = ft_unset(instr);
	if (ft_strcmp(instr->cmd, "export") == 0)
		exit_status = ft_export(instr);
	return (exit_status);
}

int	exec_instr(t_mini *mini, t_exitnum *exitnum)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < mini->instr_num && i < mini->tks_num)
	{
		mini->instr[j].cmd_arr = malloc(sizeof(char *) * 64);
		ft_memset(mini->instr[j].cmd_arr, 0, sizeof(char *) * 64);
		i = init_instr_cmdarr(mini, i, &mini->instr[j]);
		if (mini->tkn[i].type == 3)
			i++;
		j++;
	}
	exec_pipeline(mini, mini->instr_num, exitnum);
	return (0);
}

int	exec_pipeline(t_mini *mini, int instr_num, t_exitnum *exitnum)
{
	int	num_pipes;
	int	pids[64];
	int	pipes[63][2];
	int	i;

	num_pipes = instr_num - 1;
	i = handle_single_command(mini, exitnum);
	if (i != 1 || mini->exit_status != 0)
	{
		if (mini->exit_status != 0)
			return (mini->exit_status);
		else if (i == 1)
			return (mini->exit_status = i);
		else if (i != 0)
			return (0);
	}
	create_pipes(pipes, num_pipes);
	if (mini->instr_num > 1)
		if (open_all_heredocs(mini, exitnum) == 1)
			return (1);
	fork_processes(mini, pipes, pids, exitnum);
	closepipes(pipes, num_pipes);
	wait_for_children(mini, pids, instr_num);
	return (0);
}
