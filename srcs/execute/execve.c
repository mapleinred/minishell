/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 05:34:45 by xzhang            #+#    #+#             */
/*   Updated: 2024/06/23 05:34:47 by xzhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static char	**initcmd2( t_instr *instr, char ***args)
// {
// 	int		i;
// 	int		count;
// 	char	**cmd;

// 	i = 0;
// 	*args = ft_split(instr->arg, ' ');
// 	count = count_words(instr->arg, ' ');
// 	cmd = (char **)malloc(sizeof(char *) * (count + 2));
// 	if (!cmd)
// 	{
// 		free_env(*args);
// 		return (NULL);
// 	}
// 	cmd[0] = instr->cmd;
// 	if (!*args)
// 		return (cmd[1] = NULL, cmd);
// 	while (i < count + 1 && (*args)[i])
// 	{
// 		cmd[i + 1] = (*args)[i];
// 		i++;
// 	}
// 	cmd[i + 1] = NULL;
// 	return (cmd);
// }

// int	checkexecve_program(t_instr *instr)
// {
// 	char	**args;
// 	char	**cmd;
// 	int		i;

// 	i = count_words(instr->arg, ' ');
// 	cmd = initcmd2(instr, &args);
// 	if (!cmd)
// 		return (1);
// 	if (execve(instr->cmd, cmd, instr->mini->e) == -1)
// 	{
// 		perror("execve failed");
// 		free_env(instr->mini->e);
// 		if (args)
// 			free_env(args);
// 		free_tkn(instr->mini);
// 		free(instr->mini->input);
// 		free(cmd[0]);
// 		free(cmd[i + 1]);
// 		free(cmd);
// 		free(instr->arg);
// 		free(instr->mini->pipe);
// 		return (1);
// 	}
// 	return (0);
// }

// static char	**initcmd3( t_instr *instr, char ***args)
// {
// 	int		i;
// 	int		count;
// 	char	**cmd;

// 	i = 0;
// 	*args = ft_split(instr->arg, ' ');
// 	count = count_words(instr->arg, ' ');
// 	cmd = (char **)malloc(sizeof(char *) * (count + 2));
// 	if (!cmd)
// 	{
// 		free_env(*args);
// 		return (NULL);
// 	}
// 	cmd[0] = instr->cmd;
// 	cmd[0] = instr->cmd;
// 	if (!*args)
// 		return (cmd[1] = NULL, cmd);
// 	while (i < count + 1 && (*args)[i])
// 	{
// 		cmd[i + 1] = (*args)[i];
// 		i++;
// 	}
// 	cmd[i + 1] = NULL;
// 	return (cmd);
// }

// int	checkexecve(t_instr *instr)
// {
// 	//char	**cmd;
// 	//char	**args;

// 	// cmd = initcmd3(instr, &args);
// 	// if (!cmd)
// 	// 	return (1);
// 	if (execve(instr->cmd_arr[0], instr->cmd_arr, instr->mini->e) == -1)
// 	{
// 		perror("execve failed");
// 		free_env(instr->mini->e);
// 		free(instr->arg);
// 		free(args);
// 		free_tkn(instr->mini);
// 		free(instr->mini->pipe);
// 		//free_env(cmd);
// 		rl_clear_history();
// 		free(instr->mini->input);
// 		return (1);
// 	}
// 	return (0);
// }
