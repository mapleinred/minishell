/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:49:10 by mertan            #+#    #+#             */
/*   Updated: 2024/04/10 11:53:13 by mertan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//type '10', '11' == sq, dq
//type '2' == '>', '<'
//type '3' == |'
//type '4' == alnum, meta chars
//type '5' == cmd;

int	make_tkn_error(t_mini *mini, int i)
{
	if (mini->input[0] == '|' || ((mini->input[i] == '|' \
	&& mini->input[i + 1] == '\0')))
		return (free_tokens(mini));
	if ((mini->input[0] == '>' && mini->input[1] == '\0') \
		|| (mini->input[i] == '>' && ft_strchr("<|\0", mini->input[i + 1])))
		return (free_tokens(mini));
	if ((mini->input[0] == '<' && mini->input[1] == '\0') \
		|| (mini->input[i] == '<' && ft_strchr(">|\0", mini->input[i + 1])))
		return (free_tokens(mini));
	if ((mini->input[0] == '>' && mini->input[1] == '>' \
		&& mini->input[2] == '\0') || (mini->input[i] == '>' \
		&& mini->input[i + 1] == '>' && ft_strchr("<|\0", mini->input[i + 2])))
		return (free_tokens(mini));
	if ((mini->input[0] == '<' && mini->input[1] == '<' \
		&& mini->input[2] == '\0') || (mini->input[i] == '<' \
		&& mini->input[i + 1] == '<' && ft_strchr(">|\0", mini->input[i + 2])))
		return (free_tokens(mini));
	return (0);
}

void	make_tkn_var(t_mini *mini, int *i, int *j, int *k)
{
	if (mini->input[*i] == ' ')
		(*i)++;
	else if (mini->input[*i] == '\'' || mini->input[*i] == '"')
	{
		*i += init_tkn(&mini->input[*i], &mini->tkn[*j], 1, *i);
		(*j)++;
	}
	else if (ft_strchr("<>", mini->input[*i]))
	{
		*i += init_tkn(&mini->input[*i], &mini->tkn[*j], 2, *i);
		(*j)++;
	}
	else if (mini->input[*i] == '|')
	{
		*i += init_tkn(&mini->input[*i], &mini->tkn[*j], 3, *i);
		(*j)++;
		(*k)++;
	}
	else
	{
		*i += init_tkn(&mini->input[*i], &mini->tkn[*j], 4, *i);
		(*j)++;
	}
}

int	make_tkn(t_mini *mini)
{
	int	i;
	int	j;
	int	k;
	int	len;

	i = 0;
	j = 0;
	k = 0;
	len = ft_strlen(mini->input);
	while (i <= len && mini->input[i])
	{
		mini->tkn[j].mini = mini;
		if (make_tkn_error(mini, i) == -1)
			return (-1);
		make_tkn_var(mini, &i, &j, &k);
	}
	mini->tks_num = j;
	mini->instr_num = k + 1;
	return (0);
}
