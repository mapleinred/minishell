/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ins1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:49:10 by mertan            #+#    #+#             */
/*   Updated: 2024/04/10 11:53:13 by mertan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_export_a1(t_instr *instr, int *i, char *var, int *j)
{
	char	*tmp;
	char	*tmp1;

	(void)(*j);
	tmp = ft_strjoin(instr->mini->tkn[*i - 1].str, instr->mini->tkn[*i].str);
	if (instr->mini->tkn[*i].str[0] == '\0' \
		|| instr->mini->tkn[*i].str[0] == ' ')
	{
		(*i)++;
		if (instr->mini->tkn[*i].type == 40)
		{	
			tmp1 = ft_strdup(tmp);
			free(tmp);
			tmp = ft_strjoin(tmp1, instr->mini->tkn[*i].str);
			free(tmp1);
		}
	}
	if (check_env(tmp, var, instr) == 0)
		append_env(instr, tmp, instr->mini->env_count);
	return (free(var), free(tmp), -1);
}

int	ft_export_a2(t_instr *instr, int *i, char *var, int *j)
{
	(*i)++;
	*j = 0;
	if (instr->mini->tkn[*i].type == 10 || instr->mini->tkn[*i].type == 11)
	{
		if (ft_export_a1(instr, i, var, j) == -1)
			return (-1);
	}
	else
	{
		(*i)--;
		if (check_env(instr->mini->tkn[*i].str, var, instr) == 0)
			append_env(instr, instr->mini->tkn[*i].str, instr->mini->env_count);
		return (free(var), -1);
	}
	return (0);
}

int	ft_export_a3(t_instr *instr, int *i, int *j)
{
	char	*var;
	char	*str;

	str = instr->mini->tkn[*i].str;
	if (str[*j] == '=')
	{
		var = ft_substr(str, 0, *j);
		if (ft_export_error(instr, var, str) != 0)
			return (1);
		if (instr->mini->tkn[*i].type == 101 \
			|| instr->mini->tkn[*i].type == 111)
		{
			if (check_env(str, var, instr) == 0)
				append_env(instr, str, instr->mini->env_count);
			free(var);
			return (-1);
		}
		else if (ft_export_a2(instr, i, var, j) == -1)
			return (-1);
	}
	return (0);
}

int	ft_export_a4(t_instr *instr, int i, int j, char *var)
{
	int	exit_num;

	while (i < instr->mini->tks_num)
	{
		j = 0;
		while (instr->mini->tkn[i].str[j])
		{	
			exit_num = ft_export_a3(instr, &i, &j);
			if (exit_num == 1)
				return (1);
			else if (exit_num == -1)
				break ;
			j++;
			if (j == (int)ft_strlen(instr->mini->tkn[i].str))
			{
				var = ft_strdup(instr->mini->tkn[i].str);
				if (ft_export_error(instr, var, instr->mini->tkn[i].str) != 0)
					return (1);
				free(var);
			}
		}
		i++;
	}
	return (0);
}

int	ft_export(t_instr *instr)
{
	if (instr->arg == NULL)
		return (declare_env(instr->mini->e, instr->mini->env_count));
	if (check_omitspaces(instr) != 0)
		return (ft_export_a4(instr, 1, 0, NULL));
	else
		ft_export_nq(instr);
	return (0);
}
