/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:49:10 by mertan            #+#    #+#             */
/*   Updated: 2024/04/10 11:53:13 by mertan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	free_tokens(t_mini *mini)
{
	int	i;

	i = 0;
	while (i < 128)
	{
		if (mini->tkn[i].str != NULL)
		{
			free(mini->tkn[i].str);
		}
		mini->tkn[i].type = 0;
		i++;
	}
	ft_error(mini, "Minishell: Syntax error", 2);
	return (-1);
}

void	freemem(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		free(str[i]);
		str[i] = NULL;
	}
	free(str);
	str = NULL;
}

void	fterror(char *str)
{
	perror(str);
	exit(127);
}

int	check_buil(char *str)
{
	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "cd") == 0
		|| ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "env") == 0
		|| ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

void	free_instructions(t_mini *mini)
{
	int	i;

	i = 0;
	while (i < 64)
	{
		if (mini->instr[i].arg != NULL)
		{
			free(mini->instr[i].arg);
		}
		if (mini->instr[i].cmd != NULL)
		{
			free(mini->instr[i].cmd);
		}
		if (mini->instr[i].redir_num < 64)
		{
			free_redir(&mini->instr[i]);
		}
		mini->instr[i].redir_num = 0;
		i++;
	}
}
/*
void	ftperror(char *str)
{
	char	*tmp;

	tmp = ft_strjoin(": ", str);
	perror(tmp);
	free(tmp);
	exit(127);
}*/
