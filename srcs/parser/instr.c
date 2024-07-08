/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:49:10 by mertan            #+#    #+#             */
/*   Updated: 2024/06/30 18:59:29 by xzhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_instr_f1(t_mini *mini, int i, t_instr *instr)
{
	char	*tmp;

	instr->cmd = ft_strdup(mini->tkn[i].str);
	i++;
	if (mini->tkn[i].type == 10 || mini->tkn[i].type == 11)
	{
		tmp = instr->cmd;
		instr->cmd = ft_strjoin(tmp, mini->tkn[i].str);
		free(tmp);
		i++;
	}
	if (mini->tkn[i].type == 40)
	{
		tmp = instr->cmd;
		instr->cmd = ft_strjoin(tmp, mini->tkn[i].str);
		free(tmp);
		i++;
	}
	return (i);
}

int	init_instr(t_mini *mini, int i, t_instr *instr)
{
	while (i < mini->tks_num && mini->tkn[i].type != 3)
	{
		if (mini->tkn[i].type == 2)
			i = init_redir(mini, i, instr);
		else if (mini->tkn[i].type == 5 || mini->tkn[i].type == 50 \
			|| mini->tkn[i].type == 51)
		{
			i = init_instr_f1(mini, i, instr);
		}
		else if (mini->tkn[i].type == 10 || mini->tkn[i].type == 101 \
		|| mini->tkn[i].type == 111 || mini->tkn[i].type == 11 \
		|| mini->tkn[i].type == 4 || mini->tkn[i].type == 40)
			i = init_arg(mini, i, instr);
	}
	return (i);
}

int	init_instr_cmdarr1(t_mini *mini, int i, t_instr *instr, int *j)
{
	char	*tmp;

	instr->cmd_arr[*j] = ft_strdup(mini->tkn[i].str);
	i++;
	while (i < mini->tks_num && (mini->tkn[i].type == 10 \
		|| mini->tkn[i].type == 11 || mini->tkn[i].type == 40))
	{
		tmp = instr->cmd_arr[*j];
		instr->cmd_arr[*j] = ft_strjoin(tmp, mini->tkn[i].str);
		free(tmp);
		i++;
	}
	if (i == mini->tks_num)
		return (i);
	(*j)++;
	return (i);
}	

int	init_instr_cmdarr(t_mini *mini, int i, t_instr *instr)
{
	int		j;

	j = 0;
	while (i < mini->tks_num)
	{
		if (mini->tkn[i].type == 2)
			i += 2;
		else if (mini->tkn[i].type == 3)
			break ;
		else if (mini->tkn[i].type == 5 || mini->tkn[i].type == 50 \
			|| mini->tkn[i].type == 51)
			i = init_instr_cmdarr1(mini, i, instr, &j);
		else if (mini->tkn[i].type == 10 || mini->tkn[i].type == 101 \
		|| mini->tkn[i].type == 111 || mini->tkn[i].type == 11 \
		|| mini->tkn[i].type == 4 || mini->tkn[i].type == 40)
			i = init_arg1(mini, i, &j, instr);
	}
	return (i);
}

void	create_instr(t_mini *mini)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < mini->instr_num)
	{
		mini->instr->mini = mini;
		i = init_instr(mini, i, &mini->instr[j]);
		if (mini->tkn[i].type == 3)
			i++;
		j++;
	}
}
