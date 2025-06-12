/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_inpipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 05:31:25 by xzhang            #+#    #+#             */
/*   Updated: 2024/06/30 17:59:17 by achak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_builtin(t_instr *instr, char **envp, t_exitnum *exitnum)
{
	(void) envp;
	if (check_buil(instr->cmd) == 1)
	{
		exec_buil1(instr, exitnum);
		free_env(instr->mini->e);
		free(exitnum);
		free_mini(instr->mini);
		exit(instr->mini->exit_status);
	}
}
/*
void	handle_dot_slash_command(t_instr *instr, t_exitnum *exitnum)
{
	if (ft_strcmp("./minishell", instr->cmd) == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (checkexecve_program(instr) == 1)
	{
		free(exitnum);
		exit(127);
	}
}

void	handle_slash_command(t_instr *instr, char **envp, \
t_exitnum *exitnum)
{
	if (check_buil(instr->cmd) == 1)
	{
		exec_buil(instr->mini, exitnum);
		free(exitnum);
		free_env(envp);
		free_mini(instr->mini);
		exit(instr->mini->exit_status);
	}
	if (checkexecve(instr) == 1)
	{
		free(exitnum);
		exit (127);
	}
}
*/

int	exec_inthepipe(t_instr *instr, char **envp, t_exitnum *exitnum)
{
	if (instr->cmd == NULL)
	{
		free(exitnum);
		free_env(instr->mini->e);
		free_mini(instr->mini);
		exit(0);
	}
	if (check_buil(instr->cmd) == 1)
	{
		handle_builtin(instr, envp, exitnum);
	}
	else if (ft_strchr(instr->cmd_arr[0], '/') == NULL)
	{
		execute(instr, envp, exitnum);
	}
	else
	{
		execute_command(NULL, instr->cmd_arr, instr, exitnum);
	}
	return (1);
}
/*
	else if (ft_strncmp(instr->cmd, "./", 2) == 0 \
	|| ft_strncmp(instr->cmd, "../", 3) == 0)
	{
		handle_dot_slash_command(instr, exitnum);
	}
*/
