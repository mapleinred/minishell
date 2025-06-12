/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
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
int	find_strlen(char *str, int type, int i)
{
	char	c;

	c = str[i];
	if (type == 1)
	{
		i++;
		while (str[i] != c && str[i] != '\0')
			i++;
		i++;
	}
	if (type == 2)
	{
		i++;
		if (str[i] == c)
			i++;
	}
	if (type == 3)
		i = 1;
	if (type == 4)
	{
		while (str[i] != ' ' && str[i] != '\0' && \
		!ft_strchr("<>|", str[i]) && str[i] != '\'' && str[i] != '"')
			i++;
	}
	return (i);
}

void	init_tkn_type1(char *str, t_tkn *tkn, int len, int str_pos)
{
	if (len < 3)
		tkn->str = ft_strdup("");
	else
	{
		tkn->str = (char *)malloc(len - 1);
		ft_strlcpy(tkn->str, str + 1, len - 1);
	}
	if (*str == '\'')
	{
		if (str_pos == 0)
			tkn->type = 10;
		else if (str_pos != 0 && *(str - 1) == ' ')
			tkn->type = 101;
		else
			tkn->type = 10;
	}
	if (*str == '"')
	{
		if (str_pos == 0)
			tkn->type = 11;
		else if (str_pos != 0 && *(str - 1) == ' ')
			tkn->type = 111;
		else
			tkn->type = 11;
	}
}

int	init_tkn(char *str, t_tkn *tkn, int type, int str_pos)
{
	int	i;
	int	len;

	i = 0;
	tkn->type = type;
	len = find_strlen(str, type, i);
	if (type == 1)
	{
		init_tkn_type1(str, tkn, len, str_pos);
	}
	else
	{
		if (len != 0)
		{
			tkn->str = (char *)malloc(len + 1);
			ft_strlcpy(tkn->str, str, len + 1);
		}
		if (tkn->type == 4 && ft_strlen(tkn->mini->input) != ft_strlen(str) \
			&& (*(str - 1) == '\'' || *(str - 1) == '"'))
			tkn->type = 40;
	}
	return (len);
}
