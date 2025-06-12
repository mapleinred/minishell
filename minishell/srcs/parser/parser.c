/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:49:10 by mertan            #+#    #+#             */
/*   Updated: 2024/04/10 11:53:13 by mertan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//added else if type 11 or 111 to be type 51
int	parse_tkn_cmd(t_mini *mini, int i)
{
	if (mini->tkn[i].type == 10 || mini->tkn[i].type == 101 \
		|| mini->tkn[i].type == 111 || mini->tkn[i].type == 11 \
		|| mini->tkn[i].type == 4 || mini->tkn[i].type == 40)
	{
		if (mini->tkn[i].type == 10 || mini->tkn[i].type == 101)
			mini->tkn[i].type = 50;
		else if (mini->tkn[i].type == 11 || mini->tkn[i].type == 111)
			mini->tkn[i].type = 51;
		else
			mini->tkn[i].type = 5;
		i++;
	}
	return (i);
}

//added else if type 11 or 111 to be type 51
int	parse_tkn_f1(t_mini *mini, int i)
{
	if (mini->tkn[0].type == 10 || mini->tkn[0].type == 101
		|| mini->tkn[0].type == 111 || mini->tkn[0].type == 11
		|| mini->tkn[0].type == 4 || mini->tkn[i].type == 40)
	{
		if (mini->tkn[0].type == 10 || mini->tkn[0].type == 101)
			mini->tkn[0].type = 50;
		else if (mini->tkn[0].type == 11 || mini->tkn[0].type == 111)
			mini->tkn[0].type = 51;
		else
			mini->tkn[0].type = 5;
		i++;
	}
	if (mini->tkn[0].type == 2)
	{
		while (mini->tkn[i].type == 2)
			i += 2;
		if (mini->tkn[i].type != 10 && mini->tkn[i].type != 11 \
			&& mini->tkn[i].type != 101 && mini->tkn[i].type != 111)
			i = parse_tkn_cmd(mini, i);
	}
	return (i);
}

int	parse_tkn_f2(t_mini *mini, int i)
{
	while (i < mini->tks_num)
	{
		if (mini->tkn[i].type == 2)
		{
			while (mini->tkn[i].type == 2)
				i += 2;
		}
		if (mini->tkn[i].type == 3)
		{
			i++;
			while (mini->tkn[i].type == 2)
				i += 2;
			i = parse_tkn_cmd(mini, i);
		}
		else
			i++;
	}
	return (i);
}

//added type 51 into condition
int	parse_tkn(t_mini *mini, t_exitnum *exitnum)
{
	int	i;

	i = 0;
	i = parse_tkn_f1(mini, i);
	i = parse_tkn_f2(mini, i);
	i = 0;
	while (i < mini->tks_num)
	{
		if (mini->tkn[i].type == 5 || mini->tkn[i].type == 51 \
			|| mini->tkn[i].type == 11 || mini->tkn[i].type == 111 \
			|| mini->tkn[i].type == 4 || mini->tkn[i].type == 40)
		{
			if (ft_strchr(mini->input, '$') != 0)
				mini->tkn[i].str = expand_var(mini->tkn[i].str, mini, exitnum);
		}
		i++;
	}
	return (0);
}
