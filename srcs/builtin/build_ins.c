/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:49:10 by mertan            #+#    #+#             */
/*   Updated: 2024/04/10 11:53:13 by mertan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exit(t_instr *instr, t_exitnum *exitnum)
{
	int	exit_status;

	free_env(instr->mini->e);
	printf("exit\n");
	free(exitnum);
	if (instr->arg == NULL)
		ft_exit_a(instr->mini, 0);
	ft_exit_sign(instr);
	if (instr->arg != NULL && ft_strchr(instr->arg, ' ') != NULL)
	{
		printf("exit: too many arguments\n");
		ft_exit_a(instr->mini, 1);
	}
	if (ft_atoi(instr->arg) == 0 || check_number(instr->arg) == 0)
	{
		printf("exit: numeric argument required\n");
		ft_exit_a(instr->mini, 2);
	}
	else
	{
		exit_status = ft_atoi(instr->arg);
		ft_exit_a(instr->mini, exit_status);
	}
	return (0);
}

//char *getcwd(char *buf, size_t size);
//When buf is NULL and size is 0, getcwd dynamically allocates a buffer 
//large enough to hold the current directory path.
//getcwd returns a pointer to buffer containing the current directory path. 
//If an error occurs, it returns NULL, and errno is set to indicate the error.
int	ft_cd(t_instr *instr)
{
	int		status;
	char	*cwd;

	if (instr->arg != NULL && ft_strchr(instr->arg, ' ') != NULL)
	{
		ft_error(instr->mini, "cd: too many arguments", 1);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		ft_error(instr->mini, "cd: getcwd: ", 1);
	update_env("OLDPWD", cwd, instr->mini);
	free(cwd);
	status = update_cd_status(instr->arg, instr->mini);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		ft_error(instr->mini, "cd: getcwd: ", 1);
	update_env("PWD", cwd, instr->mini);
	free(cwd);
	instr->mini->exit_status = status;
	return (status);
}

int	ft_pwd(t_instr *instr)
{
	char	*cwd;

	(void)instr;
	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	return (0);
}

int	ft_env(t_instr *instr)
{
	int	i;

	i = 0;
	while (instr->mini->e[i] != NULL)
	{
		if (ft_strncmp("PATH", instr->mini->e[i], 4) == 0)
			break ;
		i++;
	}
	i = 0;
	while (instr->mini->e[i])
	{
		if (ft_strchr(instr->mini->e[i], '=') != NULL)
			printf("%s\n", instr->mini->e[i]);
		i++;
	}
	return (0);
}

int	ft_unset(t_instr *instr)
{
	int		i;
	char	**args;

	if (instr->arg == NULL)
		return (0);
	args = ft_split(instr->arg, ' ');
	i = 0;
	while (args[i])
	{
		ft_unset_exec(instr, args[i]);
		free(args[i]);
		i++;
	}
	free(args);
	return (0);
}
