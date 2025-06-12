/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ins_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:49:10 by mertan            #+#    #+#             */
/*   Updated: 2024/04/10 11:53:13 by mertan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	update_env(char	*var, char *new_str, t_mini *mini)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	while (mini->e[i])
	{
		len = 0;
		while (mini->e[i][len] != '=')
			len++;
		if (ft_strncmp(mini->e[i], var, len) == 0)
		{
			free(mini->e[i]);
			tmp = ft_strjoin(var, "=");
			mini->e[i] = ft_strjoin(tmp, new_str);
			free(tmp);
			return (1);
		}
		i++;
	}
	return (0);
}

char	*get_env_path(char *var, char **e)
{
	int		i;
	int		len;
	char	*path;

	i = 0;
	path = NULL;
	while (e[i] != NULL)
	{
		len = 0;
		while (e[i][len] != '=' && e[i][len] != '\0')
			len++;
		if (ft_strncmp(e[i], var, len) == 0)
			path = ft_strdup(e[i] + (len + 1));
		i++;
	}
	return (path);
}

//When you call chdir with a specified path, it attempts to change the 
//current working directory of the process to that path. This affects all
//relative path operations in the process, meaning any subsequent file
//operations using relative paths will be relative to the new directory.
//On success, chdir return (0), otherwise, return (-1) with errno 
//int chdir(const char *PATH);
int	update_cd_status(char *arg, t_mini *mini)
{
	int		status;
	char	*path;
	char	*tmp;

	path = get_env_path("HOME", mini->e);
	if (!path || path[5] == '\0')
	{
		free(path);
		return (ft_error(mini, "cd: HOME not set", 1));
	}
	if (arg == NULL || arg[0] == '~')
		status = chdir(path);
	else if (arg[0] == '\0')
		return (free(path), 0);
	else
		status = chdir(arg);
	if (status != 0)
	{
		tmp = ft_strjoin("Minishell: cd: ", arg);
		perror(tmp);
		free(tmp);
		status = 1;
	}
	free(path);
	return (status);
}

int	check_env(char *str, char *var, t_instr *instr)
{
	int		i;

	i = 0;
	while (instr->mini->e[i])
	{
		if (ft_strncmp(instr->mini->e[i], var, ft_strlen(var)) == 0)
		{
			free(instr->mini->e[i]);
			instr->mini->e[i] = ft_strdup(str);
			return (1);
		}
		i++;
	}
	return (0);
}

int	declare_env(char **env, int env_count)
{
	int		i;
	char	**new_env;
	int		j;

	i = 0;
	j = 0;
	new_env = (char **)malloc(sizeof(char *) * env_count);
	while (env[i])
	{
		if (env[i][0] == '_')
		{
			j++;
			i++;
		}
		if (env[i])
		{
			new_env[i - j] = ft_strdup(env[i]);
			i++;
		}
	}
	new_env[i - j] = NULL;
	sort_env_ascii(new_env, i - j);
	free_env(new_env);
	return (0);
}
