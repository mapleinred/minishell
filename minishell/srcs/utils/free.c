/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:49:10 by mertan            #+#    #+#             */
/*   Updated: 2024/06/30 16:50:45 by achak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_env(char **e)
{
	int	i;

	i = 0;
	while (e[i])
	{
		free(e[i]);
		e[i] = NULL;
		i++;
	}
	free(e);
	e = NULL;
}

void	free_tkn(t_mini *mini)
{
	int	i;

	i = 0;
	while (i < mini->tks_num)
	{
		if (mini->tkn[i].str != NULL)
		{
			free(mini->tkn[i].str);
		}
		mini->tkn[i].type = 0;
		i++;
	}
}

void	free_redir(t_instr *instr)
{
	int	i;

	i = 0;
	while (i < instr->redir_num)
	{
		if (instr->redir[i].str != NULL)
			free(instr->redir[i].str);
		instr->redir[i].type = 0;
		i++;
	}
}

void	free_instr(t_mini *mini)
{
	int	i;

	i = 0;
	while (i < mini->instr_num)
	{
		if (mini->instr[i].cmd_arr)
			free_env(mini->instr[i].cmd_arr);
		if (mini->instr[i].arg != NULL)
		{
			free(mini->instr[i].arg);
		}
		if (mini->instr[i].cmd != NULL)
		{
			free(mini->instr[i].cmd);
		}
		if (mini->instr[i].redir_num != 0)
		{
			free_redir(&mini->instr[i]);
		}
		mini->instr[i].redir_num = 0;
		i++;
	}
}

void	free_mini(t_mini *mini)
{
	if (mini->input != NULL)
	{
		free(mini->input);
	}
	if (mini->tks_num != 0)
	{
		free_tkn(mini);
	}
	if (mini->instr_num != 0)
	{
		free_instr(mini);
	}
	if (mini->pipe != NULL)
	{
		free(mini->pipe);
	}
	mini->tks_num = 0;
	mini->instr_num = 0;
}
