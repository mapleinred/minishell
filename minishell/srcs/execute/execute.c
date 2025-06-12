/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 05:26:42 by xzhang            #+#    #+#             */
/*   Updated: 2024/06/30 17:08:39 by achak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*subfindpath(t_mini *mini, char *cmd, int i)
{
	char	**paths;
	char	*path;
	char	*path1;

	paths = ft_split(mini->e[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path1 = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path1, cmd);
		free(path1);
		if (access(path, F_OK) == 0)
		{
			free_env(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_env(paths);
	return (NULL);
}

char	*findpath(char *cmd, t_mini *mini, t_exitnum *exitnum)
{
	char	*path1;
	int		i;
	char	**envp;

	i = 0;
	envp = mini->e;
	path1 = get_env_path("PATH", mini->e);
	if (!path1 || path1[5] == '\0')
	{
		access(cmd, F_OK);
		free(path1);
		free_env(envp);
		perror(cmd);
		free(exitnum);
		free_mini(mini);
		exit(127);
	}
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	free(path1);
	path1 = subfindpath(mini, cmd, i);
	if (!path1)
		return (NULL);
	return (path1);
}
/*
// char	*get_path_or_exit(char **cmd, t_instr *instr, char **envp, \
// t_exitnum *exitnum)
// {
// 	char	*path;

// 	path = findpath(cmd[0], instr->mini);
// 	if (!path)
// 	{
// 		ft_putstr_fd(cmd[0], 2);
// 		ft_putstr_fd(": command not found\n", 2);
// 		free_env(cmd);
// 		free_env(envp);
// 		free(exitnum);
// 		free_mini(instr->mini);
// 		exit(127);
// 	}
// 	return (path);
// }

// char	**initialize_cmd(t_instr *instr)
// {
// 	char	**args;
// 	char	**cmd;
// 	int		count;
// 	int		i;

// 	i = 0;
// 	args = ft_split(instr->arg, ' ');
// 	count = count_words(instr->arg, ' ');
// 	cmd = (char **)malloc(sizeof(char *) * (count + 2));
// 	if (!cmd)
// 	{
// 		freemem(args);
// 		return (NULL);
// 	}
// 	ft_memset(cmd, 0, sizeof(char *) * (count + 2));
// 	cmd[0] = ft_strdup(instr->cmd);
// 	while (i < count && args)
// 	{
// 		cmd[i + 1] = args[i];
// 		i++;
// 	}
// 	cmd[i + 1] = NULL;
// 	free(args);
// 	return (cmd);
// }

// int	execute(t_instr *instr, char **envp, t_exitnum *exitnum)
// {
// 	char	**cmd;
// 	char	*path;

// 	cmd = initialize_cmd(instr);
// 	if (!cmd)
// 		return (1);
// 	path = get_path_or_exit(cmd, instr, envp, exitnum);
// 	execute_command(path, cmd, instr, exitnum);
// 	return (2);
// }
*/

int	execute(t_instr *instr, char **envp, t_exitnum *exitnum)
{
	char	*path;

	path = get_path_or_exit(instr->cmd_arr[0], instr, envp, exitnum);
	execute_command(path, instr->cmd_arr, instr, exitnum);
	return (2);
}

char	*get_path_or_exit(char *cmd, t_instr *instr, \
char **envp, t_exitnum *exitnum)
{
	char	*path;

	path = findpath(cmd, instr->mini, exitnum);
	if (!path)
	{
		ft_putstr_fd(instr->cmd_arr[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_env(envp);
		free(exitnum);
		free_mini(instr->mini);
		exit(127);
	}
	return (path);
}
