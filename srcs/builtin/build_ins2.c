/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:49:10 by mertan            #+#    #+#             */
/*   Updated: 2024/06/30 18:12:47 by xzhang            ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//option '0' == no option
//option '1' == -n

/*
int	ft_echo_option(char *tmp, int i, int *flag)
{
	if (ft_strncmp(tmp, "-n", 2) == 0)
	{
		*flag = 1;
		i = 2;
		while (tmp[i] != '\0' && tmp[i] != ' ')
		{
			if (tmp[i] != 'n')
			{
				*flag = 0;
				break ;
			}
			i++;
		}
	}
	return (i);
}

int	ft_echo_opt(t_instr *instr, int *flag, int *k, int *j)
{
	int	t;

	t = instr->mini->tkn[*j].type;
	if (ft_strncmp(instr->mini->tkn[*j].str, "-n", 2) == 0 \
		&& (t == 4 || t == 101 || t == 111))
	{
		*k = 2;
		while (instr->mini->tkn[*j].str[*k] != '\0')
		{
			if (instr->mini->tkn[*j].str[*k] != 'n')
			{
				*flag = 0;
				return (-1);
			}
			(*k)++;
		}
		if (*j + 1 < instr->mini->tks_num)
		{
			if (instr->mini->tkn[*j + 1].type == 10 \
				|| instr->mini->tkn[*j + 1].type == 11)
				*flag = 0;
		}
	}
	return (0);
}

int	ft_echo_tkn(t_instr *instr, char *tmp, int i, int *flag)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	(void)i;
	if (ft_strncmp(tmp, "-n", 2) == 0)
	{
		*flag = 1;
		j = 0;
		while (j < instr->mini->tks_num)
		{
			if (ft_echo_opt(instr, flag, &k, &j) == -1)
				break ;
			j++;
		}
	}
	return (k);
}*/

int	ft_echo_tkn(t_instr *instr, int *flag)
{
	int	i;

	i = 1;
	if (ft_strncmp(instr->mini->tkn[1].str, "-n", 2) == 0)
		*flag = 1;
	while (*flag == 1 && instr->mini->tkn[1].str[i])
	{
		if (instr->mini->tkn[1].str[i] != 'n')
		{
			*flag = 0;
			break ;
		}
		i++;
		if (instr->mini->tks_num > 2)
		{
			if (instr->mini->tkn[2].type == 10 \
				|| instr->mini->tkn[2].type == 11)
				*flag = 0;
		}
	}
	return (i);
}

int	ft_echo(t_instr *instr)
{
	char	*tmp;
	int		i;
	int		flag;

	flag = 0;
	tmp = instr->arg;
	if (tmp == NULL)
	{
		printf("\n");
		return (0);
	}
	i = ft_echo_tkn(instr, &flag);
	if (flag == 1)
	{
		if (ft_strchr(tmp, ' '))
			i++;
		write(STDOUT_FILENO, tmp + i, ft_strlen(tmp + i));
	}
	else
		printf("%s\n", tmp);
	return (0);
}
