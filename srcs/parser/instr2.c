/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:49:10 by mertan            #+#    #+#             */
/*   Updated: 2024/06/30 18:59:29 by xzhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_redir_f1(t_mini *mini, int i, t_instr *instr, int *k)
{
	char	*tmp;

	if (mini->tkn[i].type == 10 || mini->tkn[i].type == 101 \
		|| mini->tkn[i].type == 11 || mini->tkn[i].type == 111 \
		|| mini->tkn[i].type == 4 || mini->tkn[i].type == 40)
	{
		instr->redir[*k].str = ft_strdup(mini->tkn[i].str);
		i++;
	}
	if (mini->tkn[i].type == 10 || mini->tkn[i].type == 11)
	{
		tmp = instr->redir[*k].str;
		instr->redir[*k].str = ft_strjoin(tmp, mini->tkn[i].str);
		free(tmp);
		i++;
	}
	if (mini->tkn[i].type == 40)
	{
		tmp = instr->redir[*k].str;
		instr->redir[*k].str = ft_strjoin(tmp, mini->tkn[i].str);
		free(tmp);
		i++;
	}
	return (i);
}

int	init_redir(t_mini *mini, int i, t_instr *instr)
{
	int		k;

	k = instr->redir_num;
	instr->redir[k].instr = instr;
	if (mini->tkn[i].str[0] == '>' && mini->tkn[i].str[1] == '\0')
		instr->redir[k].type = 1;
	else if (mini->tkn[i].str[0] == '<' && mini->tkn[i].str[1] == '\0')
		instr->redir[k].type = 2;
	else if (mini->tkn[i].str[0] == '>' && mini->tkn[i].str[1] == '>')
		instr->redir[k].type = 3;
	else if (mini->tkn[i].str[0] == '<' && mini->tkn[i].str[1] == '<')
		instr->redir[k].type = 4;
	i++;
	i = init_redir_f1(mini, i, instr, &k);
	k++;
	instr->redir_num = k;
	return (i);
}
