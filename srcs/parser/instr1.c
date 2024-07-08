/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:49:10 by mertan            #+#    #+#             */
/*   Updated: 2024/06/30 18:59:29 by xzhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_arg_f2(t_mini *mini, int i, int j, t_instr *instr)
{
	char	*tmp;

	tmp = instr->cmd_arr[j];
	if (tmp)
		instr->cmd_arr[j] = ft_strjoin(tmp, mini->tkn[i].str);
	else
		instr->cmd_arr[j] = ft_strdup(mini->tkn[i].str);
	free(tmp);
	i++;
	return (i);
}

int	init_arg_f1(t_mini *mini, int i, t_instr *instr)
{
	char	*tmp;

	tmp = instr->arg;
	instr->arg = ft_strjoin(tmp, " ");
	free(tmp);
	tmp = instr->arg;
	instr->arg = ft_strjoin(tmp, mini->tkn[i].str);
	free(tmp);
	i++;
	return (i);
}

int	init_arg(t_mini *mini, int i, t_instr *instr)
{
	char	*tmp;

	instr->arg = ft_strdup(mini->tkn[i].str);
	i++;
	while (i < mini->tks_num && mini->tkn[i].type != 3)
	{
		if (mini->tkn[i].type == 2)
			i = init_redir(mini, i, instr);
		else if (mini->tkn[i].type == 4 \
			|| mini->tkn[i].type == 101 || mini->tkn[i].type == 111)
			i = init_arg_f1(mini, i, instr);
		else if (mini->tkn[i].type == 40 \
			|| mini->tkn[i].type == 10 || mini->tkn[i].type == 11)
		{
			tmp = instr->arg;
			instr->arg = ft_strjoin(tmp, mini->tkn[i].str);
			free(tmp);
			i++;
		}
		else if (mini->tkn[i].type == 3)
			return (i);
	}
	return (i);
}

int	init_arg1(t_mini *mini, int i, int *j, t_instr *instr)
{
	char	*tmp;

	instr->cmd_arr[*j] = ft_strdup(mini->tkn[i].str);
	i++;
	while (i < mini->tks_num && mini->tkn[i].type != 3)
	{
		if (mini->tkn[i].type == 2)
			i += 2;
		else if (mini->tkn[i].type == 4 \
			|| mini->tkn[i].type == 101 || mini->tkn[i].type == 111)
			i = init_arg_f2(mini, i, ++(*j), instr);
		else if (mini->tkn[i].type == 40 \
			|| mini->tkn[i].type == 10 || mini->tkn[i].type == 11)
		{
			tmp = instr->cmd_arr[*j];
			instr->cmd_arr[*j] = ft_strjoin(tmp, mini->tkn[i].str);
			free(tmp);
			i++;
		}
		else if (mini->tkn[i].type == 3)
			return (i);
	}
	return (i);
}
